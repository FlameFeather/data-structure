#include<stdio.h>
#include<math.h>
double fact(int n)
{
	double a = 1;
	for (int i = 1; i <= n; i++)
		a = a * i;
	return a;
}
int main()
{
	double a, b = 0.000011, s = 0;
	double esp = 0.00001;
	int i = 1;
	scanf("%lf", &a);
	while (fabs(b) > esp)
	{
		b = pow(a, i) / fact(i);
		i++;
		s = s + b;
	}
	s = s + 1;
	printf("%.4f", s);
	return 0;
}