#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
double x[100005], y[100005],L[100005],R[100005];
int main()
{
	long long T,a,v,m,n,l=0;
	double t = 0,Ti;
	scanf_s("%lld", &T);
	while (T>0)
	{
		scanf_s("%lld%lld", &a, &v);
		scanf_s("%lld%lld", &n, &m);
		for (int i = 1; i <= n; i = i + 1)
		{
			scanf_s("%lf%lf", &L[i], &R[i]);
			l = l + R[i] - L[i];
		}
		for (int i = 1; i <= m; i = i + 1)
		{
			scanf_s("%lf%lf", &x[i], &y[i]);
		}
			for (int i = 1; i <= m; i = i + 1)
			{
				if (y[i] * a > 0)
				{
					Ti = (a + y[i]) * l / y[i] / v;
					t = t + Ti;
				}
			}
		
		printf("%.2lf\n", t);
		T = T - 1;
		l = 0;
		t = 0;
	}
	return 0;
}