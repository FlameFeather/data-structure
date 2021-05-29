#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include <iostream>
#include <cstdio>
#include <cstring>
typedef long long ll;
ll n, x, a[200005], nums = 1, head[400005], ans[400001], k;
struct edge
{
	ll next, w, to;
}E[400005];
void add(ll from, ll to, ll w)
{
	E[nums].to = to;
	E[nums].w = w;
	E[nums].next = head[from];
	head[from] = nums++; //边的总数加1 并跟新该出发点链表尾部元素
}
void dfs(int x, int fa)
{
	ans[++k] = x;
	a[x] *= -1;
	for (ll i = head[x]; i; i = E[i].next)
	{
		if (E[i].to == fa)
			continue;
		dfs(E[i].to, x);
		ans[++k] = x;
		a[x] *= -1;
	}
	if (a[x] == -1)
	{
		if (x != 1)
		{
			ans[++k] = fa;
			a[fa] *= -1;
			ans[++k] = x;
			a[x] = 1;
		}
		else
		{
			ans[++k] = E[head[1]].to;
			ans[++k] = 1;
			ans[++k] = E[head[1]].to;
		}
	}
}
int main()
{
	scanf_s("%lld", &n);
	for (ll i = 1; i <= n; i++)
	{
		scanf_s("%lld", &a[i]);
	}
	for (ll i = 1; i <= n - 1; i++)
	{
		ll x, y;
		scanf_s("%lld%lld", &x, &y);
		add(x, y, 0);
		add(y, x, 0);
	}
	a[1] *= -1;
	dfs(1, 0);
	for (ll i = 1; i <= k; ++i)
	{
		printf("%lld ", ans[i]);
	}
	return 0;
}