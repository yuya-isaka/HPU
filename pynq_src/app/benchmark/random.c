#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include "hyper_vector.h"

int main(int argc, char const *argv[])
{
	const int RANNUM = 512;

	hv_t **item_memory = hv_make_imem(RANNUM);

	hv_free_array(item_memory, RANNUM);

	return 0;
}