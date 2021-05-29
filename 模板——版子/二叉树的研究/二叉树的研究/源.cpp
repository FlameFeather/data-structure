#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
char a[1000005], b[1000005],c[1000005],s[4000020];
int i = 0, j = 0, k = 0;
void solve(int id)
{
	a[i++] = s[id];
	if (s[2 * id] != '\0')
		solve(2 * id);
	b[j++] = s[id];
	if (s[2 * id + 1] != '\0')
		solve(2 * id + 1);
	c[k++] = s[id];
}
int main()
{
	int n;
	scanf_s("%d", &n);
	scanf_s("%s", s+1,sizeof(s));
	solve(1);
	if (strcmp(a, b) >= 0 && strcmp(b, c) >= 0)
	{
		printf("%s", c);
	}
	else if (strcmp(a, b) <= 0 && strcmp(b, c) <= 0)
	{
		printf("%s", a);
	}
	else if (strcmp(b, a) >= 0 && strcmp(a, c) >= 0)
	{
		printf("%s", b);
	}
	return 0;
}