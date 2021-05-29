#include<stdio.h>
#include<stdlib.h>
int zdy()
{
	int i, k, r, x, y;
	if (scanf_s("%d%d", &x, &y) == EOF)
	{
		r = 0;
		return r;
	}
	if (x < y)
	{
		i = x;
		k = y;
	}
	else
	{
		i = y;
		k = x;
	}
	for (; i > 0; i = i - 1)
	{
		if (x % i == 0 && y % i == 0)
		{
			printf("%d ", i);
			break;
		}
	}
	for (; ; k = k + 1)
	{
		if (k % y == 0 && k % x == 0)
		{
			printf("%d", k);
			r = 1;
			return r;
		}
	}
	return y;
}
int main()
{
	int d;
	for (;;)
	{
		d = zdy();
		if (d == 0)
		{
			break;
		}
		printf("\n");
	}
	return 0;
}