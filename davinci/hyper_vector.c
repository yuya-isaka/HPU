
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "hyper_vector.h"

#ifdef SIMD
#include <arm_neon.h>
#endif

#ifdef OPENMP
#include <omp.h>
#endif

#ifdef OPENMP
extern hv_int_t **hv_bound_buff;
#else
extern hv_int_t *hv_bound_buff;
#endif

void hv_init(void)
{
#ifdef OPENMP
	hv_bound_buff = (hv_int_t **)calloc(omp_get_max_threads(), sizeof(hv_int_t *));
	for (uint32_t i = 0; i < omp_get_max_threads(); i++)
	{
		hv_bound_buff[i] = (hv_int_t *)calloc(HV_DIM, sizeof(hv_int_t));
	}
#else
	hv_bound_buff = (hv_int_t *)calloc(HV_DIM, sizeof(hv_int_t));
#endif
}

void hv_finish(void)
{
#ifdef OPENMP
	for (uint32_t i = 0; i < omp_get_max_threads(); i++)
	{
		free(hv_bound_buff[i]);
	}
#endif
	free(hv_bound_buff);
}

hv_t *hv_make(void)
{
	hv_t *result = (hv_t *)calloc(HV_NUM, sizeof(hv_t));
	if (result == NULL)
	{
		perror("  Failed: calloc");
		exit(1);
	}

	return result;
}

void hv_free(hv_t *data)
{
	free(data);
}

hv_t **hv_make_array(const uint32_t size)
{
	hv_t **result = (hv_t **)calloc(size, sizeof(hv_t *));
	if (result == NULL)
	{
		perror("  Failed: calloc");
		exit(1);
	}

	for (uint32_t i = 0; i < size; i++)
	{
		result[i] = hv_make();
	}
	return result;
}

void hv_free_array(hv_t **data, const uint32_t size)
{
	for (uint32_t i = 0; i < size; i++)
	{
		hv_free(data[i]);
	}
	free(data);
}

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

hv_t **hv_make_imem(const uint32_t size)
{
	xor128(1);

	hv_t **result = hv_make_array(size);

	for (uint32_t i = 0; i < size; i++)
	{
		for (uint32_t j = 0; j < HV_NUM; j++)
		{
#ifdef HV64
			union
			{
				struct
				{
					uint32_t data_0;
					uint32_t data_1;
				};
				hv_t data;
			} conv;
			if (i == 0 && j == 0)
			{
				conv.data_0 = 88675123;
			}
			else
			{
				conv.data_0 = xor128(0);
			}
			conv.data_1 = xor128(0);
			result[i][j] = conv.data;
#else
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
#endif
		}
	}
	return result;
}

void hv_copy(hv_t *dst, hv_t *src)
{
	memcpy(dst, src, sizeof(hv_t) * HV_NUM);
	return;
}

hv_t *hv_bind(hv_t src1[HV_NUM], hv_t src2[HV_NUM])
{
	hv_t *dst = hv_make();
#ifdef SIMD
#ifdef HV64
	for (uint32_t i = 0; i < HV_NUM; i += 2)
	{
		hv_t src1_128[2] = {src1[i], src1[i + 1]};
		uint32x4_t hv_neon_src1 = vld1q_u64(src1_128);
		hv_t src2_128[2] = {src2[i], src2[i + 1]};
		uint32x4_t hv_neon_src2 = vld1q_u64(src2_128);

		uint32x4_t hv_neon_dst = veorq_u64(hv_neon_src1, hv_neon_src2);

		hv_t dst_128[2];
		vst1q_u64(dst_128, hv_neon_dst);
		for (uint32_t j = 0; j < 2; j++)
		{
			dst[i + j] = dst_128[j];
		}
	}
#else
	for (uint32_t i = 0; i < HV_NUM; i += 4)
	{
		hv_t src1_128[4] = {src1[i], src1[i + 1], src1[i + 2], src1[i + 3]};
		uint32x4_t hv_neon_src1 = vld1q_u32(src1_128);
		hv_t src2_128[4] = {src2[i], src2[i + 1], src2[i + 2], src2[i + 3]};
		uint32x4_t hv_neon_src2 = vld1q_u32(src2_128);

		uint32x4_t hv_neon_dst = veorq_u32(hv_neon_src1, hv_neon_src2);

		hv_t dst_128[4];
		vst1q_u32(dst_128, hv_neon_dst);
		for (uint32_t j = 0; j < 4; j++)
		{
			dst[i + j] = dst_128[j];
		}
	}
#endif
#else
	for (uint32_t i = 0; i < HV_NUM; i++)
	{
		dst[i] = src1[i] ^ src2[i];
	}
#endif

	return dst;
}

static hv_t perm_element_right(hv_t *origin_hv, const uint32_t perm_num)
{
	hv_t remain_hv = *origin_hv >> perm_num;
	*origin_hv = *origin_hv << (ELEMENT_SIZE - perm_num);
	return remain_hv;
}

static hv_t *perm_right(hv_t base_hv[HV_NUM], const uint32_t perm_num)
{
	hv_t *result_hv = hv_make();

	hv_t origin_hv = base_hv[0];
	hv_t origin_hv_perm = perm_element_right(&origin_hv, perm_num);

	result_hv[0] |= origin_hv_perm;
	result_hv[HV_NUM - 1] |= origin_hv;

	// SIMD化（新しいperm定義）
	for (uint32_t i = 1; i < HV_NUM; i++)
	{
		hv_t origin_hv = base_hv[i];
		hv_t origin_hv_perm = perm_element_right(&origin_hv, perm_num);

		result_hv[i] |= origin_hv_perm;
		result_hv[i - 1] |= origin_hv;
	}

	return result_hv;
}

static hv_t perm_element_left(hv_t *origin_hv, const uint32_t perm_num)
{
	hv_t remain_hv = *origin_hv << perm_num;
	*origin_hv = *origin_hv >> (ELEMENT_SIZE - perm_num);
	return remain_hv;
}

static hv_t *perm_left(hv_t base_hv[HV_NUM], const uint32_t perm_num)
{
	hv_t *result_hv = hv_make();

	hv_t origin_hv = base_hv[HV_NUM - 1];
	hv_t origin_hv_perm = perm_element_left(&origin_hv, perm_num);

	result_hv[HV_NUM - 1] |= origin_hv_perm;
	result_hv[0] |= origin_hv;

	// SIMD化（新しいperm定義）
	for (uint32_t i = HV_NUM - 2; i >= 0; i--)
	{
		hv_t origin_hv = base_hv[i];
		hv_t origin_hv_perm = perm_element_left(&origin_hv, perm_num);

		result_hv[i] |= origin_hv_perm;
		result_hv[i + 1] |= origin_hv;
	}

	return result_hv;
}

// SIMD化（新しいperm）
static hv_t *perm_select(hv_t origin[HV_NUM], const uint32_t perm_num, hv_t *(*perm_func)(hv_t *, const uint32_t))
{
	uint32_t repeat_perm_num = perm_num / (ELEMENT_SIZE - 1);
	uint32_t pre_perm_num;
	if (perm_num % (ELEMENT_SIZE - 1) != 0)
	{
		pre_perm_num = perm_num % (ELEMENT_SIZE - 1);
	}
	else
	{
		pre_perm_num = ELEMENT_SIZE - 1;
		repeat_perm_num--;
	}

	hv_t *new = perm_func(origin, pre_perm_num);

	for (uint32_t i = 0; i < repeat_perm_num; i++)
	{
		hv_t *perm_result = perm_func(new, ELEMENT_SIZE - 1);
		hv_copy(new, perm_result);
		hv_free(perm_result);
	}

	return new;
}

hv_t *hv_perm(hv_t origin[HV_NUM], const uint32_t perm_num)
{
	if (perm_num == 0)
	{
		hv_t *new = hv_make();
		memcpy(new, origin, sizeof(hv_t) * HV_NUM);
		return new;
	}
	else if (perm_num >= HV_DIM)
	{
		perror("Failed: permutation");
		exit(1);
	}

	hv_t *new = NULL;

	if (perm_num > (HV_DIM / 2))
	{
		const uint32_t perm_num_new = HV_DIM - perm_num;
		new = perm_select(origin, perm_num_new, perm_left);
	}
	else
	{
		new = perm_select(origin, perm_num, perm_right);
	}

	return new;
}

// SIMD化むずい
void hv_bound(hv_t encoded_hv[HV_NUM])
{
	uint32_t index_assign = HV_NUM - 1;
	for (uint32_t i = 0; i < HV_NUM; i++)
	{
		hv_t hv = encoded_hv[i];
		hv_t mask = (hv_t)1;
		for (uint32_t j = 0; j < ELEMENT_SIZE; j++)
		{
			uint32_t index = index_assign * ELEMENT_SIZE + j;
#ifdef OPENMP
			hv_bound_buff[omp_get_thread_num()][index] += (mask & hv ? -1 : 1);
#else
			hv_bound_buff[index] += (mask & hv ? -1 : 1);
#endif
			mask <<= 1;
		}
		index_assign--;
	}
}

// SIMD化むずい
hv_t *hv_bound_result(void)
{
#ifdef OPENMP
	hv_int_t *hv_bound_buff_result = (hv_int_t *)calloc(HV_DIM, sizeof(hv_int_t));
	for (uint32_t i = 0; i < omp_get_max_threads(); i++)
	{
		for (uint32_t j = 0; j < HV_DIM; j++)
		{
			hv_bound_buff_result[j] += hv_bound_buff[i][j];
		}
	}
#endif

	hv_t *bound_hv = hv_make();
	hv_t mask = (hv_t)1 << (ELEMENT_SIZE - 1);
	uint32_t index_assign = HV_NUM - 1;
	for (uint32_t i = 0; i < HV_NUM; i++)
	{
		hv_t hv = 0;
		for (uint32_t j = 0; j < ELEMENT_SIZE; j++)
		{
			uint32_t index = i * ELEMENT_SIZE + j;
#ifdef OPENMP
			hv_t sign_bit = (hv_bound_buff_result[index] & mask ? 1 : 0);
#else
			hv_t sign_bit = (hv_bound_buff[index] & mask ? 1 : 0);
#endif
			hv += (sign_bit << j);
		}
		bound_hv[index_assign--] = hv;
	}

#ifdef OPENMP
	free(hv_bound_buff_result);
#endif

	return bound_hv;
}

hv_t *hv_bound_batch(hv_t **batch_data, const uint32_t batch_size)
{
	hv_t *hv_result = hv_make();

#ifdef OPENMP
	uint32_t **hv_buff = (uint32_t **)calloc(omp_get_max_threads(), sizeof(uint32_t *));
	for (uint32_t i = 0; i < omp_get_max_threads(); i++)
	{
		hv_buff[i] = (uint32_t *)calloc(HV_DIM, sizeof(uint32_t));
	}
#else
	uint32_t *hv_buff = (uint32_t *)calloc(HV_DIM, sizeof(uint32_t));
#endif

#ifdef OPENMP
#pragma omp parallel for
#endif
	for (uint32_t i = 0; i < batch_size; i++)
	{
		uint32_t index_assign = HV_NUM - 1;
		for (uint32_t j = 0; j < HV_NUM; j++)
		{
			hv_t hv = batch_data[i][j];
			hv_t mask = (hv_t)1;
			for (uint32_t k = 0; k < ELEMENT_SIZE; k++)
			{
				uint32_t index = index_assign * ELEMENT_SIZE + k;
#ifdef OPENMP
				hv_buff[omp_get_thread_num()][index] += (mask & hv ? 1 : 0);
#else
				hv_buff[index] += (mask & hv ? 1 : 0);
#endif
				mask <<= 1;
			}
			index_assign--;
		}
	}

#ifdef OPENMP
	uint32_t *hv_buff_result = (uint32_t *)calloc(HV_DIM, sizeof(uint32_t));
	for (uint32_t i = 0; i < omp_get_max_threads(); i++)
	{
		for (uint32_t j = 0; j < HV_DIM; j++)
		{
			hv_buff_result[j] += hv_buff[i][j];
		}
	}

	for (uint32_t i = 0; i < omp_get_max_threads(); i++)
	{
		free(hv_buff[i]);
	}
	free(hv_buff);
#endif

	const uint32_t threshold = batch_size / 2;
	uint32_t index = HV_NUM - 1;
	uint32_t counter = 0;
	hv_t tmp_hv = 0;
	for (uint32_t i = 0; i < HV_DIM; i++)
	{
#ifdef OPENMP
		if (hv_buff_result[i] > threshold)
		{
			tmp_hv |= (hv_t)1 << counter;
		}
#else
		if (hv_buff[i] > threshold)
		{
			tmp_hv |= (hv_t)1 << counter;
		}
#endif
		counter++;
		if (counter >= ELEMENT_SIZE)
		{
			counter = 0;
			hv_result[index--] = tmp_hv;
			tmp_hv = 0;
		}
	}

#ifdef OPENMP
	free(hv_buff_result);
#else
	free(hv_buff);
#endif

	return hv_result;
}