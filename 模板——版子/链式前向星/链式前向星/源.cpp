#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<ctype.h>
#include<cstdlib>
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>
#include<queue>
#include<memory.h>
using namespace std;
typedef long long ll;
struct as
{
	ll to, z, next;
}edge[200005];
ll tot = 1, head[200005], a[200005], b[200005], s = 1;
void addedge(ll n, ll to, ll z)
{
	edge[tot].z = z;
	edge[tot].to = to;
	edge[tot].next = head[n];
	head[n] = tot++;
}
void dfs(ll x0, ll x)
{
	ll f = 0;
	for (ll i = head[x];; i = edge[i].next)
	{
		if (edge[i].to == x0)continue;
		if (i != 0)
		{
			dfs(x, edge[i].to);
			f = 1;
		}
		if (edge[i].next == 0)break;
	}
	if (f == 0)b[s++] = x;
}
int main()
{
	ll n, xx = 0; cin >> n;
	for (ll i = 1; i <= n - 1; i++)
	{
		ll x, y; cin >> x >> y;
		addedge(x, y, 1);
		addedge(y, x, 1);
		a[x]++, a[y]++;
		if (a[x] > 1)xx = x;
		if (a[y] > 1)xx = y;
	}
	dfs(0, xx);
	printf("%lld\n", s / 2);
	for (ll i = 1; i <= s / 2; i++)
	{
		if (b[s / 2 + i] == 0)
		{
			b[s / 2 + i] = b[s / 2 + i - 1];
		}
		printf("%lld %lld\n", b[i], b[s / 2 + i]);
	}
	return 0;
}