#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
int main()
{
	long long x;
	while (scanf_s("%lld", &x)) {
		long long X, sw, s = 1, yu, cd = 1, ss = 0;
		X = x;
		if (x == 1)
		{
			printf("1 1");
			return 0;
		}
		/*
		if (x == 11)
		{
			printf("1 2");
			return 0;
		}
		if (x == 111)
		{
			printf("1 3");
			return 0;
		}
		*/
		for (int i = 1; X > 0; i = i + 1)
		{
			X = X / 10;
			sw = i;
		}
		for (int i = 1; i <= sw; i = i + 1)
		{
			s = s * 10 + 1;
		}
		yu = s;
		for (cd = 1; yu != 0; cd = cd + 1)
		{
			s = yu;
			yu = yu % x;
			if (yu == 0)
			{
				ss = s / x + ss * 10;
				break;
			}
			if (ss > 9999979)
			{
				printf("%lld", ss);
				ss = 0;
			}
			ss = s / x + ss * 10;
			if (ss == 0)printf("0");
			yu = yu * 10 + 1;
		}
		printf("%lld %lld\n", ss, cd + sw);
	}
	return 0;
}