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
bool dp[100001];
int n, m;
int val[101], num[101];
int main()
{
	dp[0] = 1;
	while (~scanf("%d %d", &n, &m))
	{
		if (n == 0 && m == 0)break;
		for (int i = 1; i <= n; ++i)scanf("%d", &val[i]);
		for (int i = 1; i <= n; ++i)scanf("%d", &num[i]);
		for (int i = 1; i <= m; ++i)dp[i] = 0;
		int ans = 0;

		for (int i = 1; i <= n; ++i)
		{
			int cnt = num[i];
			for (int k = 1; k <= cnt; k <<= 1)
			{
				for (int j = m; j >= val[i] * k; --j)
				{
					dp[j] |= dp[j - val[i] * k];
				}
				cnt -= k;
			}

			if (!cnt)continue;
			for (int j = m; j >= val[i] * cnt; --j)
			{
				dp[j] |= dp[j - val[i] * cnt];
			}
		}

		for (int i = 1; i <= m; ++i)ans += dp[i];
		printf("%d\n", ans);
	}
	return 0;
}