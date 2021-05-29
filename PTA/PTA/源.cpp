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
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;
const int maxn = 105;
int a[15];
int cnt[4005], dp[12][4005];
int main()
{
	int k, n;
	while (scanf("%d %d", &k, &n) != EOF)
	{
		for (int i = 0; i < n; ++i)
			scanf("%d", &a[i]);
		for (int i = 0; i < (1 << n); ++i)
		{
			int sum = 0;
			for (int j = 0; j < n; ++j)
			{
				if (i & (1 << j))
					sum += a[j];
			}
			cnt[i] = sum;
		}
		for (int i = 0; i < (1 << n); ++i)
			dp[1][i] = cnt[i];
		for (int i = 2; i <= k; ++i)
		{
			for (int j = 0; j < (1 << n); ++j)
			{
				dp[i][j] = 1 << 30;
				for (int l = j; l; l = (l - 1) & j)
				{
					dp[i][j] = min(dp[i][j], max(dp[i - 1][l], cnt[l ^ j]));
				}
			}
		}
		printf("%d\n", dp[k][(1 << n) - 1]);
	}
	return 0;
}
