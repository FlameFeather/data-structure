//#pragma GCC optimize(2)
//std::ios::sync_with_stdio(false);
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<string>
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
struct as
{
	ll to, z, next;
}edge[1000005];
ll tot = 1, head[500005];
ll anc[500005][30], dep[500005];
void addedge(ll n, ll to, ll z)
{
	edge[tot].z = z;
	edge[tot].to = to;
	edge[tot].next = head[n];
	head[n] = tot++;
}
void dfs(ll fa, ll u, ll root)
{
	anc[u][0] = fa; dep[u] = dep[fa] + 1;
	for (ll i = 1; i < 30; i++)
	{
		anc[u][i] = anc[anc[u][i - 1]][i - 1];
		//if (anc[u][i] == 0)break;
	}
	for (ll i = head[u];i; i = edge[i].next)
	{
		if (edge[i].to == fa)continue;
		if (i != 0)dfs(u, edge[i].to, root);
	}
}
int main()
{
	ll n, m, root;
	scanf("%lld%lld%lld", &n, &m, &root);
	for (ll i = 1; i < n; i++)
	{
		ll x, y;
		scanf("%lld%lld", &x, &y);
		addedge(x, y, 1);
		addedge(y, x, 1);
	}
	dep[0] = 0;
	dfs(0, root, root);
	for (ll i = 1; i <= m; i++)
	{
		ll x, y;
		scanf("%lld%lld", &x, &y);
		if (dep[x] < dep[y])swap(x, y);
		for (ll j = 29; j >= 0; j--)
		{
			if (dep[anc[x][j]] >= dep[y])
				x = anc[x][j];
		}
		if (x == y)
		{
			printf("%lld\n", x);
			continue;
		}
		for (ll j = 29; j >= 0; j--)
		{
			if (anc[x][j] != anc[y][j])
			{
				x = anc[x][j];
				y = anc[y][j];
			}
		}
		printf("%lld\n", anc[x][0]);
	}
	return 0;
}