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
	// CSVファイル（data.csv）を開く
	FILE *file = fopen("isolet.data", "rt");
	if (!file)
	{
		// 開くのに失敗したらエラーを出力する
		perror("fopen");
		return 1;
	}

	// ここにCSVデータの読み込み処理
	char Lines[10000];
	// ここで作業
	while (fgets(Lines, 10000, file) != NULL)
	{
		/* 最初に見つかった区切り文字（","）に "\0" を挿入する */
		trim(Lines);
		char *tp = strtok(Lines, ",");
		int tmp_num = 0;
		while ((tp = strtok(NULL, ",")))
		{
			tmp_num++;
			if (tmp_num == 617)
			{
				printf("Number: %d\n", atoi(tp));
			}
			else
			{
				printf("%s\n", tp);
			}
		}
	}

	// 使い終わったらファイルを閉じる
	fclose(file);

	return 0;
}