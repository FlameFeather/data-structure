//pragma GCC optimize(2)
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<ctype.h>
#include<cstdlib>
#include<vector>
#include<map>
#include<time.h>
#include<iostream>
#include<algorithm>
#include<queue>
#include<memory.h>
#include<set>
#include<unordered_map>
#include<cstdlib>
#include <random>
#include <windows.h>
#pragma comment( lib,"winmm.lib" )
using namespace std;
typedef long long ll;
struct as
{
	ll last, v, next;
}a[1000006];
struct ovo
{
	ll now, v, next;
}c[1000006];
int main()
{
	LARGE_INTEGER t1, t2, tc;
	QueryPerformanceFrequency(&tc);
	QueryPerformanceCounter(&t1);
	//freopen("G:\\学妹题.in", "r", stdin);
	freopen("C:\\Users\\000\\Desktop\\新建文件夹 (2)\\新建文件夹\\学妹的链表.in", "r", stdin);
	freopen("C:\\Users\\000\\Desktop\\新建文件夹 (2)\\新建文件夹\\学妹的链表.out", "w", stdout);
	ll head, n;
	while (scanf("%lld%lld", &head, &n) != EOF)
	{
		memset(a, 0, sizeof(a));
		memset(c, 0, sizeof(c));
		for (ll i = 1; i <= n; i++)
		{
			ll x, y, z;
			scanf("%lld%lld%lld", &x, &y, &z);
			if (a[x].next != 0 || a[x].v != 0)continue;
			a[x].v = y;
			a[x].next = z;
		}
		ll x = head;
		for (ll i = head; i != -1; i = a[i].next)
		{
			a[i].last = x;
			x = i;
		}
		ll f = 0;
		ll xx = -1;
		for (ll i = head; i != -1; i = a[i].next)
		{
			if (a[i].v < a[a[i].last].v)
			{
				if (xx == 1)c[f - 1].next = i;
				c[f].now = i;
				c[f].next = -1;
				c[f].v = a[i].v;
				f++;
				xx = 1;
				a[a[i].last].next = a[i].next;
				if (a[i].next != -1)a[a[i].next].last = a[i].last;
			}
		}
		for (ll i = head; i != -1; i = a[i].next)
		{
			if (a[i].next == -1)
			{
				printf("%05lld %lld -1\n", i, a[i].v);
			}
			else printf("%05lld %lld %05lld\n", i, a[i].v, a[i].next);
		}
		for (ll i = 0; i < f; i++)
		{
			if (c[i].next == -1)
			{
				printf("%05lld %lld -1\n", c[i].now, c[i].v);
			}
			else  printf("%05lld %lld %05lld\n", c[i].now, c[i].v, c[i].next);
		}
	}
	QueryPerformanceCounter(&t2);
	printf("Use Time:%f\n", (t2.QuadPart - t1.QuadPart) * 1.0 / tc.QuadPart);
	return 0;
}