#pragma GCC optimize(2)
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
#include<time.h>
#include<set>
#include<stack>
#include<unordered_map>
#include<complex>
using namespace std;
typedef long long ll;

struct node { double x, y; }s[300000];
ll t[300000];
ll n;
bool cmp(node a, node b)
{
	return a.x < b.x || (a.x == b.x && a.y < b.y);
}

double dis(ll a, ll b)
{
	return sqrt((s[a].x - s[b].x) * (s[a].x - s[b].x) + (s[a].y - s[b].y) * (s[a].y - s[b].y));
}
bool comp(ll a, ll b)
{
	return s[a].y < s[b].y;
}

double solve(ll l, ll r)
{
	double d = 1e9;
	if (l == r)	return d;
	if (l == r - 1)  return dis(l, r);
	ll m = l + (r - l) / 2;
	double d1 = solve(l, m);//分治求解 
	double d2 = solve(m + 1, r);
	d = min(d1, d2);
	ll k = 0;
	for (ll i = l; i <= r; i++)
		if (fabs(s[m].x - s[i].x) < d)//将横坐标之差小于d的取过来 
			t[++k] = i;
	sort(t + 1, t + k + 1, comp);//注意这里要排序 
	for (ll i = 1; i < k; i++)
	{
		for (ll j = i + 1; j <= k && s[t[j]].y - s[t[i]].y < d; j++)//如果纵坐标也满足要求，注意已经排过序的序列 
		{
			double d3 = dis(t[j], t[i]);
			d = min(d3, d);
		}
	}
	return d;

}
int main()
{
	while (scanf("%lld", &n) != EOF)
	{
		if (n == 0)break;
		for (ll i = 1; i <= n; i++)
			scanf("%lf%lf", &s[i].x, &s[i].y);
		sort(s + 1, s + n + 1, cmp);
		printf("%.2lf\n", solve(1, n) / 2);
	}
	return 0;
}
//https://www.luogu.com.cn/problem/P1257
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
