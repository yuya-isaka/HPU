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

	// メモリセットアップ
	hdc_setup();

	// アイテムメモリ生成
	hdc_com_gen(88675123);
	for (int i = 0; i < 31; i++)
	{
		hdc_com_gen(xor128(0));
	}
	for (int i = 0; i < 511; i++)
	{
		for (int j = 0; j < 32; j++)
		{
			hdc_com_gen(xor128(0));
		}
	}
	hdc_compute_only();

	hdc_finish();

	return 0;
}