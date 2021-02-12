#include <stdio.h>
#include <locale.h>
#include <wchar.h>
#include <assert.h>
#include <stdlib.h>
#include <sys\stat.h>

typedef struct
{
	wchar_t *symbol;
}LINE;

typedef struct
{
	LINE *line;
	int numOfLines;
}TEXT;

int NumOfLines(int *fileArr, int length);

int MaxLength(int *fileArr, int length);

TEXT ReadText(char *path);

void StrSort(TEXT text);

void StrSwap(wchar_t **str1, wchar_t **str2);

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

int NumOfLines(int *fileArr, int length)
{
	int num = 0;
	for(int i = 0; i < length; i++)
	{
		if(fileArr[i] == '\n')
			num++;
	}
	return num;
}

int MaxLength(int *fileArr, int length)
{
	int max = 0, num = 0;
	for(int i = 0; i < length; i++)
	{
		num++;
		if(fileArr[i] == '\n')
		{
			if(max < num)
				max = num;
			num = 0;
		}
	}
	return max;
}

TEXT ReadText(char *path)
{
	FILE *file;
	file = fopen(path, "r");
	if(file == NULL)
		printf("FILE NOT FOUND");
	assert(file != NULL);
	struct stat statbuf;
	fstat(fileno(file), &statbuf);
	int length = statbuf.st_size;
	int fileArr[length];
	int c, i = 0;
	while((c = getc(file)) != EOF)
	{
		fileArr[i++] = c;
	}
	length = i;
	fclose(file);
	
	TEXT text;
	text.numOfLines = NumOfLines(fileArr, length);
	int maxLength = MaxLength(fileArr, length);
	text.line = malloc(sizeof(text.line) * text.numOfLines);
	for(int n = 0; n < text.numOfLines; n++)
		text.line[n].symbol = malloc(sizeof(text.line[n].symbol) * maxLength);
	int k = 0, j = 0;
	for(int i = 0; i < length; i++)
	{
			text.line[k].symbol[j++] = fileArr[i];
			if(fileArr[i] == '\n')
			{
				k++;
				j = 0;
			}
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
				StrSwap(&text.line[j - 1].symbol, &text.line[j].symbol);
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
	FILE *file;
	file = fopen(path, "a");
	for(int i = 0; i < text.numOfLines; i++)
	{
		int c, j = 0;
		while((c = text.line[i].symbol[j]) != '\n')
		{
			putc(c, file);
			j++;
		}
		putc('\n', file);
	}
	fclose(file);
}