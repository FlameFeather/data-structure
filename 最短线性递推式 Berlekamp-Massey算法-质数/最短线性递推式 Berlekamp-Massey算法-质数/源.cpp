//#pragma GCC optimize(2)
//std::ios::sync_with_stdio(false)
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<ctype.h>
#include<cstdlib>
#include<string>
#include<string.h>
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
#include <cassert>
using namespace std;
typedef long long ll;
#define rep(i,a,n) for(int i=a;i<n;i++)
#define SZ(x) ((int)(x).size())
typedef vector<int> VI;
const ll mod = 1e9 + 7;
ll powmod(ll a, ll b)
{
	ll ret = 1;
	a %= mod;
	while (b)
	{
		if (b & 1)
			ret = ret * a % mod;
		a = a * a % mod;
		b >>= 1;
	}
	return ret;
}
int _, n;
namespace linear_seq
{
	const int N = 10010;
	ll res[N], base[N], _c[N], _md[N];
	vector<int> Md;
	void mul(ll* a, ll* b, int k)
	{
		for (int i = 0; i < k + k; i++)
			_c[i] = 0;
		for (int i = 0; i < k; ++i)
			if (a[i])
				for (int j = 0; j < k; j++)
					_c[i + j] = (_c[i + j] + a[i] * b[j]) % mod;
		for (int i = k + k - 1; i >= k; i--)
			if (_c[i])
				for (int j = 0; j < (int)Md.size(); j++)
					_c[i - k + Md[j]] = (_c[i - k + Md[j]] - _c[i] * _md[Md[j]]) % mod;
		for (int i = 0; i < k; i++)
			a[i] = _c[i];
	}

	int solve(ll n, VI a, VI b)
	{
		ll ans = 0, pnt = 0;
		int k = SZ(a);
		for (int i = 0; i < k; i++)
			_md[k - 1 - i] = -a[i];
		_md[k] = 1;
		Md.clear();
		for (int i = 0; i < k; i++)
			if (_md[i] != 0)
				Md.push_back(i);
		for (int i = 0; i < k; i++)
			res[i] = base[i] = 0;
		res[0] = 1;
		while ((1ll << pnt) <= n)pnt++;
		for (int p = pnt; p >= 0; p--)
		{
			mul(res, res, k);
			if ((n >> p) & 1)
			{
				for (int i = k - 1; i >= 0; i--)
					res[i + 1] = res[i];
				res[0] = 0;
				for (int j = 0; j < (int)Md.size(); ++j)
					res[Md[j]] = (res[Md[j]] - res[k] * _md[Md[j]]) % mod;
			}
		}
		rep(i, 0, k) ans = (ans + res[i] * b[i]) % mod;
		if (ans < 0)ans += mod;
		return ans;
	}
	VI BM(VI s)
	{
		VI C(1, 1), B(1, 1);
		int L = 0, m = 1, b = 1;
		for (int n = 0; n < (int)s.size(); ++n)
		{
			ll d = 0;
			for (int i = 0; i < L + 1; i++)
				d = (d + (ll)C[i] * s[n - i]) % mod;
			if (d == 0)++m;
			else if (2 * L <= n)
			{
				VI T = C;
				ll c = mod - d * powmod(b, mod - 2) % mod;
				while (SZ(C) < SZ(B) + m)C.push_back(0);
				for (int i = 0; i < (int)B.size(); i++)
					C[i + m] = (C[i + m] + c * B[i]) % mod;
				L = n + 1 - L;
				B = T;
				b = d;
				m = 1;
			}
			else
			{
				ll c = mod - d * powmod(b, mod - 2) % mod;
				while (SZ(C) < SZ(B) + m)C.push_back(0);
				for (int i = 0; i < (int)B.size(); i++)
					C[i + m] = (C[i + m] + c * B[i]) % mod;
				++m;
			}
		}
		return C;
	}
	ll gao(VI a, ll n)
	{
		VI c = BM(a);
		c.erase(c.begin());
		for (int i = 0; i < (int)c.size(); i++)
			c[i] = (mod - c[i]) % mod;
		return (ll)solve(n, c, VI(a.begin(), a.begin() + SZ(c)));
	}
}
int main()
{
	ll A, B;
	ll nnn;
	VI a;//下面几行是“找规律”的前几个数字
	a.push_back(0);
	a.push_back(0);
	a.push_back(0);
	a.push_back(1);
	a.push_back(4);
	a.push_back(12);
	a.push_back(31);
	a.push_back(76);
	a.push_back(180);
	ll t; scanf("%lld", &t);
	while (t--)
	{
		ll x; scanf("%lld", &x);//找第x个数
		printf("%lld\n", linear_seq::gao(a, x - 1));
	}
}
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