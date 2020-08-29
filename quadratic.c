#include <stdio.h>
#include <math.h>

int FindRoots(double a, double b, double c, double* x1, double* x2)
{
	int D = b * b - 4 * a * c;
	if (a == 0)
	{
		if (b == 0)
		{
			if (c == 0)
				return -1;
			else
				return 0;
		}
		else 
		{
			*x1 = -c / b;
			return 1;
		}		
	}
	else 
	{
		if (D >= 0)
		{
			*x1 = (-b - sqrt(D)) / 2 / a;
			*x2 = (-b + sqrt(D)) / 2 / a;
			if (D == 0)
				return 1;
			else
				return 2;
		}
		else
			return 0;		
	}
}
int main()
{
	printf(" Quadratic equation solver\n");
	printf(" ENTER a, b, c :\n");
	double a = 0, b = 0, c = 0;
	scanf_s("%lg %lg %lg", &a, &b, &c);
	double x1 = 0, x2 = 0;
	int number = FindRoots(a, b, c, &x1, &x2);
	switch (number)
	{
	case 2:
		printf("x1 = %lg  x2 = %lg\n", x1, x2);
		break;
	case 1:
		printf("x1 = %lg", x1);
		break;
	case 0:
		printf("NO ROOTS\n");
		break;
	case -1:
		printf("roots do not exist or their number is infinite");
		break;
	default:
		printf("ERROR");
		return -1;
	}
	return 0;
}
