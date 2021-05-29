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
#include<stack>
#include<istream>
#include<iostream>
#include<algorithm>
#include<queue>
#include<memory.h>
#include<set>
#include<unordered_map>
using namespace std;
typedef long long ll;
vector<pair<ll, ll>>bead[1000006];
ll dp0[1000006][2], dp1[1000006][2];
ll f[1000006][2], ff[1000006];
int main()
{
	ll t; scanf("%lld", &t);
	while (t--)
	{
		ll n, m; scanf("%lld%lld", &n, &m);
		for (ll i = 1; i <= n; i++)bead[i].clear(), ff[i] = 1;
		for (ll i = 1; i <= n; i++)
		{
			pair<ll, ll>x;
			bead[i].push_back(x);
			for (ll j = 1; j <= m; j++)
			{
				pair<ll, ll>x;
				scanf("%lld", &x.first);
				bead[i].push_back(x);
			}
		}
		ll FFF = 0;
		for (ll i = 1; i <= n; i++)
		{
			for (ll j = 1; j <= m; j++)
			{
				ll x;
				scanf("%lld", &x);
				bead[i][j].second = x;
				ff[i] = min(ff[i], x);
			}
			if (ff[i] == ff[i - 1] && ff[i] == 1)FFF = 1;
		}
		if (n == 1)
		{
			ll yy = 0;
			for (ll i = 1; i <= m; i++)yy = max(yy, bead[1][i].first);
			printf("%lld\n", yy);
			continue;
		}
		if (ff[1] == ff[n] && ff[1] == 1)FFF = 1;
		/*if (FFF)
		{
			printf("-1\n");
			continue;
		}*/
		ll maxn = -5;
		f[1][0] = f[1][1] = 0;
		ll f1 = 1, f2 = 1;
		for (ll i = 1; i <= n; i++)
		{
			f[i + 1][0] = f[i + 1][1] = 0;
			for (ll j = 1; j <= m; j++)
			{
				if (j == 1)dp0[i][0] = dp0[i][1] = 0;
				if (i == 1)
				{
					if (bead[i][j].second == 0)dp0[i][0] = max(dp0[i][0], bead[i][j].first), f[i][0] = 1;
				}
				else
				{
					if (bead[i][j].second == 0)
					{
						if (f[i - 1][0])dp0[i][0] = max(dp0[i][0], bead[i][j].first + dp0[i - 1][0]), f[i][0] = 1;
						if (f[i - 1][1])dp0[i][0] = max(dp0[i][0], bead[i][j].first + dp0[i - 1][1]), f[i][0] = 1;
					}
					else
					{
						if (f[i - 1][0])dp0[i][1] = max(dp0[i][1], bead[i][j].first + dp0[i - 1][0]), f[i][1] = 1;
					}
				}
			}
			if (f[i][0] + f[i][1] == 0)
			{
				f1 = 0; goto line1;
			}
		}
		maxn = max(dp0[n][0], dp0[n][1]);
	line1:;
		f[1][0] = f[1][1] = 0;
		for (ll i = 1; i <= n; i++)
		{
			f[i + 1][0] = f[i + 1][1] = 0;
			for (ll j = 1; j <= m; j++)
			{
				if (j == 1)dp1[i][0] = dp1[i][1] = 0;
				if (i == 1)
				{
					if (bead[i][j].second == 1)dp1[i][1] = max(dp1[i][1], bead[i][j].first), f[i][1] = 1;
				}
				else
				{
					if (bead[i][j].second == 0)
					{
						if (f[i - 1][0])dp1[i][0] = max(dp1[i][0], bead[i][j].first + dp1[i - 1][0]), f[i][0] = 1;
						if (f[i - 1][1])dp1[i][0] = max(dp1[i][0], bead[i][j].first + dp1[i - 1][1]), f[i][0] = 1;
					}
					else
					{
						if (f[i - 1][0])dp1[i][1] = max(dp1[i][1], bead[i][j].first + dp1[i - 1][0]), f[i][1] = 1;
					}
				}
			}
			if (f[i][0] + f[i][1] == 0) {
				f2 = 0; goto line2;
			}
		}
		maxn = max(maxn, dp1[n][0]);
	line2:;
		if (f1 == f2 && f1 == 0)printf("-1\n");
		else printf("%lld\n", maxn);
	}
	return 0;
}