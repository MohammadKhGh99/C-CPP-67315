#include <stdio.h>

int normalize(double *data[], int len)
{
	if (len > 0)
	{
		double **p=data;
		double sum = 0.0;
		int j=0;
		while(j<len)
		{
			double a = **p;
			if (a<0)
			{
				a*=-1;
			}
			sum += a;
			p++;
			j++;
		}

		double **slow=data;
		int i=0;
		while (i<len)
		{
			double x;
			if (**slow < 0)
			{
				x = (-1) * (**slow);
			}
			else
			{
				x = **slow;
			}
			if (sum!=0)
			{
				**slow = x / sum;
			}
			else
			{
				return 0;
			}
			slow++;
			i++;
		}

		return 1;
	}
	return 0;
}

int main()
{
//	double x0 = 5, x1 = 32, x2 = 0, x3 = 0.3, x4 = 43.12;
//	double x0 = -0.3, x1 = -13, x2 = -0.3, x3 = 551, x4 = 11;
	double x0 = 0;
	double *data[] = {&x0};
	int len = 1;
	double **p=data;

	if (normalize(data, len))
	{
		int i=0;
		while (i<len)
		{
			printf("%lf\n", **p);
			p++;
			i++;
		}
		printf("Hello, World!\n");
	}

	return 0;
}