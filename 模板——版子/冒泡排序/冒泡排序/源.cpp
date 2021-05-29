#include<stdio.h>
#include<stdlib.h>
int hw()
{
	int i, x = 0, y = 1, p = 4, k, j;
	char a[101] , c;
	for (i = 0; i <= 100; i = i + 1)
	{
		scanf_s("%c", &c);
		a[i] = c;
		if (a[0] == '\n')
		{
			y = 0;
			return y;
		}
		if (c == '\n')
		{
			break;
		}


	}
	for (j = 1; j <= i - 1; j = j + 1)
	{
		for (x = 1; x <= i - j; x = x + 1)
		{
			if (a[x] < a[x - 1])
			{
				p = a[x];
				a[x] = a[x - 1];
				a[x - 1] = p;
			}
		}
	}
	for (k = 0; k <= i - 1; k = k + 1)
	{
		printf("%c", a[k]);
	}
	return y;
}
int main()
{
	int d;
	for (;;)
	{
		d = hw();
		if (d == 0)
		{
			break;
		}
		printf("\n");
	}
	return 0;
}