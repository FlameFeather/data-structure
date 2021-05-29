#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<ctype.h>
#include<cstdlib>
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>
#include<queue>
#include<memory.h>
#include<set>
using namespace std;
typedef long long ll;
const ll maxn = 1e6;
struct as
{
	ll l, r, sum;
}hjt[maxn * 40];
ll a[maxn], root[maxn], cnt;
vector<ll>v;
ll getid(ll x)
{
	return lower_bound(v.begin(), v.end(), x) - v.begin() + 1;
}
void insert(ll l, ll r, ll pre, ll* now, ll p)
{
	hjt[++cnt] = hjt[pre];
	*now = cnt;
	hjt[*now].sum++;
	if (l == r)return;
	ll mid = (l + r) >> 1;
	if (p <= mid)
	{
		return insert(l, mid, hjt[pre].l, &hjt[*now].l, p);
	}
	else
	{
		return insert(mid + 1, r, hjt[pre].r, &hjt[*now].r, p);
	}
}
ll query(ll l, ll r, ll L, ll R, ll k)
{
	if (l == r)return l;
	ll mid = (l + r) >> 1;
	ll tmp = hjt[hjt[R].l].sum - hjt[hjt[L].l].sum;
	if (k <= tmp)
	{
		return query(l, mid, hjt[L].l, hjt[R].l, k);
	}
	else
	{
		return query(mid + 1, r, hjt[L].r, hjt[R].r, k - tmp);
	}
}
int main()
{
	ll n, m;
	cin >> n >> m;
	for (ll i = 1; i <= n; i++)
	{
		scanf("%lld", &a[i]);
		v.push_back(a[i]);
	}
	sort(v.begin(), v.end());
	v.erase(unique(v.begin(), v.end()), v.end());
	for (ll i = 1; i <= n; i++)
	{
		insert(1, n, root[i - 1], &root[i], getid(a[i]));
	}
	while (m--)
	{
		ll l, r, k;
		scanf("%lld%lld%lld", &l, &r, &k);
		printf("%lld\n", v[query(1, n, root[l - 1], root[r], k) - 1]);
	}
	return 0;
}