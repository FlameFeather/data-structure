#pragma GCC optimize(2)
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
using namespace std;
typedef long long ll;
struct as
{
	ll to, z, next;
}edge[50004];
ll tot = 1, head[20004], vis[20004], dfn[20004], low[20004];
ll cz[20004], in[20004], out[20004];
stack<ll>st; ll cnt = 0, cn = 0;
inline void addedge(ll n, ll to, ll z)
{
	edge[tot].z = z;
	edge[tot].to = to;
	edge[tot].next = head[n];
	head[n] = tot++;
}
void Tarjan(ll fa, ll u)
{
	vis[u] = 1; dfn[u] = low[u] = ++cn;
	st.push(u);
	for (ll i = head[u]; i; i = edge[i].next)
	{
		if (dfn[edge[i].to] == 0)
		{
			Tarjan(u, edge[i].to);
			low[u] = min(low[u], low[edge[i].to]);
		}
		else if(vis[edge[i].to])low[u] = min(low[u], low[edge[i].to]);
	}
	if (dfn[u] == low[u])
	{
		cnt++;
		while (1)
		{
			ll x;
			x = st.top();
			st.pop(); vis[x] = 0;
			cz[x] = cnt;
			if (x == u)return;
		}
	}
}
int main()
{
	ll n, m;
	while (scanf("%lld%lld", &n, &m) != EOF)
	{
		memset(head, 0, sizeof head);
		memset(dfn, 0, sizeof dfn);
		memset(in, 0, sizeof in);
		memset(out, 0, sizeof out);
		cnt = 0; tot = 1; cn = 0;
		for (ll i = 1; i <= m; i++)
		{
			ll x, y;
			scanf("%lld%lld", &x, &y);
			addedge(x, y, 1);
		}
		for (ll i = 1; i <= n; i++)
		{
			//cn = 0;
			if (dfn[i] == 0)Tarjan(0, i);
		}
		if (cnt == 1)
		{
			puts("0");	continue;
		}
		for (ll i = 1; i <= n; i++)
		{
			for (ll j = head[i]; j; j = edge[j].next)
			{
				if (cz[i] != cz[edge[j].to])out[cz[i]]++, in[cz[edge[j].to]]++;
			}
		}
		ll res1 = 0, res2 = 0;
		for (ll i = 1; i <= cnt; i++)
		{
			if (out[i] == 0)res1++;
			if (in[i] == 0)res2++;
		}
		printf("%lld\n", max(res1, res2));
	}
	return 0;
}