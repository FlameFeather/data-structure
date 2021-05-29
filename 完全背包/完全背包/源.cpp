//#pragma GCC optimize(2)
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
#include<cstdlib>
using namespace std;
typedef long long ll;
struct monster
{
    ll v, f;
}g[1000];
ll dp[100000], num[100000];
int main()
{
    ll n, m, k, s;
    while (scanf("%lld%lld%lld%lld", &n, &m, &k, &s) != EOF)
    {
        memset(dp, 0, sizeof dp);
        memset(num, 0, sizeof num);
        ll minn = 1e9;
        for (ll i = 1; i <= k; i++)scanf("%lld%lld", &g[i].v, &g[i].f);
        for (ll i = 1; i <= k; i++)
        {
            for (ll j = g[i].f; j <= m; j++)
            {
                if (num[j - g[i].f] + 1 <= s && dp[j - g[i].f] + g[i].v > dp[j])
                {
                    dp[j] = dp[j - g[i].f] + g[i].v;
                    num[j] = num[j - g[i].f] + 1;
                    if (dp[j] >= n)minn = min(minn, j);
                }
            }
        }
        if (minn == 1e9)printf("-1\n");
        else printf("%lld\n", m - minn);
    }
    return 0;
}