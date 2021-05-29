#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<ctype.h>
#include<cstdlib>
#include<vector>
#include<map>
#include<iostream>
#include<algorithm>
#include<queue>
#include<memory.h>
#include<set>
//#include<unordered_map>
#include<cstdlib>
using namespace std;
typedef long long ll;
struct as
{
	ll v, next, last;
}a[100005];
int main()
{
	ll t;
	scanf("%lld", &t);
	while (t--)
	{
		ll n, s, ss = 0;
		scanf("%lld", &n);
		s = n;
		memset(a, 0, sizeof(a));
		for (ll i = 1; i <= n; i++)
		{
			scanf("%lld", &a[i].v);
			a[i - 1].next = i;
			a[i].last = i - 1;
		}
		a[n].next = n + 1;
		a[n + 1].next = n + 2;
		a[n + 1].v = 1e18;
		a[n + 1].last = n;
		for (ll i = 1; i < n; )
		{
			ll j = i;
			ll z = 0;
			while (a[j].v > a[a[j].next].v)
			{
				j = a[j].next;
				z++;
			}
			if (j != i)
			{
				s = s - (z + 1);
				i = a[i].last;
				a[i].next = a[j].next;
				a[a[j].next].last = i;
				if (i == 0)i = a[i].next;
			}
			else
			{
				i = a[i].next;
			}
		}
		printf("%lld\n", s);
		if (s == 0)printf("\n");
		else for (ll i = 0; ;)
		{
			printf("%lld", a[a[i].next].v);
			ss++;
			i = a[i].next;
			if (ss == s)
			{
				printf("\n");
				break;
			}
			else
			{
				printf(" ");
			}
		}
	}
	return 0;
}