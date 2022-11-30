#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "hyper_vector.h"

extern int32_t bound_buff[HV_DIM];

static uint32_t xor128(int reset)
{
	static uint32_t x = 123456789;
	static uint32_t y = 362436069;
	static uint32_t z = 521288629;
	static uint32_t w = 88675123;

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

void initHV(void)
{
	memset(bound_buff, 0, sizeof(int32_t) * HV_DIM);
}

// -----------------------------------------------------------------------

static uint32_t right_perm_31(uint32_t *over_hv, uint32_t perm_num)
{
	uint32_t remain_hv = *over_hv >> perm_num;
	uint32_t mask = (1 << perm_num) - 1;
	*over_hv = (*over_hv & mask) << (32 - perm_num);
	return remain_hv;
}

static void right_perm(hv_t new_hv[HV_NUM], hv_t base_hv[HV_NUM], size_t perm_num)
{
	hv_t result_hv[HV_NUM];
	memset(result_hv, 0, sizeof(result_hv));

	uint32_t origin_hv = base_hv[0];
	uint32_t origin_hv_perm = right_perm_31(&origin_hv, perm_num);

	result_hv[0] |= origin_hv_perm;
	result_hv[HV_NUM - 1] |= origin_hv;

	for (int i = 1; i < HV_NUM; i++)
	{
		uint32_t origin_hv = base_hv[i];
		uint32_t origin_hv_perm = right_perm_31(&origin_hv, perm_num);

		result_hv[i] |= origin_hv_perm;
		result_hv[i - 1] |= origin_hv;
	}
	for (int i = 0; i < HV_NUM; i++)
	{
		new_hv[i] = result_hv[i];
	}
}

static uint32_t left_perm_31(uint32_t *over_hv, uint32_t perm_num)
{
	uint32_t remain_hv = *over_hv << perm_num;
	uint32_t mask = UINT32_MAX << (32 - perm_num);
	*over_hv = (*over_hv & mask) >> (32 - perm_num);
	return remain_hv;
}

static void left_perm(hv_t new_hv[HV_NUM], hv_t base_hv[HV_NUM], size_t perm_num)
{
	hv_t result_hv[HV_NUM];
	memset(result_hv, 0, sizeof(result_hv));

	uint32_t origin_hv = base_hv[HV_NUM - 1];
	uint32_t origin_hv_perm = left_perm_31(&origin_hv, perm_num);

	result_hv[HV_NUM - 1] |= origin_hv_perm;
	result_hv[0] |= origin_hv;

	for (int i = HV_NUM - 2; i >= 0; i--)
	{
		uint32_t origin_hv = base_hv[i];
		uint32_t origin_hv_perm = left_perm_31(&origin_hv, perm_num);

		result_hv[i] |= origin_hv_perm;
		result_hv[i + 1] |= origin_hv;
	}
	for (int i = 0; i < HV_NUM; i++)
	{
		new_hv[i] = result_hv[i];
	}
}

hv_t *makeHV(void)
{
	hv_t *result = (hv_t *)calloc(HV_NUM, sizeof(hv_t));
	return result;
}

static void perm_left_right(hv_t new[HV_NUM], hv_t origin[HV_NUM], size_t perm_num, void (*perm_func)(hv_t *, hv_t *, size_t))
{
	uint32_t repeat_perm_num = perm_num / 31;
	uint32_t pre_perm_num;
	if (perm_num % 31 != 0)
	{
		pre_perm_num = perm_num % 31;
	}
	else
	{
		pre_perm_num = 31;
		repeat_perm_num--;
	}

	perm_func(new, origin, pre_perm_num);

	for (int i = 0; i < repeat_perm_num; i++)
	{
		perm_func(new, new, 31);
	}
}

hv_t *perm(hv_t origin[HV_NUM], hv_t perm_num)
{
	hv_t *new = makeHV();

	if (perm_num == 0)
	{
		memcpy(new, origin, sizeof(hv_t) * HV_NUM);
		return new;
	}
	else if (perm_num >= HV_DIM)
	{
		perror("Failed: permutation");
		exit(1);
	}

	if (perm_num > (HV_DIM / 2))
	{
		perm_num = HV_DIM - perm_num;
		perm_left_right(new, origin, perm_num, left_perm);
	}
	else
	{
		perm_left_right(new, origin, perm_num, right_perm);
	}

	return new;
}

void bound(hv_t encoded_hv[HV_NUM])
{
	// reductionを使って並列化する必要性あり
	// https://www.isus.jp/products/c-compilers/32-openmp-traps/
	uint32_t index_assign = HV_NUM - 1;
	for (int i = 0; i < HV_NUM; i++)
	{
		hv_t hv = encoded_hv[i];
		uint32_t mask = 1;
		for (int j = 0; j < 32; j++)
		{
			uint32_t index = index_assign * 32 + j;
			bound_buff[index] += (mask & hv ? -1 : 1);
			mask <<= 1;
		}
		index_assign--;
	}
}

hv_t *bound_extract(void)
{
	hv_t *bound_hv = makeHV();
	uint32_t mask = 1 << (32 - 1);
	uint32_t index_assign = HV_NUM - 1;
	for (int i = 0; i < HV_NUM; i++)
	{
		uint32_t hv = 0;
		for (int j = 0; j < 32; j++)
		{
			uint32_t index = i * 32 + j;
			uint32_t sign_bit = (bound_buff[index] & mask ? 1 : 0);
			hv += (sign_bit << j);
		}
		bound_hv[index_assign--] = hv;
	}

	return bound_hv;
}

hv_t *bind(hv_t src1[HV_NUM], hv_t src2[HV_NUM])
{
	hv_t *dst = makeHV();
	for (int i = 0; i < HV_NUM; i++)
	{
		dst[i] = src1[i] ^ src2[i];
	}

	return dst;
}

void freeHV(hv_t *data)
{
	free(data);
}

hv_t **makeArrayHV(size_t size)
{
	hv_t **result = (hv_t **)calloc(size, sizeof(hv_t *));
	for (int i = 0; i < size; i++)
	{
		result[i] = makeHV();
	}

	return result;
}

void freeArrayHV(hv_t **data, size_t size)
{
	for (int i = 0; i < size; i++)
	{
		freeHV(data[i]);
	}
	free(data);
}

hv_t **makeItemMemory(size_t size)
{
	hv_t **result = makeArrayHV(size);

	xor128(1);

	for (uint32_t i = 0; i < size; i++)
	{
		for (uint32_t j = 0; j < HV_NUM; j++)
		{
			uint32_t tmp = 0;
			if (i == 0 && j == 0)
			{
				tmp = 88675123;
			}
			else
			{
				tmp = xor128(0);
			}
			result[i][j] = tmp;
		}
	}

	return result;
}

void copyHV(hv_t *dst, hv_t *src)
{
	memcpy(dst, src, sizeof(hv_t) * HV_NUM);
	return;
}