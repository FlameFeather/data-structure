//#pragma GCC optimize(2)
//std::ios::sync_with_stdio(false);
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<string>
#include<istream>
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
#include<stack>
#include<unordered_map>
#include<cstdlib>
using namespace std;
typedef long long ll;
struct as
{
	ll to, z, next;
}edge[400005];
ll tot = 1, head[200005];
void addedge(ll n, ll to, ll z)
{
	edge[tot].z = z;
	edge[tot].to = to;
	edge[tot].next = head[n];
	head[n] = tot++;
}
ll dis[200005], vis[200005];
struct cmp //ÖØÐ´·Âº¯Êý
{
	bool operator() (pair<ll, ll> a, pair<ll, ll> b)
	{
		return a.second > b.second; //Ð¡¶¥¶Ñ
	}
};
priority_queue <pair<ll, ll>, vector<pair<ll, ll>>, cmp>q;
void Dijkstra()
{
	ll di = 0;
	q.push({ 1,0 });
	dis[1] = 0;
	while (q.size())
	{
		pair<ll, ll> poi;
		poi = q.top();
		q.pop();
		//if (vis[poi.first])continue;
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
int main()
{
	ll n, m; scanf("%lld%lld", &n, &m);
	for (ll i = 1; i <= m; i++)
	{
		ll x, y, z;
		scanf("%lld%lld%lld", &x, &y, &z);
		addedge(x, y, z);
		addedge(y, x, z);
	}
	for (ll i = 1; i <= n; i++)dis[i] = 1e9;
	Dijkstra();
	if (dis[n] == 1e9)printf("qwb baka\n");
	else printf("%lld\n", dis[n]);
	return 0;
}