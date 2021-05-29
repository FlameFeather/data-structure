#include<stdio.h>
#include<stdlib.h>
#include<string.h>
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
#include<unordered_map>
using namespace std;
typedef long long ll;
const ll mod = 1e9 + 7;
struct as
{
	ll a[3][3] = { 0,0,0,0,0,0,0,0,0 };
};
as mult(as a, as b)
{
	as c;
	for (ll i = 1; i <= 2; i++)
	{
		for (ll k = 1; k <= 2; k++)
		{
			for (ll j = 1; j <= 2; j++)
			{
				c.a[i][j] = (c.a[i][j] + a.a[i][k] * b.a[k][j] % mod) % mod;
			}
		}
	}
	return c;
}
as ksm(as a, ll b, ll p)
{
	as res;
	res.a[1][1] = 1, res.a[1][2] = 0, res.a[2][1] = 0, res.a[2][2] = 1;
	while (b)
	{
		if (b & 1)
			res = mult(res, a);
		b >>= 1;
		a = mult(a, a);
	}
	return res;
}
int main()
{
	ll n;
	scanf("%lld", &n);
	as x;
	x.a[1][1] = 0, x.a[1][2] = 1, x.a[2][1] = 1, x.a[2][2] = 1;
	as b = ksm(x, n - 1, mod);
	printf("%lld", (b.a[1][1] + b.a[1][2]) * (b.a[2][1] + b.a[2][2]) % mod);
	return 0;
}