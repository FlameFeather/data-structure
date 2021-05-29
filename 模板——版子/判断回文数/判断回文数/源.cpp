#include<stdio.h>
#include<stdlib.h>
int hw()
{
	int i, x, y, p = 4;
	char a[101], c;
	for (i = 0; i <= 100; i = i + 1)
	{
		scanf_s("%c", &c);
		if (c == '\n')
		{
			break;
		}
		a[i] = c;
		if (a[i] == '\0')
		{
			p = 2;
			return p;
		}
	}
	x = 0;
	y = i - 1;
	for (; x < y; x = x + 1, y = y - 1)
	{
		if (a[x] != a[y])
		{
			break;
		}
	}
	if (x == 0 && y == -1)
	{
		p = 2;
		return p;
	}
	if (x < y)
	{
		p = 0;
	}
	else if (x >= y)
	{
		p = 1;
	}
	return p;
}
int main()
{
	int d;
	for (;;)
	{
		d = hw();
		if (d == 2)
		{
			return 0;
		}

		if (d == 1)
		{
			printf("Yes\n");
		}
		else if (d == 0)
		{
			printf("No\n");
		}
	}
	return 0;
}