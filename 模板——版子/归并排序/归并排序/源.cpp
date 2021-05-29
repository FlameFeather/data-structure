#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include <ctype.h>
#include<stdio.h>
using namespace std;
typedef long long ll;
int arr[10005];
ll s;
void sort(int l, int r)
{
	int m = (l + r) / 2, x = l, y = m;
	int L = m - l + 1, R = r - m;
	/*int* pl = new int[L+10];
	int* pr = new int[R+10];*/
	int pl[50005];
	int pr[50005];
	for (int i = l; i <= m; i++)
	{
		pl[i - l + 1] = arr[i];
	}
	for (int i = m + 1; i <= r; i++)
	{
		pr[i - m] = arr[i];
	}
	int i = 1, j = 1;
	while (i <= L && j <= R)
	{
		if (pl[i] < pr[j])
		{
			arr[l] = pl[i];
			i++;
			l++;
		}
		else
		{
			arr[l] = pr[j];
			j++;
			l++;
			s = s + L - i + 1;
		}
	}
	while (i <= L)
	{
		arr[l] = pl[i];
		i++;
		l++;
	}
	while (j <= R)
	{
		arr[l] = pr[j];
		j++;
		l++;
	}
}
void unfold(int l, int r)
{
	if (l == r)
	{
		return;
	}
	int mid;
	mid = (l + r) / 2;
	unfold(l, mid);
	unfold(mid + 1, r);
	sort(l, r);
}
int main()
{
	int n, t;
	scanf_s("%d", &t);
	for (int i = 1; i <= t; i++)
	{
		scanf_s("%d", &n);
		for (int i = 1; i <= n; i++)
		{
			scanf_s("%d", &arr[i]);
		}
		unfold(1, n);
		printf("Case #%d: %lld\n", i, s);
		s = 0;
	}
	return 0;
}