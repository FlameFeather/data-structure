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
typedef int ll;
struct as
{
	ll to, z, next;
}edge[10003];
ll tot = 1, head[3003];
void addedge(ll n, ll to, ll z)
{
	edge[tot].z = z;
	edge[tot].to = to;
	edge[tot].next = head[n];
	head[n] = tot++;
}
long long dis[3003];
ll vis[3003];
struct cmp //重写仿函数
{
	bool operator() (pair<ll, ll> a, pair<ll, ll> b)
	{
		return a.second > b.second; //小顶堆
	}
};
priority_queue <pair<ll, ll>, vector<pair<ll, ll>>, cmp>q;
void Dijkstra(ll s)
{
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
			if (dis[poi.first] + edge[i].z < dis[edge[i].to])
			{
				dis[edge[i].to] = dis[poi.first] + edge[i].z;
				if (vis[edge[i].to] == 0)q.push({ edge[i].to,dis[edge[i].to] });
			}
			/*dis[edge[i].to] = min(dis[edge[i].to], dis[poi.first] + edge[i].z);
			if (vis[edge[i].to] == 0)q.push({ edge[i].to,dis[edge[i].to] });*/
		}
	}
}
queue<ll>Q;
long long t[3003], h[3003];
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
			if (h[u] + edge[i].z < h[v])
			{
				h[v] = h[u] + edge[i].z;
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
	ll n, m; scanf("%d%d", &n, &m);
	for (ll i = 1; i <= m; i++)
	{
		ll x, y, z;
		scanf("%d%d%d", &x, &y, &z);
		addedge(x, y, z);
	}
	for (ll i = 1; i <= n; i++) addedge(n + 1, i, 0);
	if (!spfa(n + 1, n))
	{
		printf("-1\n");
		return 0;
	}
	for (ll u = 1; u <= n; u++)
		for (ll i = head[u]; i; i = edge[i].next) edge[i].z += h[u] - h[edge[i].to];
	for (ll i = 1; i <= n; i++)
	{
		for (ll i = 1; i <= n; i++)dis[i] = 1e9;
		Dijkstra(i);
		long long ans = 0;
		for (ll j = 1; j <= n; j++)
		{
			if (dis[j] == 1e9)
				ans += j * 1e9;
			else
				ans += j * (dis[j] + h[j] - h[i]);
		}
		printf("%lld\n", ans);
	}
	return 0;
}
//https://www.luogu.com.cn/problem/P5905