#include <stdio.h>
#include <stdint.h>
#include <arm_neon.h>

int main()
{
	int16_t a[4] = {0, 1, 2, 3};

	// SIMDレジスタに値を移す
	int16x4_t va = vld1_s16(a);

	printf("lane[0]: %d\n", vget_lane_s16(va, 0));
	printf("lane[1]: %d\n", vget_lane_s16(va, 1));
	printf("lane[2]: %d\n", vget_lane_s16(va, 2));
	printf("lane[3]: %d\n", vget_lane_s16(va, 3));

	int16_t b[4];
	// インタリーブ
	// SIMDレジスタから値を戻す
	vst1_s16(b, va);

	for (int i = 0; i < 4; i++)
	{
		printf("b[%d]: %d\n", i, b[i]);
	}

	return 0;
}