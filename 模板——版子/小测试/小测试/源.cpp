#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
int main()
{
	long long a[25],n,x;
	scanf_s("%lld%lld", &n,&x);
	for (int i = 1; i <= n; i = i + 1)
	{
		scanf_s("%lld", &a[i]);
	}
	for (int i = 1; i <= n; i = i + 1)
	{
		if (x == a[i])
		{
			printf("%d", i - 1);
			return 0;
		}
	}
	printf("Not Found");
	return 0;
}