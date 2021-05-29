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
using namespace std;
typedef long long ll;
const ll mod = 1e9 + 7;
ll a[1000006];
ll ksm(ll a, ll b, ll p)
{
	ll res = 1;
	while (b)
	{
		if (b & 1)
			res = res * a % p;
		b >>= 1;
		a = a * a % p;
	}
	return res;
}
ll c(ll x, ll y)
{
	ll s = 1, Y = y;
	for (ll i = x; i > x - y; i--)
	{
		s = s * i % mod * ksm(Y, mod - 2, mod) % mod;
		Y--;
	}
	return s;
}
int main()
{
	ll n; cin >> n;
	a[1] = 1; a[2] = 2;
	for (ll i = 3; i <= n; i++)
	{
		a[i] = (a[i - 1] + (i - 1) * a[i - 2]) % mod;
	}
	printf("%lld\n", a[n]);
	return 0;
}