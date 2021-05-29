#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<algorithm>
long long a[100000];

int comp(const void* a, const void* b)
{
	return *(int*)a - *(int*)b;
}
int main()
{
	long long n, k,zd,szd=0,zs,szs=0;
	scanf_s("%lld%lld", &n,&k);
	for (int i = 0; i < n; i = i + 1)
	{
		scanf_s("%lld", &a[i]);
	}
	qsort(a, n, sizeof(long long), comp);
	/*zd = a[1];
	zs = a[1];
	for (int i = 1; i <= k; i = i + 1)
	{
		for (int j = 1; j <= n; j = j + 1)
		{
			if (zd < a[j])
			{
				zd = a[j];
			}
		}
		szd = szd + zd;
	}
	for (int i = 1; i <= k; i = i + 1)
	{
		for (int j = 1; j <= n; j = j + 1)
		{
			if (zs > a[j])
			{
				zs = a[j];
			}
		}
		szs = szs + zs;
	}*/
	for (int i = 0; i < k-1; i = i + 1)
	{
		szd = szd + a[i];
	}
	for (int i = n-1; i >n-k; i = i - 1)
	{
		szs = szs + a[i];
	}
	printf("%lld", abs(szd - szs));
	return 0;
}