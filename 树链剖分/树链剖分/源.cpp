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
}edge[200006];
ll tot = 1, head[200006];
ll a[100005]; ll mod;
void addedge(ll n, ll to, ll z)
{
	edge[tot].z = z;
	edge[tot].to = to;
	edge[tot].next = head[n];
	head[n] = tot++;
}
//线段树——————区间修改，区间查询
//题意：一个线性数组，不断把某区间内的值修改“为”另一个输入值，查询区间内和。
ll num[100006 * 4];//开四倍空间
ll lazy[100006 * 4], w[100005];

void push_up(ll root)//根节点状态更新
{
	num[root] = (num[root * 2] + num[root * 2 + 1]) % mod;
}
void build(ll l, ll r, ll root)//线段树建树
{
	if (l == r)
	{
		num[root] = w[l];
		return;
	}
	ll mid = (l + r) / 2;
	build(l, mid, root * 2);
	build(mid + 1, r, root * 2 + 1);
	push_up(root);
}

void push_down(ll root, ll len)//传入：root结点下标、对应的当前[l,r]区间长度
{
	if (lazy[root] == 0)//假若这个节点根本没有lazy_tag
		return;
	//num[root] += len * lazy[root];
	lazy[root * 2] = (lazy[root * 2] + lazy[root]) % mod;
	lazy[root * 2 + 1] = (lazy[root * 2 + 1] + lazy[root]) % mod;
	num[root * 2] = (num[root * 2] + lazy[root] * (len - (len) / 2) % mod) % mod;;
	num[root * 2 + 1] = (num[root * 2 + 1] + lazy[root] * ((len) / 2) % mod) % mod;

	lazy[root] = 0;
}

void upgrade(ll la, ll rb, ll l, ll r, ll val, ll root)//线段更新
//la、rb为需更新的区间左、右端点，l、r为当前区间左、右端点，root为当前l、r对应的根存储位置
{
	if (la <= l && rb >= r)
	{
		num[root] = (num[root] + (r - l + 1) * val % mod) % mod;
		lazy[root] = (lazy[root] + val) % mod;
		return;
	}

	push_down(root, r - l + 1);

	ll mid = (l + r) / 2;
	if (la <= mid)
	{
		upgrade(la, rb, l, mid, val, root * 2);
	}
	if (rb > mid)
	{
		upgrade(la, rb, mid + 1, r, val, root * 2 + 1);
	}
	push_up(root);
}

ll query(ll la, ll rb, ll l, ll r, ll root)//查询区间[la,rb]的值
{
	if (l >= la && r <= rb)
	{
		return num[root];
	}
	push_down(root, r - l + 1);
	ll mid = (l + r) / 2;
	ll ans = 0;
	if (la <= mid)
	{
		ans = (ans + query(la, rb, l, mid, root * 2)) % mod;
	}
	if (rb > mid)
	{
		ans = (ans + query(la, rb, mid + 1, r, root * 2 + 1)) % mod;
	}
	push_up(root);
	return ans;
}
ll fa[100005], dep[100005], siz[100005], son[100005];
void dfs1(ll f, ll u)
{
	fa[u] = f; dep[u] = dep[f] + 1; siz[u] = 1;
	ll maxn = -1;
	for (ll i = head[u]; i; i = edge[i].next)
	{
		if (edge[i].to == f)continue;
		dfs1(u, edge[i].to);
		siz[u] += siz[edge[i].to];
		if (siz[edge[i].to] > maxn)
		{
			son[u] = edge[i].to;
			maxn = siz[edge[i].to];
		}
	}
}
ll timi, dfn[1000005], top[1000005];
void dfs2(ll t, ll u)
{
	dfn[u] = ++timi, top[u] = t; w[timi] = a[u];
	if (son[u] == 0)return;
	dfs2(t, son[u]);
	for (ll i = head[u]; i; i = edge[i].next)
	{
		if (edge[i].to == fa[u] || edge[i].to == son[u])continue;
		dfs2(edge[i].to, edge[i].to);
	}
}
void mchain(ll x, ll y, ll z, ll n, ll root)
{
	z %= mod;
	while (top[x] != top[y])
	{
		if (dep[top[x]] < dep[top[y]])
			swap(x, y);
		upgrade(dfn[top[x]], dfn[x], 1, n, z, root);
		//modify(dfn[top[x]], dfn[x], z);
		x = fa[top[x]];
	}
	if (dep[x] > dep[y])
		swap(x, y);
	upgrade(dfn[x], dfn[y], 1, n, z, root);
	//modify(dfn[x], dfn[y], z);
}
ll qchain(ll x, ll y, ll n, ll root)
{
	ll ret = 0;
	while (top[x] != top[y])
	{
		if (dep[top[x]] < dep[top[y]])
			swap(x, y);
		ret += query(dfn[top[x]], dfn[x], 1, n, root);
		//query(dfn[top[x]], dfn[x]);
		x = fa[top[x]];
	}
	if (dep[x] > dep[y])
		swap(x, y);
	ret += query(dfn[x], dfn[y], 1, n, root);;
	//query(dfn[x], dfn[y]);
	return ret % mod;
}
void mson(ll x, ll z, ll n, ll root)
{
	upgrade(dfn[x], dfn[x] + siz[x] - 1, 1, n, z, root);
	//modify(dfn[x], dfn[x] + siz[x] - 1, z);
}
ll qson(ll x, ll n, ll root)
{
	return query(dfn[x], dfn[x] + siz[x] - 1, 1, n, root);
}
int main()
{
	freopen("C:\\Users\\000\\Downloads\\P3384_2.in", "r", stdin);
	ll n, m, root, p;
	scanf("%d%d%d%d", &n, &m, &root, &p);
	mod = p;
	for (ll i = 1; i <= n; i++)scanf("%d", &a[i]);
	for (ll i = 1; i < n; i++)
	{
		ll x, y; scanf("%d%d", &x, &y);
		addedge(x, y, 1); addedge(y, x, 1);
	}
	dfs1(0, root);
	dfs2(0, root);
	build(1, n, 1);
	for (ll i = 1; i <= m; i++)
	{
		ll op; scanf("%d", &op);
		if (op == 1)
		{
			ll x, y, z; scanf("%d%d%d", &x, &y, &z);
			mchain(x, y, z, n, 1);
		}
		else if (op == 2)
		{
			ll x, y; scanf("%d%d", &x, &y);
			printf("%d\n", qchain(x, y, n, 1));
		}
		else if (op == 3)
		{
			ll x, z; scanf("%d%d", &x, &z);
			mson(x, z, n, 1);
		}
		else
		{
			ll x; scanf("%d", &x);
			printf("%d\n", qson(x, n, 1));
		}
	}
	//ll n, x;//原数组结点总数
	//scanf("%lld%lld", &n, &x);
	//build(1, n, 1);//建树
	//while (x--)
	//{
	//	ll ju;
	//	scanf("%lld", &ju);
	//	if (ju == 1)
	//	{
	//		ll la, rb, val;
	//		scanf("%lld%lld%lld", &la, &rb, &val);
	//		upgrade(la, rb, 1, n, val, 1);//更新[l,r]区间结点，每个结点都被更新“成”val
	//	}
	//	else
	//	{
	//		ll la, rb, val;
	//		scanf("%lld%lld", &la, &rb);
	//		printf("%lld\n", query(la, rb, 1, n, 1));//查询区间[la,rb]的值
	//	}
	//}
	return 0;
}
//模板题https://www.luogu.com.cn/problem/P3384
/*
 * ┌───┐   ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┐ ┌───┬───┬───┐  ┌──┐  ┌──┐  ┌──┐
 * │Esc│   │ F1│ F2│ F3│ F4│ │ F5│ F6│ F7│ F8│ │ F9│F10│F11│F12│ │P/S│S L│P/B│  │┌┐│  │┌┐│  │┌┐│
 * └───┘   └───┴───┴───┴───┘ └───┴───┴───┴───┘ └───┴───┴───┴───┘ └───┴───┴───┘  └└┘┘  └└┘┘  └└┘┘
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐ ┌───┬───┬───┐ ┌───┬───┬───┬───┐
 * │~ `│! 1│@ 2│# 3│$ 4│% 5│^ 6│& 7│* 8│( 9│) 0│_ -│+ =│ BacSp │ │Ins│Hom│PUp│ │Num│ / │ * │ - │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤ ├───┼───┼───┤ ├───┼───┼───┼───┤
 * │ Tab │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │{ [│} ]│ | \ │ │Del│End│PDn│ │ 7 │ 8 │ 9 │   │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤ └───┴───┴───┘ ├───┼───┼───┤ + │
 * │ Caps │ A │ S │ D │ F │ G │ H │ J │ K │ L │: ;│" '│ Enter  │               │ 4 │ 5 │ 6 │   │
 * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────────┤     ┌───┐     ├───┼───┼───┼───┤
 * │ Shift  │ Z │ X │ C │ V │ B │ N │ M │< ,│> .│? /│  Shift   │     │ ↑ │     │ 1 │ 2 │ 3 │   │
 * ├─────┬──┴─┬─┴──┬┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤ ┌───┼───┼───┐ ├───┴───┼───┤ E││
 * │ Ctrl│ Win│ Alt│         Space         │ Alt│ Win│Menu│Ctrl│ │ ← │ ↓ │ → │ │   0   │ . │←─┘│
 * └─────┴────┴────┴───────────────────────┴────┴────┴────┴────┘ └───┴───┴───┘ └───────┴───┴───┘
 */
