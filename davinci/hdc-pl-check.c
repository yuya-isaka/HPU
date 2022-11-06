#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

void makeArray(uint16_t ***a, const int y, const int x)
{
	*a = (uint16_t **)calloc(y, sizeof(uint16_t *));
	for (int i = 0; i < y; i++)
	{
		(*a)[i] = (uint16_t *)calloc(x, sizeof(uint16_t));
	}
}

void freeArray(uint16_t ***a, const int y)
{
	for (int i = 0; i < y; i++)
	{
		free((*a)[i]);
	}
	free(*a);
}

uint16_t get_bit(int addr_flag, unsigned int inst_num, uint16_t addr)
{
	if (addr_flag)
	{
		uint16_t result = 0;
		if (inst_num == 1)
		{
			uint16_t inst = 3 << 14;
			result = inst | addr;
		}
		else if (inst_num == 2)
		{
			uint16_t inst = 5 << 13;
			result = inst | addr;
		}
		else if (inst_num == 4)
		{
			uint16_t inst = 9 << 12;
			result = inst | addr;
		}
		else if (inst_num == 6)
		{
			uint16_t inst = 17 << 11;
			result = inst | addr;
		}
		else
		{
			printf("error");
		}
		return result;
	}
	else
	{
		uint16_t inst = 0;
		if (inst_num == 3)
		{
			inst = 1 << 14;
		}
		else if (inst_num == 5)
		{
			inst = 1 << 13;
		}
		else if (inst_num == 7)
		{
			inst = 1 << 12;
		}
		else if (inst_num == 8)
		{
			inst = 1 << 11;
		}
		else if (inst_num == 9)
		{
			inst = 1 << 10;
		}
		else if (inst_num == 10)
		{
			inst = 1 << 9;
		}
		else
		{
			printf("error");
		}
		return inst;
	}
}

int main(int argc, char const *argv[])
{
	printf("\n\n");
	// ---------------------------------------------
	uint16_t **src_tmp;
	uint16_t **ascii_array;
	const int train_num = 2;
	const char *train_path[] = {"data/decorate/simple_en", "data/decorate/simple_fr"};
	// const char *train_path[] = {"data/decorate/en", "data/decorate/fr"};
	const int ngram = 3;
	const int core_num = 8;
	const int instruction_num = 9;
	int all_ngram = 0;
	int even = 0;
	// -------------------------------------------
	for (int i = 0; i < train_num; i++)
	{
		const char *path = train_path[i];
		printf("------------- %sの学習 -------------\n\n", path);
		FILE *file;
		file = fopen(path, "r");
		if (file == NULL)
		{
			perror("  Failed to open file");
			exit(1);
		}
		int ch;
		int num = 0;
		// while (((ch = fgetc(file)) != EOF) && ((ch = fgetc(file) != 255))) // ubuntu:EOF == -1,  petalinux:EOF == 255
		while ((ch = fgetc(file)) != EOF) // ubuntu:EOF == -1,  petalinux:EOF == 255
		{
			num++;
		}
		fseek(file, 0, SEEK_SET);
		char *content = (char *)calloc(num, sizeof(char));
		size_t done = fread(content, sizeof(char), num, file);
		if (done < num)
		{
			perror("  Failed: fread file");
		}
		fclose(file);
		all_ngram = strlen(content) - ngram + 1;
		even = all_ngram % 2 == 0;
		printf("content: %s\n", content); // myname...
		printf("all_ngram: %d\n", all_ngram);
		printf("even: %d\n", even);

		int all_instruction = all_ngram / core_num;
		if (all_ngram % core_num != 0)
		{
			all_instruction++;
		}
		all_instruction *= instruction_num;
		// printf("all_instruction: %d\n", all_instruction);

		makeArray(&src_tmp, core_num, all_instruction);
		makeArray(&ascii_array, all_ngram, ngram);
		for (int i = 0; i < core_num; i++)
		{
			for (int j = 0; j < all_instruction; j++)
			{
				src_tmp[i][j] = 0;
			}
		}
		for (int i = 0; i < all_ngram; i++)
		{
			for (int j = 0; j < ngram; j++)
			{
				ascii_array[i][j] = (unsigned char)(content[i + j]) - 97;
			}
		}
		// コード---------------------------------------------

		int instruction = 0;
		int core = 0;
		for (int i = 0; i < all_ngram; i++)
		{
			// 1
			uint16_t addr = ascii_array[i][0];
			uint16_t inst = get_bit(1, 1, addr);
			src_tmp[core][instruction] = inst;
			instruction++;

			// 10
			inst = get_bit(0, 10, 0);
			src_tmp[core][instruction] = inst;
			instruction++;

			// 2
			addr = ascii_array[i][1];
			inst = get_bit(1, 2, addr);
			src_tmp[core][instruction] = inst;
			instruction++;

			// 7
			inst = get_bit(0, 7, 0);
			src_tmp[core][instruction] = inst;
			instruction++;

			// 10
			inst = get_bit(0, 10, 0);
			src_tmp[core][instruction] = inst;
			instruction++;

			// 2
			addr = ascii_array[i][2];
			inst = get_bit(1, 2, addr);
			src_tmp[core][instruction] = inst;
			instruction++;

			// 3
			inst = get_bit(0, 3, 0);
			src_tmp[core][instruction] = inst;
			instruction++;

			// 7
			inst = get_bit(0, 7, 0);
			src_tmp[core][instruction] = inst;
			instruction++;

			// 8 or 9
			if (i == (all_ngram - 1))
			{
				inst = get_bit(0, 9, 0);
				src_tmp[core][instruction] = inst;
				instruction++;
			}
			else
			{
				inst = get_bit(0, 8, 0);
				src_tmp[core][instruction] = inst;
				instruction++;
			}

			if (core != (core_num - 1))
			{
				instruction -= instruction_num;
			}

			core = (core + 1) % core_num;
		}

		printf("\n");
		int flag = 0;
		int mass = 1;
		for (int j = 0; j < all_instruction; j++)
		{
			if (flag == 0)
			{
				printf("命令の塊%d\n", mass);
				mass++;
			}
			for (int i = 0; i < core_num; i++)
			{
				printf("%7d ", src_tmp[i][j]);
			}
			flag++;
			if (flag == instruction_num)
			{
				printf("\n");
				flag = 0;
			}
			printf("\n");
		}

		// ---------------------------------------------
		freeArray(&ascii_array, ngram);
		freeArray(&src_tmp, core_num);
		printf("\n\n");
	}

	return 0;
}