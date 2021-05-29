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
queue<ll> q;
void spfa()
{
	//memset(dis, 0x3f, sizeof dis);
	dis[1] = 0; vis[1] = 1;//vis记录是否在队列里 
	q.push(1);
	ll u, v;
	while (q.size())
	{
		u = q.front(); q.pop(); vis[u] = 0;
		for (ll i = head[u]; i; i = edge[i].next)//向外发散 
		{
			v = edge[i].to;
			if (dis[u] + edge[i].z < dis[v])
			{
				dis[v] = dis[u] + edge[i].z;
				if (!vis[v]) q.push(v), vis[v] = 1; //不在队列中，那就放进去更新别的点 
			}
		}
	}
}
int main()
{
	ll n, m; 
	while (scanf("%lld%lld", &n, &m) != EOF)
	{
		if (n == 0 && m == 0)break;
		tot = 1;
		for (ll i = 1; i <= n; i++)head[i] = 0;
		for (ll i = 1; i <= m; i++)
		{
			ll x, y, z;
			scanf("%lld%lld%lld", &x, &y, &z);
			addedge(x, y, z);
			addedge(y, x, z);
		}
		for (ll i = 1; i <= n; i++)dis[i] = 1e9;
		spfa();
		printf("%lld\n", dis[n]);
	}
	return 0;
}