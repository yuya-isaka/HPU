
// ユーザに使ってもらう関数たち
// HDC
// generate
// shift
// xor
// move
// lastore
// store
// finish
// even

// ↓

// 欲しいのは
// ・ランダム生成する数 （generate関数でわかる）
// ・HDC演算の実行回数 (HDC関数から取得)
// ・コアの数 (HDC関数から取得)
// ・命令の数　（リンクドリストで作るならいらない？）
// ・計算する総数が偶数か奇数か　（even関数から取得）
// ・asm_array

// それぞれの関数から何らかのテキスト（setting.json）に吐き出すように設定する。

int main(int argc, char const *argv[])
{
	puts("\n  -------------------------------------- HDC Program start ------------------------------------\n");

	// 学習対象の個数（英語、フランス語）
	int train_num = 2;
	const char *train_path[] = {"data/decorate/en", "data/decorate/fr"};

	int core_num = 16;
	HDC(train_num, core_num);

	// 割り当てたいキーワードをユーザが選定
	generate(27); // 27個のハイパーベクトルとキーワードがセットになったitem_memoryが生成

	for (int i = 0; i < train_num; i++)
	{
		const char *path = train_path[i];
		// ファイルオープン
		FILE *file;
		file = fopen(path, "r");
		if (file == NULL)
		{
			perror("  Failed to open file");
			exit(1);
		}

		int ch;
		int num = 0;
		while (((ch = fgetc(file)) != EOF) && ((ch = fgetc(file) != 255))) // ubuntu:EOF == -1,  petalinux:EOF == 255
		{
			num++;
		}
		fseek(file, 0, SEEK_SET);
		char *train_data = (char *)calloc(num, sizeof(char));
		fread(train_data, sizeof(char), num, file);
		fclose(file);

		// ngramの数（パラメータから計算）
		const int NGRAM = 3;
		int all_ngram = strlen(train_data) - NGRAM + 1;
		even(all_ngram);

		int core_num ＝ 0;
		for (int i = 0; i < all_ngram; i++)
		{
			for (int j = 0; j < NGRAM; j++)
			{
				int addr = train_data[i + j] - 97;
				shift(addr, j, core_num);

				// 0番目以外はxor
				if (j != 0)
				{
					xor(reg1, reg2, core_num);
				}

				// 最後以外はmove
				if (j != N - 1)
				{
					move(core_num);
				}
			}

			// 最後の命令はlastore
			if (i == (train_size - N))
			{
				lastore(core_num);
			}
			// 最後以外の命令はstore
			else
			{
				store(core_num);
			}

			core_num = (core_num + 1) % CORE_MAX;
		}

		finish(i);
	}

	puts("\n  --------------------------------------- HDC Program end -------------------------------------\n");

	return 0;
}
