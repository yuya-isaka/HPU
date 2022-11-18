
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> // uint16_t
#include <string.h>
#include <fcntl.h>	  // open
#include <unistd.h>	  // read
#include <sys/mman.h> // mmap
#include <sys/stat.h>
#include <time.h>

// ------------------------------------------------------------------------------------------------

// 簡易アセンブラ
// 10種類の命令
uint16_t assemble(const char inst_str[], uint16_t addr)
{
	if (strcmp(inst_str, "load") == 0 || strcmp(inst_str, "wbitem") == 0)
	{
		uint16_t result = 0;

		// load
		if (strcmp(inst_str, "load") == 0)
		{
			uint16_t inst = 49152;
			result = inst | addr;
		}

		// wb.item
		else if (strcmp(inst_str, "wbitem") == 0)
		{
			uint16_t inst = 40960;
			result = inst | addr;
		}

		return result;
	}

	else
	{
		uint16_t inst = 0;

		// rshift
		if (strcmp(inst_str, "rshift") == 0)
		{
			inst = 16384;
		}

		// lshift
		else if (strcmp(inst_str, "lshift") == 0)
		{
			inst = 8192;
		}

		// xor
		else if (strcmp(inst_str, "xor") == 0)
		{
			inst = 4096;
		}

		// store
		else if (strcmp(inst_str, "store") == 0)
		{
			inst = 2048;
		}

		// last
		else if (strcmp(inst_str, "last") == 0)
		{
			inst = 1024;
		}

		// move
		else if (strcmp(inst_str, "move") == 0)
		{
			inst = 512;
		}

		// wb
		else if (strcmp(inst_str, "wb") == 0)
		{
			inst = 256;
		}

		else
		{
			printf("error");
		}

		return inst;
	}
}

// ----------------------------------------------------------------------------------------------------------------------------------------------

int main(int argc, char const *argv[])
{
	clock_t start = clock();

	uint16_t *src = (uint16_t *)calloc(300000000, sizeof(uint16_t));

	const int core_num = 32;
	// const int trial_num = 50000000;
	const int trial_num = 10000000;
	const int send_num_max = 33000000;

	// ----------------------------------------------------------------------------------------------------------------------------------------------

	int send_num = 0;

	int addr1[core_num];
	int addr2[core_num];
	int send_num_array[100];
	int send_num_count = 0;
	int count = 0;

	for (int i = 0; i < trial_num; i += core_num)
	{

		// ----------------------------------------------------------------------------------------------------------------------------------------------

		for (int j = 0; j < core_num; j++)
		{
			addr1[j] = rand() % 512;
			addr2[j] = rand() % 512;
		}

		for (int j = 0; j < core_num; j++)
		{
			src[send_num++] = assemble("load", addr1[j]);
			count++;
		}

		for (int j = 0; j < core_num; j++)
		{
			src[send_num++] = assemble("move", 0);
			count++;
		}

		for (int j = 0; j < core_num; j++)
		{
			src[send_num++] = assemble("load", addr2[j]);
			count++;
		}

		for (int j = 0; j < core_num; j++)
		{
			src[send_num++] = assemble("xor", 0);
			count++;
		}

		for (int j = 0; j < core_num; j++)
		{
			src[send_num++] = assemble("store", 0);
			count++;
		}

		// --------------------------------------------------------------------------------------------------------------------------------------------

		if (count >= send_num_max)
		{
			// last命令
			for (int j = 0; j < core_num; j++)
			{
				uint16_t inst = assemble("last", 0);
				src[send_num++] = inst;
				count++;
			}
			send_num_array[send_num_count++] = count;
			count = 0;
		}
	}

	// ----------------------------------------------------------------------------------------------------------------------------------------------

	// last命令
	for (int i = 0; i < core_num; i++)
	{
		uint16_t inst = assemble("last", 0);
		src[send_num++] = inst;
		count++;
	}
	send_num_array[send_num_count++] = count;

	clock_t end = clock();
	const double time = ((double)(end - start)) / CLOCKS_PER_SEC * 1000.0;
	printf("データ準備時間（CPU）: %lf[ms]\n", time);

	// ----------------------------------------------------------------------------------------------------------------------------------------------

	puts("\n  --------------------------------------- HDC Program end -------------------------------------\n");

	return 0;
}
