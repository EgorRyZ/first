#include <stdio.h>
#include <locale.h>
#include <wchar.h>
#include <assert.h>
#include <stdlib.h>

enum ReturnCodes
{
	ERRORCODE = -123
};
typedef struct
{
	wchar_t *symbol;
}LINE;

typedef struct
{
	LINE *line;
}TEXT;

int NumOfLines(char *path);

int MaxLength(char *path);

void ReadText(char *path, TEXT text);

void StrSort(TEXT text, int numOfLines);

void StrSwap(wchar_t **str1, wchar_t **str2);

int Compare(wchar_t *str1, wchar_t *str2);

void WriteText(char *path, TEXT text, int numOfLines);

int main()
{
	setlocale(LC_ALL, "Russian");
	
	char *fromFile = "C://C/onegin/yevgeniy-onegin.txt";
	char *toFile = "C://C/onegin/sorted.txt";
	
	int numOfLines = NumOfLines(fromFile);
	int maxLength = MaxLength(fromFile);
	if(maxLength == ERRORCODE || numOfLines == ERRORCODE)
	{
		printf("%d", ERRORCODE);
		return ERRORCODE;
	}
	TEXT text;
	text.line = (LINE*)malloc(sizeof(LINE) * numOfLines);
	for(int i = 0; i < numOfLines; i++)
		text.line[i].symbol = (wchar_t*)malloc(sizeof(wchar_t) * maxLength);
	ReadText(fromFile, text);
	StrSort(text, numOfLines);
	WriteText(toFile, text, numOfLines);
	
	return 0;
}

int NumOfLines(char *path)
{
	FILE *file;
	file = fopen(path, "r");
	if(file == NULL)
		return ERRORCODE;
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
	if(file == NULL)
		return ERRORCODE;
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

void ReadText(char *path, TEXT text)
{
	assert(text.line != NULL);
	FILE *file;
	file = fopen(path, "r");
	assert(file != NULL);
	int c, i = 0, j = 0;
	while((c = getc(file)) != EOF)
	{
		text.line[i].symbol[j] = c;
		j++;
		if(c == '\n')
		{
			i++;
			j = 0;
		}
	}
	fclose(file);
}

void StrSort(TEXT text, int numOfLines)
{
	assert(text.line != NULL);
	for(int i = 0; i < numOfLines - 1; i++)
	{
		for(int j = 1; j < numOfLines - i; j++)
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

void WriteText(char *path, TEXT text, int numOfLines)
{
	assert(text.line != NULL);
	FILE *file;
	file = fopen(path, "a");
	for(int i = 0; i < numOfLines; i++)
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



