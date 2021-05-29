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
}edge[240005];
ll tot = 2, head[120005], cure[120005];
ll d[1205], gap[1205];
void addedge(ll n, ll to, ll v)
{
	edge[tot].v = v;
	edge[tot].to = to;
	edge[tot].next = head[n];
	head[n] = tot++;
}
void bfs(ll s, ll t, ll n)
{
	queue<ll>q;
	memset(d, 0, sizeof(d));
	q.push(s); d[s] = 1;
	gap[d[s]] = 1;
	while (q.size())
	{
		ll u = q.front(); q.pop();
		for (ll i = head[u]; i; i = edge[i].next)
		{
			ll v = edge[i].to;
			if (d[v])continue;
			q.push(v); d[v] = d[u] + 1;
			gap[d[v]]++;
		}
	}
	for (ll i = 1; i <= n; i++)cure[i] = head[i];
}
ll n;
ll dfs(ll s, ll u, ll t, ll flow)
{
	if (u == t)return flow;
	if (flow == 0)return 0;
	ll delta = 0;
	for (ll i = cure[u]; i; i = edge[i].next)
	{
		cure[u] = i;
		if (edge[i].v <= 0 || d[edge[i].to] + 1 != d[u])continue;
		ll tmp = dfs(s, edge[i].to, t, min(flow - delta, edge[i].v));
		if (tmp <= 0)continue;
		edge[i].v -= tmp;
		edge[i ^ 1].v += tmp;
		delta += tmp;
		if (delta == flow)return flow;
	}
	if (--gap[d[u]] == 0)d[s] = n + 1;
	++gap[++d[u]];
	cure[u] = head[u];
	return delta;
}
int main()
{
	ll m, s, t, max = 0;
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
	bfs(t, s, n);
	while (d[s] <= n)
	{
		max += dfs(s, s, t, 1e18);
	}
	printf("%lld", max);
	return 0;
}