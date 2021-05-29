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
vector<ll>xx;
vector<ll> mul(vector<ll>& A, ll b)
{
	vector<ll> C;//结果数组
	ll t = 0;
	for (ll i = 0; i < A.size() || t; i++)
	{
		if (i < A.size()) t += A[i] * b;
		C.push_back(t % 10);
		t /= 10;
	}
	return C;
}
int main()
{
	ll t;
	scanf("%lld", &t);
	while (t--)
	{
		xx.clear();
		ll n, s = 0;
		scanf("%lld", &n);
		for (ll i = 1; i <= n; i++)
		{
			ll x;
			scanf("%lld", &x);
			if (x == 0)
			{
				s++;
			}
			else
			{
				xx.push_back(x);
			}
		}
		sort(xx.begin(), xx.end());
		ll y, I, b;
		vector<ll> a;
		b = xx[0];
		for (auto it = xx.begin() + 1; it != xx.end(); it++)
		{
			if (it == xx.begin() + 1)
			{
				a.push_back(*it);
				for (ll j = 1; j <= s; j++)
				{
					a.push_back(0);
				}
			}
			else
			{
				a.push_back(*it);
			}
		}
		reverse(a.begin(), a.end());
		auto C = mul(a, b);
		for (ll i = C.size() - 1; i >= 0; i--) printf("%lld", C[i]);
		printf("\n");
	}
	return 0;
}