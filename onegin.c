#include <stdio.h>
#include <locale.h>
#include <wchar.h>
#include <assert.h>
#include <stdlib.h>
#include <sys\stat.h>

typedef struct
{
	wchar_t *symbol;
	int strLength;
}LINE;

typedef struct
{
	LINE *line;
	int numOfLines;
}TEXT;

int NumOfLines(wchar_t *fileArr, int length);

TEXT ReadText(char *path);

TEXT TextStruct(wchar_t *fileArr, int length);

void StrSort(TEXT text);

void StrSwap(wchar_t **str1, wchar_t **str2);

void Swap(int *a, int *b);

int Compare(wchar_t *str1, wchar_t *str2);

void WriteText(char *path, TEXT text);

int main()
{
	setlocale(LC_ALL, "Russian");
	
	char *fromFile = "C://C/onegin/yevgeniy-onegin.txt";
	char *toFile = "C://C/onegin/sorted.txt";

	TEXT text = ReadText(fromFile);
	
	StrSort(text);
	
	WriteText(toFile, text);
	
	return 0;
}

int NumOfLines(wchar_t *fileArr, int length)
{
	int num = 0;
	for(int i = 0; i < length; i++)
	{
		if(fileArr[i] == '\n')
			num++;
	}
	return num;
}

TEXT ReadText(char *path)
{
	FILE *file = fopen(path, "r");
	if(file == NULL)
		printf("FILE NOT FOUND");
	assert(file != NULL);
	
	struct stat statbuf;
	fstat(fileno(file), &statbuf);
	int length = statbuf.st_size;
	
	wchar_t *fileArr = malloc(length * sizeof(*fileArr));
	int c = 0, i = 0;
	while((c = getc(file)) != EOF)
	{
		fileArr[i++] = c;
	}
	length = i;
	fclose(file);
	
	TEXT text = TextStruct(fileArr, length);
	return text;
}

TEXT TextStruct(wchar_t *fileArr, int length)
{
	TEXT text;
	text.numOfLines = NumOfLines(fileArr, length);
	text.line = malloc(text.numOfLines * sizeof(*(text.line)));
	for(int i = 0; i < text.numOfLines; i++)
		text.line[i].strLength = 0;
	
	int strnum = 0;
	for(int i = 0; i < length; i++)
	{
		text.line[strnum].strLength++;
		if(fileArr[i] == '\n')
			strnum++;
	}
	
	int p = 0;
	for(int i = 0; i < text.numOfLines; i++)
	{
		text.line[i].symbol = fileArr + p;
		p += text.line[i].strLength;
	}
	return text;
}

void StrSort(TEXT text)
{
	assert(text.line != NULL);
	for(int i = 0; i < text.numOfLines - 1; i++)
	{
		for(int j = 1; j < text.numOfLines - i; j++)
		{
			if(Compare(text.line[j - 1].symbol, text.line[j].symbol))
			{
				StrSwap(&text.line[j - 1].symbol, &text.line[j].symbol);
				Swap(&text.line[j - 1].strLength, &text.line[j].strLength);
			}
		}
	}	
}

void StrSwap(wchar_t **str1, wchar_t **str2)
{
	assert(*str1 != NULL);
	assert(*str2 != NULL);
	wchar_t *s = *str1;
	*str1 = *str2;
	*str2 = s;
}

void Swap(int *a, int *b)
{
	assert(a != NULL);
	assert(b != NULL);
	int t = *a;
	*a = *b;
	*b = t;
}

int Compare(wchar_t *str1, wchar_t *str2)
{
	assert(str1 != NULL);
	assert(str2 != NULL);
	int k = 0;
	while(1)
	{	
		if(str1[k] > str2[k] || str2[k] == '\n')
			return 1;
		if(str1[k] < str2[k] || str1[k] == '\n')
			return 0;
		k++;
	}		
}

void WriteText(char *path, TEXT text)
{
	assert(text.line != NULL);
	FILE *file = fopen(path, "a");
	for(int i = 0; i < text.numOfLines; i++)
	{
		for(int j = 0; j < text.line[i].strLength; j++)
		{
			putc(text.line[i].symbol[j], file);
		}
	}
	
	fclose(file);
}