#include <stdio.h>
#include <stdint.h>
#include <arm_neon.h>

// 渡された32ビットのvを、バイナリでコマンドライン出力
void printb(uint64_t v)
{
	uint64_t mask = (uint64_t)1 << (64 - 1);
	do
		putchar(mask & v ? '1' : '0');
	while (mask >>= 1);
}

// printbを使いつつ整形して、バイナリをコマンドライン出力
void putb(uint64_t v)
{
	printb(v);
}

int main()
{
	// int16_t a[4] = {0, 1, 2, 3};

	// // SIMDレジスタに値を移す
	// int16x4_t va = vld1_s16(a);

	// printf("lane[0]: %d\n", vget_lane_s16(va, 0));
	// printf("lane[1]: %d\n", vget_lane_s16(va, 1));
	// printf("lane[2]: %d\n", vget_lane_s16(va, 2));
	// printf("lane[3]: %d\n", vget_lane_s16(va, 3));

	// int16_t b[4];
	// // インタリーブ
	// // SIMDレジスタから値を戻す
	// vst1_s16(b, va);

	// for (int i = 0; i < 4; i++)
	// {
	// 	printf("b[%d]: %d\n", i, b[i]);
	// }

	uint64_t input[2] = {3, 3};
	for (int i = 0; i < 2; i++)
	{
		putb(input[i]);
	}
	printf("\n");

	uint64x2_t neon = vld1q_u64(input);
	// uint64x2_t rotated = vorrq_u64(vshrq_n_u64(neon, 1), vshlq_n_u64(neon, 64 - 1));
	// uint64x2_t rotated = vshlq_n_u64(neon, 2);
	uint64x2_t rotated = vshrq_n_u64(neon, 2);

	uint64_t result[2] = {0};
	vst1q_u64(result, rotated);
	for (int i = 0; i < 2; i++)
	{
		putb(result[i]);
	}
	// putb(vget_lane_u64(rotated, 0));
	// putb(vget_lane_u64(rotated, 1));
	printf("\n");

	return 0;
}