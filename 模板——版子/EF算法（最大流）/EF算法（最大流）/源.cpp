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
ll tot = 2, head[200005], flow[200005], pre[200005];
bool a[5003];
void addedge(ll n, ll to, ll v)
{
	edge[tot].v = v;
	edge[tot].to = to;
	edge[tot].next = head[n];
	head[n] = tot++;
}
ll bfs(ll s, ll t)
{
	queue<ll>q;
	memset(a, 0, sizeof(a));
	q.push(s); a[s] = 1; flow[s] = 1e18;
	while (q.size())
	{
		ll u = q.front(); q.pop();
		for (ll i = head[u]; i; i = edge[i].next)
		{
			ll v = edge[i].to;
			if (a[v] || edge[i].v <= 0)continue;
			flow[v] = min(flow[u], edge[i].v);
			pre[v] = i;
			q.push(v); a[v] = 1;
			if (v == t)return 1;
		}
	}
	return 0;
}
ll update(ll s, ll t)
{
	ll delta = flow[t];
	while (t != s)
	{
		edge[pre[t]].v -= delta;
		edge[pre[t] ^ 1].v += delta;
		t = edge[pre[t] ^ 1].to;
	}
	return delta;
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
	while (bfs(s, t))
	{
		max += update(s, t);
	}
	printf("%lld", max);
	return 0;
}