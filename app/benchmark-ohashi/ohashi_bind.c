// include
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> // uint16_t
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
	int *rand_array_1 = (int *)calloc(TRIAL_NUM, sizeof(int));
	int *rand_array_2 = (int *)calloc(TRIAL_NUM, sizeof(int));
	for (int i = 0; i < TRIAL_NUM; i++)
	{
		rand_array_1[i] = rand() % RANNUM;
		rand_array_2[i] = rand() % RANNUM;
	}
	END_COMPUTE = clock();
	RAN_TIME += ((double)(END_COMPUTE - START_COMPUTE)) / CLOCKS_PER_SEC;
	/////////////////////////////////////////////////////////////////////////////

	uint16_t addr_array1[THREADS_NUM];
	uint16_t addr_array2[THREADS_NUM];

	for (int ll = 0; ll < TRIAL_NUM; ll += THREADS_NUM)
	{
		int tmp = ll;

		// アドレス
		for (int k = 0; k < THREADS_NUM; k++)
		{
			addr_array1[k] = rand_array_1[tmp];
			addr_array2[k] = rand_array_2[tmp];
			tmp++;
		}

		// load ---------------------------------------------
		hdc_load_1(THREADS_NUM, addr_array1);
		// ------------------------------------------------------

		// load ---------------------------------------------
		hdc_load_2(THREADS_NUM, addr_array2);
		// ------------------------------------------------------

		// bind ---------------------------------------------
		hdc_bind_121(THREADS_NUM);
		// ------------------------------------------------------
	}

	// ラスト命令
	// hdc_last();

	hdc_compute_only();

	hdc_finish();

	printf("\n  ランダム生成時間: %lf[s]\n", RAN_TIME);

	return 0;
}