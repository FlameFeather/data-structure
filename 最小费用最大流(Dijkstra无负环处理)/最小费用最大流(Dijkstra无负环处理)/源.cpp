//#pragma GCC optimize(2)
//std::ios::sync_with_stdio(false)
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
#include<string>
#include<algorithm>
#include<queue>
#include<memory.h>
#include<set>
#include<stack>
#include<unordered_map>
#include<complex>
using namespace std;
typedef long long ll;
struct as
{
	ll to, f, c, next;
}edge[500004];
ll tot = 2, head[5003];
void addedge(ll n, ll to, ll f, ll c)
{
	edge[tot].f = f;
	edge[tot].c = c;
	edge[tot].to = to;
	edge[tot].next = head[n];
	head[n] = tot++;
}
struct node {
	ll v, e;
} p[10005];
ll dis[5003];
ll vis[5003];
struct cmp //重写仿函数
{
	bool operator() (pair<ll, ll> a, pair<ll, ll> b)
	{
		return a.second > b.second; //小顶堆
	}
};
priority_queue <pair<ll, ll>, vector<pair<ll, ll>>, cmp>q;
queue<ll>Q;
ll t[5003], h[5003];
bool Dijkstra(ll s, ll t, ll n)
{
	for (ll i = 1; i <= n; i++) dis[i] = 1e9;
	memset(vis, 0, sizeof(vis));
	while (q.size())q.pop();
	ll di = 0;
	q.push({ s,0 });
	dis[s] = 0;
	while (q.size())
	{
		pair<ll, ll> poi;
		poi = q.top();
		q.pop();
		if (vis[poi.first])continue;
		vis[poi.first] = 1;
		for (ll i = head[poi.first]; i; i = edge[i].next)
		{
			if (edge[i].f && dis[poi.first] + edge[i].c + h[poi.first] - h[edge[i].to] < dis[edge[i].to])
			{
				dis[edge[i].to] = dis[poi.first] + edge[i].c + h[poi.first] - h[edge[i].to];
				p[edge[i].to].v = poi.first;
				p[edge[i].to].e = i;
				if (vis[edge[i].to] == 0)q.push({ edge[i].to,dis[edge[i].to] });
			}
			/*dis[edge[i].to] = min(dis[edge[i].to], dis[poi.first] + edge[i].z);
			if (vis[edge[i].to] == 0)q.push({ edge[i].to,dis[edge[i].to] });*/
		}
	}
	return dis[t] != 1e9;
}
bool spfa(ll s, ll n)
{
	//memset(dis, 0x3f, sizeof dis);
	memset(h, 0x3f, sizeof(h));
	h[s] = 0; vis[s] = 1;//vis记录是否在队列里 
	Q.push(s);
	ll u, v;
	while (Q.size())
	{
		u = Q.front(); Q.pop(); vis[u] = 0;
		for (ll i = head[u]; i; i = edge[i].next)//向外发散 
		{
			v = edge[i].to;
			if (edge[i].f && h[u] + edge[i].c < h[v])
			{
				h[v] = h[u] + edge[i].c;
				if (!vis[v])
				{
					Q.push(v), vis[v] = 1; //不在队列中，那就放进去更新别的点 
					t[v]++;
					if (t[v] == n + 1) return false;
				}
			}
		}
	}
	return true;
}
int main() {
	ll n, m, s, t; scanf("%lld%lld%lld%lld", &n, &m, &s, &t);
	for (ll i = 1; i <= m; i++)
	{
		ll x, y, f, c;
		scanf("%lld%lld%lld%lld", &x, &y, &f, &c);
		addedge(x, y, f, c);
		addedge(y, x, 0, -c);
	}
	if (!spfa(s, n))
	{
		printf("-1\n");
		return 0;
	}
	ll maxf = 0, minc = 0;
	while (Dijkstra(s, t, n))
	{
		ll minf = 1e9;
		for (ll i = 1; i <= n; i++) h[i] += dis[i];
		for (ll i = t; i != s; i = p[i].v)
			minf = min(minf, edge[p[i].e].f);
		for (ll i = t; i != s; i = p[i].v) {
			edge[p[i].e].f -= minf;
			edge[p[i].e ^ 1].f += minf;
		}
		maxf += minf;
		minc += minf * h[t];
	}
	printf("%lld %lld\n", maxf, minc);
	return 0;
}