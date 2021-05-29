#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
char  p[205], fb[205], xw1[] = { "xiaow" }, xw2[] = { "winterzz" };
int main()
{
	int n, len, a[205], s = 0, T;
	scanf_s("%d", &T);

	for (int j = 1; j <= T; j = j + 1)
	{
		scanf_s("%d", &n);
		for (int i = 1; i <= n; i = i + 1)
		{
			scanf_s("%s", p, sizeof(p));
			len = strlen(p);
			for (int k = 1; k <= len - 8 + 1; k = k + 1)
			{
				strncpy_s(fb, p + k - 1, 8);
				fb[8] = '\0';
				if (strcmp(xw2, fb) == 0)
				{
					a[s] = i;
					s = s + 1;
					goto line39;
				}
			}
			for (int k = 1; k <= len - 5 + 1; k = k + 1)
			{
				strncpy_s(fb, p + k - 1, 5);
				fb[5] = '\0';
				if (strcmp(xw1, fb) == 0)
				{
					a[s] = i;
					s = s + 1;
				}
			}
		line39:;
		}
		for (int i = 0; i <= s - 1; i = i + 1)
		{
			printf("KILL %d\n", a[i]);
		}
		s = 0;
	}
	return 0;
}