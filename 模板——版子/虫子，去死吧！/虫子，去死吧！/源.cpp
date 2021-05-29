#include<stdio.h>
#include<math.h>
int a[1000000], b[1000000];
int main()
{
	int T, n, m, k, i, j, g = 1, l, x, y, z, xn, yn;
	char s;
	scanf_s("%d", &T);
	scanf_s("%d%d%d", &n, &m, &k);

	for (i = 1; i <= n; i = i + 1)
	{
		for (j = 1; j <= m; j = j + 1)
		{
			scanf_s("%d", &a[g]);
			g = g + 1;
		}
	}
	for (l = 1; l <= k; l = l + 1)
	{
		scanf_s("%c,%d,%d", &s, &x, &y);
		if (s == 's')
		{
			printf("%d", a[x * y - 1]);
		}
		else if (s == 'r')
		{
			xn = x * n;
			yn = y * n;
			for (z = 1; z <= n; z = z + 1)
			{
				b[xn] = a[xn];
				a[xn] = a[yn];
				a[yn] = b[xn];
				yn = yn + 1;
				xn = xn + 1;
			}
		}
		else if (s == 'c')
		{
			xn = 0;
			yn = 0;
			for (z = 1; z <= n; z = z + 1)
			{
				b[xn] = a[xn];
				a[xn] = a[yn];
				a[yn] = b[xn];
				yn = yn + n;
				xn = xn + n;
			}
		}
	}
	return 0;
}