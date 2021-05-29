#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<ctype.h>
#include<cstdlib>
#include <vector>
#include <iostream>
#include <algorithm>
#include<queue>
#include<memory.h>
using namespace std;
typedef long long ll;
ll not_prime[1000006], prime[1000006], mu[1000006], tot;
ll cnta[1000006], cntb[1000006], ansa[1000006], ansb[1000006], a[1000006], b[1000006];
void Prime()
{
	tot = 0;
	mu[1] = 1; not_prime[0] = not_prime[1] = 0;
	for (ll i = 2; i <= 1000005; i++)
	{
		if (!not_prime[i])prime[++tot] = i, mu[i] = -1;
		for (ll j = 1; j <= tot; j++)
		{
			if (i * prime[j] >= 1000005)break;
			not_prime[i * prime[j]] = 1;
			if (i % prime[j] == 0)
			{
				mu[i * prime[j]] = 0;
				break;
			}
			else
			{
				mu[i * prime[j]] = -mu[i];
			}
		}
	}
}
int main()
{
	Prime();
	ll n, m;
	scanf("%lld %lld", &n, &m);
	for (ll i = 1; i <= n; i++)
	{
		scanf("%lld", &a[i]);
		cnta[a[i]]++;
	}
	for (ll i = 1; i <= m; i++)
	{
		scanf("%lld", &b[i]);
		cntb[b[i]]++;
	}
	for (ll i = 1; i <= 1000005; i++)
	{
		ll aa = 0, bb = 0;
		if (mu[i])
		{
			for (ll j = i; j <= 1000005; j += i)
			{
				aa += cnta[j];
				bb += cntb[j];
			}
			for (ll j = i; j <= 1000005; j += i)
			{
				ansa[j] += mu[i] * bb;
				ansb[j] += mu[i] * aa;
			}
		}
	}
	for (ll i = 1; i <= n; ++i)
	{
		printf("%lld%c", ansa[a[i]], i == n ? '\n' : ' ');
	}
	for (ll i = 1; i <= m; ++i)
	{
		printf("%lld%c", ansb[b[i]], i == m ? '\n' : ' ');
	}
	return 0;
}