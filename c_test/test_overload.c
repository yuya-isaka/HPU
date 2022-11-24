#include <stdio.h>
#include <stdint.h>

#define DIM 1024

#if DIM % 64 == 0
typedef uint64_t HV;
#define HV_NUM DIM / 64
#elif DIM % 32 == 0
typedef uint32_t HV;
#define HV_NUM DIM % 32
#elif DIM % 16 == 0
typedef uint16_t HV;
#define HV_NUM DIM % 16
#elif DIM % 8 == 0
typedef uint8_t HV;
#define HV_NUM DIM % 8
#endif

void print(int v) __attribute__((overloadable))
{
	printf("%d\n", v);
}
void print(uint64_t v) __attribute__((overloadable))
{
	printf("%llu\n", v);
}
void print(double v) __attribute__((overloadable))
{
	printf("%f\n", v);
}
void print(const char *v) __attribute__((overloadable))
{
	printf("%s\n", v);
}

int main(int argc, char **argv)
{
	HV tmp = 5;

	print(tmp);
	print(4.0);
	print("Hello");
	print(HV_NUM);
	return 0;
}