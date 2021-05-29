//pragma GCC optimize(2)
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<ctype.h>
#include<cstdlib>
#include<vector>
#include<map>
#include<time.h>
#include<iostream>
#include<algorithm>
#include<queue>
#include<memory.h>
#include<set>
#include<unordered_map>
#include<cstdlib>
#include <random>
#include <windows.h>
#pragma comment( lib,"winmm.lib" )
using namespace std;
typedef long long ll;
default_random_engine e(time(0));
ll Random()
{
	uniform_int_distribution<ll> u(1, 6);
	ll x = pow(10, u(e));
	uniform_int_distribution<ll> U(x / 10, x);
	return U(e);
}
uniform_int_distribution<ll> u(1, 500);
uniform_int_distribution<ll> U(1, 500);
int main()
{
	LARGE_INTEGER t1, t2, tc;
	QueryPerformanceFrequency(&tc);
	QueryPerformanceCounter(&t1);
	//freopen("G:\\学妹题.in", "r", stdin);
	freopen("C:\\Users\\000\\Desktop\\新建文件夹 (2)\\新建文件夹\\Ep走迷宫(hrd).in", "w", stdout);
	ll cnt = 100;
	while (cnt--)
	{
		ll n = u(e), m = u(e), q = u(e);
		printf("%lld %lld %lld\n", n, m, q);
		for (ll i = 1; i <= n; i++)
		{
			for (ll j = 1; j <= m; j++)
			{
				printf("%lld%c", U(e), j == m ? '\n' : ' ');
			}
		}
		uniform_int_distribution<ll> x(1, n);
		uniform_int_distribution<ll> y(1, m);
		for (ll i = 1; i <= q; i++)
		{
			printf("%lld %lld\n", x(e), y(e));
		}
	}
	QueryPerformanceCounter(&t2);
	//fclose(stdout);
	//printf("Use Time:%f\n", (t2.QuadPart - t1.QuadPart) * 1.0 / tc.QuadPart);
	return 0;
}