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
#include<time.h>
#include<set>
#include<stack>
#include<unordered_map>
#include<complex>
using namespace std;
typedef long long ll;
const ll mod = 1e9 + 7;
struct node
{
	ll cnt, sum, sum2;
}dp[20][8][8];
ll a[20], powr[20];
node dfs(ll pos, ll sum, ll v, ll up)
{
	if (pos == 0)
	{
		node tmp;
		tmp.cnt = (sum && v);//数位和不是7的倍数且数字不是7的倍数
		tmp.sum = tmp.sum2 = 0;
		return tmp;
	}
	ll limt = (up ? a[pos] : 9);
	node ans; ans.cnt = ans.sum = ans.sum2 = 0;
	for (ll i = 0; i <= limt; i++)
	{
		if (i == 7)continue; node x;
		if (dp[pos - 1][(sum + i) % 7][(v * 10 + i) % 7].cnt == 0 || up)
			x = dfs(pos - 1, (sum + i) % 7, (v * 10 + i) % 7, (up && i == limt));
		else x = dp[pos - 1][(sum + i) % 7][(v * 10 + i) % 7];
		ans.cnt = (ans.cnt + x.cnt) % mod;
		ans.sum = (ans.sum + (x.sum + i * powr[pos] % mod * x.cnt % mod) % mod) % mod;
		ans.sum2 = (ans.sum2 + x.sum2 + i * 2 % mod * powr[pos] % mod * x.sum % mod + (i * powr[pos]) % mod * i % mod * powr[pos] % mod * x.cnt % mod) % mod;
	}
	if (!up) dp[pos][sum][v] = ans;
	return ans;
}
int main()
{
	powr[1] = 1;
	for (ll i = 2; i <= 19; i++)powr[i] = powr[i - 1] * 10 % mod;
	ll t; scanf("%lld", &t);
	while (t--)
	{
		ll l, r;
		scanf("%lld%lld", &l, &r);
		ll len = 0;
		l--;
		while (l)
		{
			a[++len] = l % 10;
			l /= 10;
		}
		node x = dfs(len, 0, 0, 1);
		len = 0;
		while (r)
		{
			a[++len] = r % 10;
			r /= 10;
		}
		node y = dfs(len, 0, 0, 1);
		printf("%lld\n", (y.sum2 - x.sum2 + mod) % mod);
	}
	return 0;
}
//http://acm.hdu.edu.cn/showproblem.php?pid=4507
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
