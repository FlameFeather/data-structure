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
ll tot = 1, head[200005], vis[200005];
void addedge(ll n, ll to, ll z)
{
	edge[tot].z = z;
	edge[tot].to = to;
	edge[tot].next = head[n];
	head[n] = tot++;
}
ll son[200005], maxn[200005], numNode, root;
void getRoot(ll u, ll fa)
{
	son[u] = 1; maxn[u] = 0;
	for (ll i = head[u]; i; i = edge[i].next)
	{
		if (vis[edge[i].to] || edge[i].to == fa)continue;
		getRoot(edge[i].to, u);
		maxn[u] = max(maxn[u], son[edge[i].to]);
		son[u] += son[edge[i].to];
	}
	maxn[u] = max(numNode - son[u], maxn[u]);
	if (maxn[u] < maxn[root]) root = u;
}
ll dis[200005], f = 0, d[200005];
void cal_dist(ll u, ll fa, ll w)
{
	if (u == fa)dis[u] = w, d[f++] = dis[u];
	for (ll i = head[u]; i; i = edge[i].next)
	{
		if (vis[edge[i].to] || edge[i].to == fa)continue;
		dis[edge[i].to] = dis[u] + edge[i].z;
		d[f++] = dis[edge[i].to];
		cal_dist(edge[i].to, u, 0);
	}
}
ll k;
ll cal(ll u, ll fa, ll w)
{
	f = 0; cal_dist(u, fa, w); ll cnt = 0;
	sort(d, d + f);
	for (ll l = 0, r = f - 1; l < r;)
	{
		if (d[l] + d[r] <= k) cnt += r - l, l++;
		else r--;
	}
	return cnt;
}
ll res = 0;
void dfs(ll u, ll fa)
{
	vis[u] = 1; res += cal(u, u, 0);
	for (ll i = head[u]; i; i = edge[i].next)
	{
		if (vis[edge[i].to] || edge[i].to == fa)continue;
		res -= cal(edge[i].to, edge[i].to, edge[i].z);
		numNode = son[edge[i].to];
		root = 0;
		getRoot(edge[i].to, 0);
		dfs(root, root);
	}
}
int main()
{
	ll n;
	while (scanf("%lld%lld", &n, &k) != EOF)
	{
		if (n == 0 && k == 0)break;
		//memset(head, 0, sizeof head);
		//memset(vis, 0, sizeof vis);
		tot = 1; for (ll i = 1; i <= n; i++)head[i] = 0, vis[i] = 0;
		numNode = n; res = 0; root = 0, maxn[0] = n;
		for (ll i = 1; i < n; i++)
		{
			ll x, y, z;
			scanf("%lld%lld%lld", &x, &y, &z);
			addedge(x, y, z); addedge(y, x, z);
		}
		getRoot(1, 0);
		getRoot(root, 0);
		dfs(root, root);
		printf("%lld\n", res);
	}
	return 0;
}
////#pragma GCC optimize(2)
////std::ios::sync_with_stdio(false);
//#include<stdio.h>
//#include<stdlib.h>
//#include<string.h>
//#include<string>
//#include<istream>
//#include<math.h>
//#include<ctype.h>
//#include<cstdlib>
//#include<vector>
//#include<map>
//#include<iostream>
//#include<algorithm>
//#include<queue>
//#include<memory.h>
//#include<set>
//#include<stack>
//#include<unordered_map>
//using namespace std;
//typedef long long ll;
//struct as
//{
//	ll to, z, next;
//}edge[400005];
//ll tot = 1, head[200005], vis[200005];
//void addedge(ll n, ll to, ll z)
//{
//	edge[tot].z = z;
//	edge[tot].to = to;
//	edge[tot].next = head[n];
//	head[n] = tot++;
//}
//ll son[200005], maxn[200005], numNode, root;
//void getRoot(ll u, ll fa)
//{
//	son[u] = 1; maxn[u] = 0;
//	for (ll i = head[u]; i; i = edge[i].next)
//	{
//		if (vis[edge[i].to] || edge[i].to == fa)continue;
//		getRoot(edge[i].to, u);
//		maxn[u] = max(maxn[u], son[edge[i].to]);
//		son[u] += son[edge[i].to];
//	}
//	maxn[u] = max(numNode - son[u], maxn[u]);
//	if (maxn[u] < maxn[root]) root = u;
//}
//ll dis[200005], f = 0;
//struct poi
//{
//	ll v, po;
//}d[200005];
//void cal_dist(ll u, ll fa, ll w)
//{
//	if (u == fa)dis[u] = w, d[f].v = dis[u], d[f++].po = u;
//	for (ll i = head[u]; i; i = edge[i].next)
//	{
//		if (vis[edge[i].to] || edge[i].to == fa)continue;
//		dis[edge[i].to] = dis[u] + edge[i].z;
//		d[f].v = dis[edge[i].to], d[f++].po = edge[i].to;
//		cal_dist(edge[i].to, u, 0);
//	}
//}
//ll k, res[200005];
//bool cmp(poi a, poi b)
//{
//	return a.v < b.v;
//}
//bool cmp_lower(poi mid, ll val)
//{
//	return mid.v <= val;
//}
//ll cal_add(ll u, ll fa, ll w)
//{
//	f = 0; cal_dist(u, fa, w); ll cnt = 0;
//	sort(d, d + f, cmp);
//	for (ll i = 0; i < f; i++)
//	{
//		ll pos = lower_bound(d, d + f, k - d[i].v, cmp_lower) - d;
//		if (pos == f)
//		{
//			if (d[pos - 1].v + d[i].v <= k)pos--;
//			else break;
//		}
//		else if (d[pos].v + d[i].v > k)pos--;
//		pos++;
//		res[d[i].po] += pos;
//	}
//	return cnt;
//}
//ll cal_subtract(ll u, ll fa, ll w)
//{
//	f = 0; cal_dist(u, fa, w); ll cnt = 0;
//	sort(d, d + f, cmp);
//	for (ll i = 0; i < f; i++)
//	{
//		ll pos = lower_bound(d, d + f, k - d[i].v, cmp_lower) - d;
//		if (pos == f)
//		{
//			if (d[pos - 1].v + d[i].v <= k)pos--;
//			else break;
//		}
//		else if (d[pos].v + d[i].v > k)pos--;
//		pos++;
//		res[d[i].po] -= pos;
//	}
//	return cnt;
//}
//void dfs(ll u, ll fa)
//{
//	vis[u] = 1; cal_add(u, u, 0);
//	for (ll i = head[u]; i; i = edge[i].next)
//	{
//		if (vis[edge[i].to] || edge[i].to == fa)continue;
//		cal_subtract(edge[i].to, edge[i].to, edge[i].z);
//		numNode = son[edge[i].to];
//		root = 0;
//		getRoot(edge[i].to, 0);
//		dfs(root, root);
//	}
//}
//int main()
//{
//	ll n;
//	while (scanf("%lld%lld", &n, &k) != EOF)
//	{
//		if (n == 0 && k == 0)break;
//		//memset(head, 0, sizeof head);
//		//memset(vis, 0, sizeof vis);
//		tot = 1; for (ll i = 1; i <= n; i++)head[i] = 0, vis[i] = 0, res[i] = 0;
//		numNode = n; root = 0, maxn[0] = n;
//		for (ll i = 1; i < n; i++)
//		{
//			ll x, y;
//			scanf("%lld%lld", &x, &y);
//			addedge(x, y, 1); addedge(y, x, 1);
//		}
//		getRoot(1, 0);
//		getRoot(root, 0);
//		dfs(root, root);
//		for (ll i = 1; i <= n; i++)
//			printf("%lld%s", res[i], i == n ? "\n" : " ");
//	}
//	return 0;
//}