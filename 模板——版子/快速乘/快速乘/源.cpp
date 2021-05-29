#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
typedef long long ll;
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
int main()
{
	ll x, y,s;
	while ((scanf_s("%lld%lld",&x,&y))!=EOF)
	{
		s = ksc(x, y, 999999999);
		printf("%lld\n", s);
	}
	return 0;
}