#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
double zf[1000005];
int tong[1000005];
int main()
{
	int len, n,max,I;
	scanf_s("%d", &n);
	for (int i = 1; i <= n; i = i + 1)
	{
		scanf_s("%lf", &zf[i]);
	}
	for (int i = 1; i <= n; i = i + 1)
	{
		for (int k = i+1; k <= n; k = k + 1)
		{
			if (zf[i] == zf[k]&&(zf[i] == (int)zf[i]))
			{
				tong[i] = tong[i] + 1;
				zf[k] = zf[k] + 0.5;
			}
		}
	}
	max = tong[1];
	for (int i = 1; i <= n; i = i + 1)
	{
		if (max <= tong[i])
		{
			max = tong[i];
			I = i;
		}
	}
	printf("%.0lf %d",zf[I],max+1 );
	return 0;
}