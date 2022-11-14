
#include <stdio.h>
#include <stdlib.h> /* exit(  ) free(  ) malloc(  ) に必要 */
#include <string.h> /* strcpy(  ) strcmp(  ) に必要 */

#define HASHSIZE 40	   /* ハッシュテーブルの大きさ */
#define MAX_KW_LEN 256 /* キーワードの最大の長さ */
#define NUM_KW 23	   /* キーワードの数 */

#define TRUE 1
#define FALSE 0

struct list
{
	char keyword[MAX_KW_LEN];
	struct list *next; /* 次の list へのポインタ */
};

struct list *hashtable[HASHSIZE]; /* ハッシュテーブル */

/* キーワード ( Ｃの予約語 ) */
static char kw[NUM_KW][MAX_KW_LEN] = {
	"auto", "break", "double",
	"enum", "char", "continue", "extern", "float", "for", "int",
	"long", "register", "short", "signed", "static",
	"struct", "typedef", "union", "unsigned", "return",
	"void", "volatile", "while"};

int Hash(char *key);		/* 0 から HASHSIZE のハッシュ値を返す */
void InitHTable(void);		/* キーワードをハッシュテーブルに登録 */
int FindKeyWord(char *key); /* ハッシュテーブルに登録済みか調べる */
void ListKeyWord(void);		/* ハッシュ値とキーワードを一覧表示 */
void FreeKeyWord(void);		/* malloc(  ) で割り付けたメモリを解放 */
int main(void);

/* 0 から HASHSIZE - 1 のハッシュ値を返す */
int Hash(char *key)
{
	int hashval = 0;

	while (*key != '\0')
		hashval += *key++;

	return (hashval % HASHSIZE);
}

/* キーワードをハッシュテーブルに登録 */
void InitHTable(void)
{
	int i;
	struct list *p, *q;
	int hashval;

	for (i = 0; i < NUM_KW; i++)
	{
		if ((FindKeyWord(kw[i])) == FALSE)
		{ /* 登録されていなかったら */
			/* メモリを割り付ける */
			if ((p = (struct list *)malloc(sizeof(struct list))) == NULL)
			{
				fprintf(stderr, "メモリ不足です。\n");
				exit(2);
			}

			strcpy((*p).keyword, kw[i]);
			hashval = Hash(kw[i]); /* ハッシュ値を求めて */

			if (hashtable[hashval] == NULL)
			{							/* 未登録なら */
				hashtable[hashval] = p; /* p の指すアドレスを登録 */
				p->next = NULL;			/* リストの末尾に NULL を追加 */
			}
			else
			{ /* 既に登録していたら */
				q = hashtable[hashval];
				while (q->next != NULL) /* データがなくなるまで */
					q = q->next;		/* リストをたどる */
				q->next = p;			/* リストの末尾に p の指すアドレスを登録 */
				p->next = NULL;			/* その末尾に NULL を追加 */
			}
		}
	}
}

/* ハッシュテーブルに登録済みか調べる */
int FindKeyWord(char *key)
{
	struct list *p;

	for (p = hashtable[Hash(key)]; p != NULL; p = p->next)
		if (!strcmp(key, (*p).keyword)) /* 登録済みなら */
			return (TRUE);				/* TRUE を返す */

	return (FALSE); /* 未登録ならFALSE を返す */
}

/* ハッシュ値とキーワードを一覧表示 */
void ListKeyWord(void)
{
	int i;
	struct list *p;

	for (i = 0; i < HASHSIZE; i++)
		for (p = hashtable[i]; p != NULL; p = p->next) /* p が NULL でなければ */
													   /* ハッシュ値とキーワードを表示 */
			printf("予約語:%s ハッシュ値:%d:\n", (*p).keyword, Hash((*p).keyword));
}

/* malloc(  ) で割り付けたメモリを解放 */
void FreeKeyWord(void)
{
	int i;
	struct list *p, *q;

	for (i = 0; i < HASHSIZE; i++)
		for (p = hashtable[i]; p != NULL;)
		{				 /* p が NULL でなければ */
			q = p->next; /* p->next を保存 */
			free(p);	 /* メモリを解放 */
			p = q;		 /* p->next を p に代入 */
		}
}

int main(void)
{
	int i;

	InitHTable();
	ListKeyWord();

	for (i = 0; i < 4; i++)
	{
		char *word = "short";

		if ((FindKeyWord(word)) == TRUE)
			printf("%s は登録済みです。\n", word);
		else
			printf("%s は未登録です。\n", word);
	}
	FreeKeyWord();
	return 0;
}