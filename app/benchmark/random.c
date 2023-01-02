#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "hyper_vector.h"

int main(int argc, char const *argv[])
{
	hv_t **item_memory = hv_make_imem(1024);

	hv_free_array(item_memory, 1024);

	return 0;
}