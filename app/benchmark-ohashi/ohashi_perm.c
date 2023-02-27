// include
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> // uint32_t
#include <string.h>
#include <fcntl.h>	  // open
#include <unistd.h>	  // read
#include <sys/mman.h> // mmap
#include <time.h>
#include "hdc_processor.h"

// 試行回数
// 100万回
#define TRIAL_NUM 1000000

uint32_t xor128(int reset)
{
	// 初期値
	static uint32_t x = 123456789;
	static uint32_t y = 362436069;
	static uint32_t z = 521288629;
	static uint32_t w = 88675123;

	// リセット信号
	if (reset)
	{
		x = 123456789;
		y = 362436069;
		z = 521288629;
		w = 88675123;
		return 0;
	}
	else
	{
		uint32_t t = x ^ (x << 11);
		x = y;
		y = z;
		z = w;
		return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
	}
}

int main(int argc, char const *argv[])
{
	const int RANNUM = 512;

	// hv -----------------------------
	// メモリセットアップ
	hdc_setup();

	// COM
	hdc_com_start();
	hdc_com_gen(88675123);
	for (int i = 0; i < 31; i++)
	{
		hdc_com_gen(xor128(0));
	}
	for (int i = 0; i < RANNUM - 1; i++)
	{
		for (int j = 0; j < 32; j++)
		{
			hdc_com_gen(xor128(0));
		}
	}
	hdc_compute_only();
	hdc_finish();
	// hv -----------------------------

	double RAN_TIME = 0.0;
	clock_t START_COMPUTE;
	clock_t END_COMPUTE;

	srand(10);

	// SEND_NUM初期化
	hdc_init(0);
	hdc_start();

	/////////////////////////////////////////////////////////////////////////////
	START_COMPUTE = clock();
	int *rand_array = (int *)calloc(TRIAL_NUM, sizeof(int));
	int *perm_array = (int *)calloc(TRIAL_NUM, sizeof(int));
	for (int i = 0; i < TRIAL_NUM; i++)
	{
		rand_array[i] = rand() % RANNUM;
		perm_array[i] = rand() % 1024;
	}
	END_COMPUTE = clock();
	RAN_TIME += ((double)(END_COMPUTE - START_COMPUTE)) / CLOCKS_PER_SEC;
	/////////////////////////////////////////////////////////////////////////////

	uint32_t addr_array[THREADS_NUM];

	for (int ll = 0; ll < TRIAL_NUM; ll += THREADS_NUM)
	{
		int rand_array_num = ll;
		int perm_array_num = ll;

		for (int k = 0; k < THREADS_NUM; k++)
		{
			addr_array[k] = rand_array[rand_array_num++];
		}

		// load ---------------------------------------------
		hdc_load_1(addr_array);
		// ------------------------------------------------------

		// perm ---------------------------------------------
		hdc_permute_1(perm_array[perm_array_num]);
		// ------------------------------------------------------
	}

	// ラスト命令
	// hdc_last();

	hdc_compute_only();

	hdc_finish();

	printf("\n  ランダム生成時間: %lf[s]\n", RAN_TIME);

	return 0;
}