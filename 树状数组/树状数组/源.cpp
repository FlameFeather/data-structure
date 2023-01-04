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
ll n, m;
ll a[500006] = { 0 };
ll sum1[500006];    //(D[1] + D[2] + ... + D[n])
ll sum2[500006];    //(1*D[1] + 2*D[2] + ... + n*D[n])

ll lowbit(ll x) {
	return x & (-x);
}

void updata(ll i, ll k) {
	ll x = i;    //因为x不变，所以得先保存i值
	while (i <= n) {
		sum1[i] += k;
		sum2[i] += k * (x - 1);
		i += lowbit(i);
	}
}

ll getsum(ll i) {        //求前缀和
	ll res = 0, x = i;
	while (i > 0) {
		res += x * sum1[i] - sum2[i];
		i -= lowbit(i);
	}
	return res;
}

int main() {
	scanf("%lld%lld", &n, &m);
	for (ll i = 1; i <= n; i++) {
		scanf("%lld", &a[i]);
		updata(i, a[i] - a[i - 1]);   //输入初值的时候，也相当于更新了值
	}
	for (ll i = 1; i <= m; i++)
	{
		ll op; scanf("%lld", &op);
		if (op == 1)
		{
			ll x, y, k;
			scanf("%lld%lld%lld", &x, &y, &k);
			//[x,y]区间内加上k
			updata(x, k);    //A[x] - A[x-1]增加k
			updata(y + 1, -k);        //A[y+1] - A[y]减少k
		}
		else
		{
			ll x; scanf("%lld", &x);
			//求[x,y]区间和
			ll sum = getsum(x) - getsum(x - 1);
			printf("%lld\n", sum);
		}
	}
	return 0;
}
//https://www.luogu.com.cn/problem/P3368
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
