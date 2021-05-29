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
	ll to, v, next;
}edge[200005];
ll tot = 2, head[200005], b[200005], s = 1;
bool a[5003];
void addedge(ll n, ll to, ll v)
{
	edge[tot].v = v;
	edge[tot].to = to;
	edge[tot].next = head[n];
	head[n] = tot++;
}
ll dfs(ll u, ll t, ll flow)
{
	if (u == t)return flow;
	a[u] = 1;
	if (flow == 0)return 0;
	for (ll i = head[u]; i; i = edge[i].next)
	{
		if (edge[i].v <= 0 || a[edge[i].to])continue;
		ll delta = dfs(edge[i].to, t, min(flow, edge[i].v));
		if (delta <= 0)continue;
		edge[i].v -= delta;
		edge[i ^ 1].v += delta;
		return delta;
	}
	return 0;
}
int main()
{
	ll n, m, s, t, max = 0;
	scanf("%lld%lld%lld%lld", &n, &m, &s, &t);
	//cin >> n >> m >> s >> t;
	for (ll i = 1; i <= m; i++)
	{
		ll s, t, v;
		//cin >> s >> t >> v;
		scanf("%lld%lld%lld", &s, &t, &v);
		addedge(s, t, v);
		addedge(t, s, 0);
	}
	while (ll x = dfs(s, t, 1e9 + 7))
	{
		memset(a, 0, sizeof(a));
		max += x;
	}
	cout << max;
	return 0;
}