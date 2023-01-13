#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	for (int i = 0; i < 10; i++)
	{
		char PATH[12];
		snprintf(PATH, 12, "label%d.txt", i);
		FILE *file;
		file = fopen(PATH, "r");
		char lines[3];

		int data_tmp_num = 0;
		int data_lines[150000];
		while (fgets(lines, 3, file) != NULL)
		{
			data_lines[data_tmp_num++] = atoi(lines);
		}
		fclose(file);

		printf("%d\n", data_tmp_num);
		// for (int j = 0; j < data_tmp_num; j++)
		// {
		// 	printf("%d", data_lines[j]);
		// }
	}

	return 0;
}