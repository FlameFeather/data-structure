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
#include<stack>
#include<unordered_map>
#include<cstdlib>
using namespace std;
typedef long long ll;
//线段树——————区间修改，区间查询
//题意：一个线性数组，不断把某区间内的值修改“为”另一个输入值，查询区间内和。
#define maxn 1000006
ll num[maxn * 4];//开四倍空间
ll lazy[maxn * 4];

void push_up(ll root)//根节点状态更新
{
	num[root] = num[root * 2] + num[root * 2 + 1];
}
void build(ll l, ll r, ll root)//线段树建树
{
	if (l == r)
	{
		scanf("%lld", &num[root]);
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
	lazy[root * 2] += lazy[root];
	lazy[root * 2 + 1] += lazy[root];
	num[root * 2] += lazy[root] * (len - (len) / 2);
	num[root * 2 + 1] += lazy[root] * ((len) / 2);

	lazy[root] = 0;
}

void upgrade(ll la, ll rb, ll l, ll r, ll val, ll root)//线段更新
//la、rb为需更新的区间左、右端点，l、r为当前区间左、右端点，root为当前l、r对应的根存储位置
{
	if (la <= l && rb >= r)
	{
		num[root] += (r - l + 1) * val;
		lazy[root] += val;
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
	push_down(root, r - l + 1);
	if (l >= la && r <= rb)
	{
		return num[root];
	}
	ll mid = (l + r) / 2;
	ll ans = 0;
	if (la <= mid)
	{
		ans += query(la, rb, l, mid, root * 2);
	}
	if (rb > mid)
	{
		ans += query(la, rb, mid + 1, r, root * 2 + 1);
	}
	push_up(root);
	return ans;
}
int main()
{
	ll n, x;//原数组结点总数
	scanf("%lld%lld", &n, &x);
	build(1, n, 1);//建树
	while (x--)
	{
		ll ju;
		scanf("%lld", &ju);
		if (ju == 1)
		{
			ll la, rb, val;
			scanf("%lld%lld%lld", &la, &rb, &val);
			upgrade(la, rb, 1, n, val, 1);//更新[l,r]区间结点，每个结点都被更新“成”val
		}
		else
		{
			ll la, rb, val;
			scanf("%lld%lld", &la, &rb);
			printf("%lld\n", query(la, rb, 1, n, 1));//查询区间[la,rb]的值
		}
	}
	return 0;
}