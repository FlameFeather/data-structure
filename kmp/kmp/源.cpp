#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<ctype.h>
#include<cstdlib>
#include<vector>
#include<map>
#include<time.h>
#include<iostream>
#include<algorithm>
#include<queue>
#include<memory.h>
#include<set>
#include<cstdlib>
#include <random>
using namespace std;
typedef long long ll;
ll s1[1000006], s2[1000006];
ll nxt[1000006];
void getnxt(ll a[], ll len)
{
	for (ll i = 1, j = 0; i < len;)
	{
		if (a[i] == a[j])nxt[i] = j + 1, j++, i++;
		else
		{
			if (j == 0)i++;
			else j = nxt[j - 1];
		}
		if (j < 0)j = 0, i++;
	}
}
ll kmp(ll s1[], ll s2[], ll len1, ll len2)
{
	for (ll i = 0, j = 0; i < len1;)
	{
		if (j == len2)return i - len2 + 1;
		if (s1[i] == s2[j])j++, i++;
		else
		{
			if (j == 0)i++;
			else j = nxt[j - 1];
		}
		if (j == len2)return i - len2 + 1;
	}
	return -1;
}
int main()
{
	ll t; scanf("%lld", &t);
	while (t--)
	{
		ll n, m; scanf("%lld%lld", &n, &m);
		for (ll i = 0; i < n; i++)scanf("%lld", &s1[i]);
		for (ll i = 0; i < m; i++)scanf("%lld", &s2[i]);
		getnxt(s2, m);
		printf("%lld\n", kmp(s1, s2, n, m));
	}
	return 0;
}