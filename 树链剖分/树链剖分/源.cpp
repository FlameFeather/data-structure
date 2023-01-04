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
//�߶��������������������޸ģ������ѯ
//���⣺һ���������飬���ϰ�ĳ�����ڵ�ֵ�޸ġ�Ϊ����һ������ֵ����ѯ�����ں͡�
ll num[100006 * 4];//���ı��ռ�
ll lazy[100006 * 4], w[100005];

void push_up(ll root)//���ڵ�״̬����
{
	num[root] = (num[root * 2] + num[root * 2 + 1]) % mod;
}
void build(ll l, ll r, ll root)//�߶�������
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

void push_down(ll root, ll len)//���룺root����±ꡢ��Ӧ�ĵ�ǰ[l,r]���䳤��
{
	if (lazy[root] == 0)//��������ڵ����û��lazy_tag
		return;
	//num[root] += len * lazy[root];
	lazy[root * 2] = (lazy[root * 2] + lazy[root]) % mod;
	lazy[root * 2 + 1] = (lazy[root * 2 + 1] + lazy[root]) % mod;
	num[root * 2] = (num[root * 2] + lazy[root] * (len - (len) / 2) % mod) % mod;;
	num[root * 2 + 1] = (num[root * 2 + 1] + lazy[root] * ((len) / 2) % mod) % mod;

	lazy[root] = 0;
}

void upgrade(ll la, ll rb, ll l, ll r, ll val, ll root)//�߶θ���
//la��rbΪ����µ��������Ҷ˵㣬l��rΪ��ǰ�������Ҷ˵㣬rootΪ��ǰl��r��Ӧ�ĸ��洢λ��
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

ll query(ll la, ll rb, ll l, ll r, ll root)//��ѯ����[la,rb]��ֵ
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
	//ll n, x;//ԭ����������
	//scanf("%lld%lld", &n, &x);
	//build(1, n, 1);//����
	//while (x--)
	//{
	//	ll ju;
	//	scanf("%lld", &ju);
	//	if (ju == 1)
	//	{
	//		ll la, rb, val;
	//		scanf("%lld%lld%lld", &la, &rb, &val);
	//		upgrade(la, rb, 1, n, val, 1);//����[l,r]�����㣬ÿ����㶼�����¡��ɡ�val
	//	}
	//	else
	//	{
	//		ll la, rb, val;
	//		scanf("%lld%lld", &la, &rb);
	//		printf("%lld\n", query(la, rb, 1, n, 1));//��ѯ����[la,rb]��ֵ
	//	}
	//}
	return 0;
}
//ģ����https://www.luogu.com.cn/problem/P3384
/*
 * ����������   ���������Щ������Щ������Щ������� ���������Щ������Щ������Щ������� ���������Щ������Щ������Щ������� ���������Щ������Щ�������  ��������  ��������  ��������
 * ��Esc��   �� F1�� F2�� F3�� F4�� �� F5�� F6�� F7�� F8�� �� F9��F10��F11��F12�� ��P/S��S L��P/B��  ��������  ��������  ��������
 * ����������   ���������ة������ة������ة������� ���������ة������ة������ة������� ���������ة������ة������ة������� ���������ة������ة�������  ��������  ��������  ��������
 * ���������Щ������Щ������Щ������Щ������Щ������Щ������Щ������Щ������Щ������Щ������Щ������Щ������Щ��������������� ���������Щ������Щ������� ���������Щ������Щ������Щ�������
 * ��~ `��! 1��@ 2��# 3��$ 4��% 5��^ 6��& 7��* 8��( 9��) 0��_ -��+ =�� BacSp �� ��Ins��Hom��PUp�� ��Num�� / �� * �� - ��
 * ���������ة��Щ��ة��Щ��ة��Щ��ة��Щ��ة��Щ��ة��Щ��ة��Щ��ة��Щ��ة��Щ��ة��Щ��ة��Щ��ة��Щ��ة��Щ����������� ���������੤�����੤������ ���������੤�����੤�����੤������
 * �� Tab �� Q �� W �� E �� R �� T �� Y �� U �� I �� O �� P ��{ [��} ]�� | \ �� ��Del��End��PDn�� �� 7 �� 8 �� 9 ��   ��
 * �������������ةЩ����ةЩ����ةЩ����ةЩ����ةЩ����ةЩ����ةЩ����ةЩ����ةЩ����ةЩ����ةЩ����ةЩ����ة����������� ���������ة������ة������� ���������੤�����੤������ + ��
 * �� Caps �� A �� S �� D �� F �� G �� H �� J �� K �� L ��: ;��" '�� Enter  ��               �� 4 �� 5 �� 6 ��   ��
 * ���������������ة��Щ��ة��Щ��ة��Щ��ة��Щ��ة��Щ��ة��Щ��ة��Щ��ة��Щ��ة��Щ��ة��Щ��ة��Щ��ة�����������������     ����������     ���������੤�����੤�����੤������
 * �� Shift  �� Z �� X �� C �� V �� B �� N �� M ��< ,��> .��? /��  Shift   ��     �� �� ��     �� 1 �� 2 �� 3 ��   ��
 * �������������Щ����ة��Щ��ة����Щة������ة������ة������ة������ة������ة����Щة������੤�����ةЩ��������Щ��������� ���������੤�����੤������ ���������ة������੤������ E����
 * �� Ctrl�� Win�� Alt��         Space         �� Alt�� Win��Menu��Ctrl�� �� �� �� �� �� �� �� ��   0   �� . ����������
 * �������������ة��������ة��������ة����������������������������������������������ة��������ة��������ة��������ة��������� ���������ة������ة������� �����������������ة������ة�������
 */
