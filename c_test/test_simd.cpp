#include <cstdio>
#include <x86intrin.h>

void print256epu(__m256i x)
{
	printf("%lld %lld %lld %lld\n", x[3], x[2], x[1], x[0]);
}

int main(void)
{
	__m256i v1 = _mm256_set_epi64x(0, 0, 0, -2);
	__m256i v2 = _mm256_set_epi64x(0, 0, 0, -1);
	__m256i v3 = _mm256_xor_si256(v1, v2);
	print256epu(v3);
}