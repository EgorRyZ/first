#include <stdio.h>
#include <math.h>
#include <assert.h>

int FindRoots(double a, double b, double c, double* x1, double* x2);

int Linear(double b, double c, double* x);

int Equal(double x, double y);

int main()
{
	printf(" Quadratic equation solver\n");
	printf(" ENTER a, b, c :\n");
	double a = 0, b = 0, c = 0;
	scanf("%lg %lg %lg", &a, &b, &c);
	double x1 = 0, x2 = 0;
	int number = FindRoots(a, b, c, &x1, &x2);
	switch (number)
	{
	case 2:
		printf("x1 = %lg  x2 = %lg\n", x1, x2);
		break;
	case 1:
		printf("x1 = %lg\n", x1);
		break;
	case 0:
		printf("NO ROOTS\n");
		break;
	case -1:
		printf("INFINITY OF ROOTS\n");
		break;
	default:
		printf("ERROR\n");
		return -1;
	}
	return 0;
}
int FindRoots(double a, double b, double c, double* x1, double* x2)
{
	assert(x1 != NULL && x2 != NULL);
	double D = b * b - 4 * a * c;
	if (!Equal(a, 0)) 
	{
		if (D >= 0)
		{
			double sqrtD = sqrt(D);
			*x1 = (-b - sqrtD) / 2 / a;
			*x2 = (-b + sqrtD) / 2 / a;
			if (Equal(D, 0))
				return 1;
			else
				return 2;
		}
		else
			return 0;		
	}
	else
		return Linear(b, c, x1);
}
int Linear(double b, double c, double* x)
{
	assert(x != NULL);
	if (Equal(b, 0))
	{
		if (Equal(c, 0))
			return -1;
		else
			return 0;
	}
	else 
	{
		*x = -c / b;
		return 1;
	}
}
int Equal(double x, double y)
{
	double e = 0.000001;
	if (fabs(x - y) < e)
		return 1;
	else
		return 0;
}