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

int main(int argc, char const *argv[])
{
	const int RANNUM = 512;

	// メモリセットアップ
	hdc_setup();

	clock_t START_COMPUTE = clock();
	// アイテムメモリ生成
	hdc_make_imem(RANNUM);
	clock_t END_COMPUTE = clock();
	double COM_TIME = ((double)(END_COMPUTE - START_COMPUTE)) / CLOCKS_PER_SEC;

	hdc_finish();

	printf("\n  計算時間: %lf[s]\n", COM_TIME);

	return 0;
}