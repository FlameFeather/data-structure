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
ll tot = 2, head[200005], cure[200005];
ll d[503];
void addedge(ll n, ll to, ll v)
{
	edge[tot].v = v;
	edge[tot].to = to;
	edge[tot].next = head[n];
	head[n] = tot++;
}
ll bfs(ll s, ll t, ll n)
{
	queue<ll>q;
	memset(d, 0, sizeof(d));
	q.push(s); d[s] = 1;
	while (q.size())
	{
		ll u = q.front(); q.pop();
		for (ll i = head[u]; i; i = edge[i].next)
		{
			ll v = edge[i].to;
			if (d[v] || edge[i].v <= 0)continue;
			q.push(v); d[v] = d[u] + 1;
		}
	}
	for (ll i = 1; i <= n; i++)cure[i] = head[i];
	return d[t] != 0;
}
ll dfs(ll u, ll t, ll flow)
{
	if (u == t)return flow;
	if (flow == 0)return 0;
	for (ll i = cure[u]; i; i = edge[i].next)
	{
		cure[u] = i;
		if (edge[i].v <= 0 || d[edge[i].to] - 1 != d[u])continue;
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
	while (bfs(s, t, n))
	{
		while (ll delta = dfs(s, t, 1e18))
		{
			max += delta;
		}
	}
	printf("%lld", max);
	return 0;
}