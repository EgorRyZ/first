#include <stdio.h>
#include <locale.h>
#include <wchar.h>
#include <assert.h>
#include <stdlib.h>

enum ReturnCodes
{
	FileError = -1
};

int NumOfLines(char *path);

int MaxLength(char *path);

void ReadText(char *path, wchar_t **symbol);

void StrSort(wchar_t **symbol, int numOfLines);

void StrSwap(wchar_t **str1, wchar_t **str2);

void WriteText(char *path, wchar_t **symbol, int numOfLines);

int main()
{
	setlocale(LC_ALL, "Russian");
	
	char *path1 = "C://C/yevgeniy-onegin.txt";
	char *path2 = "C://C/sorted.txt";
	
	
	int numOfLines = NumOfLines(path1);
	
	int maxLength = MaxLength(path1);
	
	wchar_t **symbol = (wchar_t**)malloc(sizeof(wchar_t*) * numOfLines);
	
	for(int i = 0; i < numOfLines; i++)
		symbol[i] = (wchar_t*)malloc(sizeof(wchar_t) * maxLength);
	
	ReadText(path1, symbol);
	
	StrSort(symbol, numOfLines);
	
	WriteText(path2, symbol, numOfLines);

	return 0;
}

int NumOfLines(char *path)
{
	FILE *file;
	file = fopen(path, "r");
	assert(file != NULL);
	int c;
	int n = 0;
	while((c = getc(file)) != EOF)
	{
		if(c == '\n')
        	n++;
	}
	fclose(file);
	return n;
}

int MaxLength(char *path)
{
	FILE *file;
	file = fopen(path, "r");
	assert(file != NULL);
	int c;
	int max = 0;
	int n = 0;
	while((c = getc(file)) != EOF)
	{
		if(c != '\n')
        	n++;
		else
		{
			if(n > max)
				max = n;
			n = 0;
		}
	}
	fclose(file);
	return max;
}

void ReadText(char *path, wchar_t **symbol)
{
	FILE *file;
	file = fopen(path, "r");
	assert(file != NULL);
	int c, i = 0, j = 0;
	while((c = getc(file)) != EOF)
	{
		*(*(symbol + i) + j) = c;
		j++;
		if(c == '\n')
		{
			i++;
			j = 0;
		}
	}
	fclose(file);
}

void StrSort(wchar_t **symbol, int numOfLines)
{
	assert(symbol != NULL);
	for(int i = 0; i < numOfLines - 1; i++)
	{
		for(int j = 1; j < numOfLines - i; j++)
		{
			int k = 0;
			while(1)
			{	
				if(*(*(symbol + j - 1) + k) > *(*(symbol + j) + k) || *(*(symbol + j) + k) == '\n')
				{
					StrSwap(symbol + j - 1, symbol + j);
					break;
				}
				if(*(*(symbol + j - 1) + k) < *(*(symbol + j) + k) || *(*(symbol + j - 1) + k) == '\n')
				{
					break;
				}
				k++;
			}
		}
	}	
}

void StrSwap(wchar_t **str1, wchar_t **str2)
{
	wchar_t *s = *str1;
	*str1 = *str2;
	*str2 = s;
}

void WriteText(char *path, wchar_t **symbol, int numOfLines)
{
	assert(symbol != NULL);
	FILE *file;
	file = fopen(path, "a");
	for(int i = 0; i < numOfLines; i++)
	{
		int c, j = 0;
		while((c = *(*(symbol + i) + j)) != '\n')
		{
			putc(c, file);
			j++;
		}
		putc('\n', file);
	}
	fclose(file);
}






