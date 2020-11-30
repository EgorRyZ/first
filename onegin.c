#include <stdio.h>
#include <locale.h>
#include <wchar.h>
#include <assert.h>

enum ReturnCodes
{
	FileError = -1
};

int NumOfLines(char *path);

void Sort(char *path, int lineNumber[], int numOfLines);

void Swap(int *a, int *b);

void FindStr(FILE *file, int strnum);

void OriginalOrder(int lineNumber[], int numOfLines);

void WriteText(char *path1, char *path2, int lineNumber[], int numOfLines);

int main()
{
	setlocale(LC_ALL, "Russian");
	char *path1 = "C://C/c/yevgeniy-onegin.txt";
	char *path2 = "C://C/sorted.txt";
	
	int numOfLines = NumOfLines(path1);
	
	int lineNumber[numOfLines];

	OriginalOrder(lineNumber, numOfLines);
	
	Sort(path1, lineNumber, numOfLines);
	
	WriteText(path1, path2, lineNumber, numOfLines);

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

void OriginalOrder(int lineNumber[], int numOfLines)
{
	assert(lineNumber != NULL);
	for(int i = 0; i < numOfLines; i++)
	{
		lineNumber[i] = i;
	}
}

void FindStr(FILE *file, int strnum)
{
	assert(file != NULL);
	int c;
	int n = 0;
	while((c = getc(file)) != EOF)
	{
		if(c == '\n')
			n++;
		if(n == strnum)
			break;
	}
}

void Swap(int *a, int *b)
{
	int t = *a;
	*a = *b;
	*b = t;	
}

void Sort(char *path, int lineNumber[], int numOfLines)
{
	assert(fopen(path, "r") != NULL);
	assert(lineNumber != NULL);
	for(int k = numOfLines - 1; k > 0; k--)
	{
		for(int j = numOfLines - 1; j > numOfLines - 1 - k; j--)
		{
			FILE *file1;
			file1 = fopen(path, "r");
			FILE *file2;
			file2 = fopen(path, "r");
			FindStr(file1, lineNumber[j - 1]);
			FindStr(file2, lineNumber[j]);
			int c1, c2;
			while((c1 = getc(file1)) != EOF && (c2 = getc(file2)) != EOF)
			{
				if(c1 > c2 || c2 == '\n')
				{
					Swap(&lineNumber[j - 1], &lineNumber[j]);
					break;
				}
				if(c1 < c2 || c1 == '\n')
				{
					break;
				}
			}
			fclose(file1);
			fclose(file2);
		}
	}
}

void WriteText(char *path1, char *path2, int lineNumber[], int numOfLines)
{
	assert(fopen(path1, "r") != NULL);
	assert(lineNumber != NULL);
	int c;
	FILE *file2;
	file2 = fopen(path2, "a");
	for(int i = 0; i < numOfLines; i++)
	{
		FILE *file1;
		file1 = fopen(path1, "r");
		FindStr(file1, lineNumber[i]);
		while((c = getc(file1)) != '\n')
			putc(c, file2);
		putc('\n', file2);
		fclose(file1);
	}	
	fclose(file2);
}
