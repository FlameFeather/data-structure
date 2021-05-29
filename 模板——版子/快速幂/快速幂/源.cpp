#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
typedef long long ll;
ll qpow(ll x, ll y, ll mod)
{
	ll s;
	if (y == 0)
	{
		return 1;
	}
	if (y % 2 == 0)
	{
		s = qpow(x, y / 2, mod) % mod;
		return s * s % mod;
	}
	else
	{
		return x * qpow(x, y - 1, mod) % mod;
	}
}
int main()
{
	ll s,a,b,c;
	while ((scanf_s("%lld",&a))!=EOF)
	{
		scanf_s("%lld%lld", &b, &c);
		scanf_s("%lld", &s);
		if (qpow(a, b, c) == s)
		{
			printf("YE5\n");
		}
		else
		{
			printf("N0\n");
		}
	}
	return 0;
}
//用循环和自定义函数实现快速乘与快速幂
ll ksc(ll a, ll b, ll p)
{
	ll res = 0;
	while (b)
	{
		if (b & 1)
			res = (res + a) % p;
		b >>= 1;
		a = (a + a) % p;
	}
	return res;
}

ll ksm(ll a, ll b, ll p)
{
	ll res = 1;
	while (b)
	{
		if (b & 1)
			res = ksc(res, a, p) % p;
		b >>= 1;
		a = ksc(a, a, p) % p;
	}
	return res;
}