#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void trim(char *text)
{
	int i = 0, j = 0;

	while (*(text + i) != '\0')
	{
		if (*(text + i) != ' ')
		{
			*(text + j) = *(text + i);
			j++;
		}
		i++;
	}
	*(text + j) = '\0';
}

int main(void)
{

	for (int i = 0; i < 26; i++)
	{
		// CSVファイル（data.csv）を開く
		FILE *file = fopen("isolet.data", "rt");

		char buf[12];
		snprintf(buf, 12, "label%d.txt", i);
		FILE *fp = fopen(buf, "w");

		int tmp_data[617];
		// ここにCSVデータの読み込み処理
		char Lines[10000];
		// ここで作業
		while (fgets(Lines, 10000, file) != NULL)
		{
			/* 最初に見つかった区切り文字（","）に "\0" を挿入する */
			trim(Lines);
			int tmp_num = 0;

			char *tp = strtok(Lines, ",");
			if (-1 <= atof(tp) && atof(tp) <= -0.8)
			{
				tmp_data[tmp_num] = 0;
			}
			else if (-0.8 < atof(tp) && atof(tp) <= -0.6)
			{
				tmp_data[tmp_num] = 1;
			}
			else if (-0.6 < atof(tp) && atof(tp) <= -0.4)
			{
				tmp_data[tmp_num] = 2;
			}
			else if (-0.4 < atof(tp) && atof(tp) <= -0.2)
			{
				tmp_data[tmp_num] = 3;
			}
			else if (-0.2 < atof(tp) && atof(tp) <= 0)
			{
				tmp_data[tmp_num] = 4;
			}
			else if (0 < atof(tp) && atof(tp) <= 0.2)
			{
				tmp_data[tmp_num] = 5;
			}
			else if (0.2 < atof(tp) && atof(tp) <= 0.4)
			{
				tmp_data[tmp_num] = 6;
			}
			else if (0.4 < atof(tp) && atof(tp) <= 0.6)
			{
				tmp_data[tmp_num] = 7;
			}
			else if (0.6 < atof(tp) && atof(tp) <= 0.8)
			{
				tmp_data[tmp_num] = 8;
			}
			else if (0.8 < atof(tp) && atof(tp) <= 1)
			{
				tmp_data[tmp_num] = 9;
			}
			while ((tp = strtok(NULL, ",")))
			{
				tmp_num++;
				if (tmp_num == 617)
				{
					if (i == atoi(tp) - 1)
					{
						for (int j = 0; j < 617; j++)
						{
							fprintf(fp, "%d", tmp_data[j]);
						}
						// printf("Number: %d\n", atoi(tp));
					}
				}
				else
				{
					if (-1 <= atof(tp) && atof(tp) <= -0.8)
					{
						tmp_data[tmp_num] = 0;
					}
					else if (-0.8 < atof(tp) && atof(tp) <= -0.6)
					{
						tmp_data[tmp_num] = 1;
					}
					else if (-0.6 < atof(tp) && atof(tp) <= -0.4)
					{
						tmp_data[tmp_num] = 2;
					}
					else if (-0.4 < atof(tp) && atof(tp) <= -0.2)
					{
						tmp_data[tmp_num] = 3;
					}
					else if (-0.2 < atof(tp) && atof(tp) <= 0)
					{
						tmp_data[tmp_num] = 4;
					}
					else if (0 < atof(tp) && atof(tp) <= 0.2)
					{
						tmp_data[tmp_num] = 5;
					}
					else if (0.2 < atof(tp) && atof(tp) <= 0.4)
					{
						tmp_data[tmp_num] = 6;
					}
					else if (0.4 < atof(tp) && atof(tp) <= 0.6)
					{
						tmp_data[tmp_num] = 7;
					}
					else if (0.6 < atof(tp) && atof(tp) <= 0.8)
					{
						tmp_data[tmp_num] = 8;
					}
					else if (0.8 < atof(tp) && atof(tp) <= 1)
					{
						tmp_data[tmp_num] = 9;
					}
				}
			}
		}
		fclose(fp);
		fclose(file);
	}

	return 0;
}