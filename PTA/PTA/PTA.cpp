#include<stdio.h>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#define scanf (void)scanf
using namespace std;
typedef long long ll;
ll head[1003], tot = 1;
struct uct
{
	ll to, v, next;
}edge[10004];
void adddge(ll x, ll to, ll v)
{
	edge[tot].to = to;
	edge[tot].v = v;
	edge[tot].next = head[x];
	head[x] = tot++;
}
ll fa[1000], tmp = 1, tm[1000], a[1000];
void dfs(ll faa, ll u)
{
	a[u] = tm[tmp++]; fa[u] = faa;
	vector<ll>v;
	for (ll i = head[u]; i; i = edge[i].next)v.push_back(edge[i].to);
	reverse(v.begin(), v.end());
	for (ll i = 0; i < v.size(); i++)
	{
		dfs(u, v[i]);
	}
}
int main()
{
	ll n, h, m = 1;
	scanf("%lld%lld", &n, &h);
	for (ll i = 1; i <= n; i++)
	{
		ll cnt = 1;
		if (i == 1)cnt = h;
		else
		{
			for (ll j = 1; j <= h; j++)cnt *= i;
			cnt--;
		}
		if (cnt >= n)
		{
			m = i;
			break;
		}
	}
	ll cnt = 2;
	for (ll i = 1; cnt <= n; i++)
	{
		for (ll j = 1; j <= m && cnt <= n; j++)
			adddge(i, cnt++, 1);
	}
	for (ll i = 1; i <= n; i++)scanf("%lld", &tm[i]);
	dfs(0, 1);
	for (ll i = 1; i <= n; i++)printf("%lld%s", a[i], i == n ? "\n" : " ");
	ll q; scanf("%lld", &q);
	while (q--)
	{
		ll x; scanf("%lld", &x);
		x++;
		ll nxt = x;
		while (nxt != 0)
		{
			ll z = a[nxt];
			nxt = fa[nxt];
			if (nxt)printf("%lld ", z);
			else
			{
				if (q == 0)printf("%lld", z);
				else printf("%lld\n", z);
			}
		}
	}
	return 0;
}