#include <stdio.h>
#include <math.h>
#include <assert.h>

enum ReturnCodes
{
	InfOfRoots = -1,
	ErrorCode = -111
};

#define Epsilon 0.000001

int QuadrRoots(double a, double b, double c, double* x1, double* x2);

int LinearRoot(double b, double c, double* x);

int areEqual(double x, double y);

int main()
{
	printf(" Quadratic equation solver\n");
	printf(" ENTER a, b, c :\n");
	double a = 0, b = 0, c = 0;
	int inputNum = scanf("%lg %lg %lg", &a, &b, &c);
	if (inputNum != 3)
	{
		return ErrorCode;	
	}
	double x1 = 0, x2 = 0;
	int numberOfRoots = QuadrRoots(a, b, c, &x1, &x2);
	switch (numberOfRoots)
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
	case InfOfRoots:
		printf("INFINITY OF ROOTS\n");
		break;
	default:
		printf("ERROR\n");
		return ErrorCode;
	}
	return 0;
}
int QuadrRoots(double a, double b, double c, double* x1, double* x2)
{
	assert(x1 != NULL && x2 != NULL);
	if (!areEqual(a, 0)) 
	{
	double D = b * b - 4 * a * c;
		if (D >= 0)
		{
			double sqrtD = sqrt(D);
			*x1 = (-b - sqrtD) / 2 / a;
			*x2 = (-b + sqrtD) / 2 / a;
			if (areEqual(D, 0))
			{
				return 1;
			}
			return 2;
		}
		return 0;		
	}
	return LinearRoot(b, c, x1);
}
int LinearRoot(double b, double c, double* x)
{
	assert(x != NULL);
	if (areEqual(b, 0))
	{
		if (areEqual(c, 0))
		{
			return InfOfRoots;
		}
		return 0;
	}	
	*x = -c / b;
	return 1;

}
int areEqual(double x, double y)
{
	if (fabs(x - y) < Epsilon)
	{
		return 1;
	}
	return 0;
}