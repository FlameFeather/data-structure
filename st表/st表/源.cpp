//#pragma GCC optimize(2)
//std::ios::sync_with_stdio(false);
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<ctype.h>
#include<cstdlib>
#include<vector>
#include<map>
#include<list>
#include<istream>
#include<iostream>
#include<algorithm>
#include<queue>
#include<memory.h>
#include<set>
#include<stack>
#include<unordered_map>
using namespace std;
typedef long long ll;
ll a[50004], po[30], lg[50004];
ll stmin[50004][30], stmax[50004][30];
int main()
{
	ll n, q; po[0] = 1; lg[0] = -1;
	scanf("%lld%lld", &n, &q);
	for (ll i = 1; i <= n; i++)
	{
		scanf("%lld", &a[i]);
		if (i <= 29)po[i] = po[i - 1] * 2;
		lg[i] = lg[i / 2] + 1;
		stmin[i][0] = a[i];
		stmax[i][0] = a[i];
	}
	for (ll i = 1; i <= lg[n]; i++)
	{
		for (ll j = 1; j + po[i] - 1 <= n; j++)
		{
			stmin[j][i] = min(stmin[j][i - 1], stmin[j + po[i - 1]][i - 1]);
			stmax[j][i] = max(stmax[j][i - 1], stmax[j + po[i - 1]][i - 1]);
		}
	}
	for (ll i = 1; i <= q; i++)
	{
		ll x, y;
		scanf("%lld%lld", &x, &y);
		ll len = y - x + 1;
		printf("%lld\n", max(stmax[x][lg[len]], stmax[y - po[lg[len]] + 1][lg[len]]) - min(stmin[x][lg[len]], stmin[y - po[lg[len]] + 1][lg[len]]));
	}
	return 0;
}