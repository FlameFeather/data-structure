#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include <iostream>
#include <cstdio>
#include <cstring>
typedef long long ll;
const ll mod = 1e9 + 7;
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
long long fact[2000001], inv[2000001];//2倍空间

void init(long long n = 2000001)
{
	fact[0] = 1;
	for (long long i = 1; i <= n; i++)
		fact[i] = (long long)i * fact[i - 1] % mod;
	inv[1] = 1;
	for (long long i = 2; i <= n; i++)
		inv[i] = mod - (long long)(mod / i) * inv[mod % i] % mod;
	inv[0] = 1;
	for (long long i = 1; i <= n; i++)
		inv[i] = (long long)inv[i - 1] * inv[i] % mod;
}

long long c(long long n, long long m)
{
	return (long long)fact[n] * inv[m] % mod * inv[n - m] % mod;
}




//扩展卢卡斯定理
long long POW_mod(long long a, long long b, long long mod)
{
    long long ans = 1;
    while (b)
    {
        if (b & 1) ans = ans * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return ans;
}

long long POW(long long a, long long b)
{
    long long ans = 1;
    while (b)
    {
        if (b & 1) ans = ans * a;
        a = a * a;
        b >>= 1;
    }
    return ans;
}

long long exGcd(long long a, long long b, long long& x, long long& y)
{
    long long t, d;
    if (!b)
    {
        x = 1;
        y = 0;
        return a;
    }
    d = exGcd(b, a % b, x, y);
    t = x;
    x = y;
    y = t - a / b * y;
    return d;
}

bool modular(long long a[], long long m[], long long k)
{
    long long d, t, c, x, y, i;

    for (i = 2; i <= k; i++)
    {
        d = exGcd(m[1], m[i], x, y);
        c = a[i] - a[1];
        if (c % d) return false;
        t = m[i] / d;
        x = (c / d * x % t + t) % t;
        a[1] = m[1] * x + a[1];
        m[1] = m[1] * m[i] / d;
    }
    return true;
}

long long reverse(long long a, long long b)
{
    long long x, y;
    exGcd(a, b, x, y);
    return (x % b + b) % b;
}

long long C(long long n, long long m, long long mod)
{
    if (m > n) return 0;
    long long ans = 1, i, a, b;
    for (i = 1; i <= m; i++)
    {
        a = (n + 1 - i) % mod;
        b = reverse(i % mod, mod);
        ans = ans * a % mod * b % mod;
    }
    return ans;
}

long long C1(long long n, long long m, long long mod)
{
    if (m == 0) return 1;
    return C(n % mod, m % mod, mod) * C1(n / mod, m / mod, mod) % mod;
}

long long cal(long long n, long long p, long long t)
{
    if (!n) return 1;
    long long x = POW(p, t), i, y = n / x, temp = 1;
    for (i = 1; i <= x; i++) if (i % p) temp = temp * i % x;
    long long ans = POW_mod(temp, y, x);
    for (i = y * x + 1; i <= n; i++) if (i % p) ans = ans * i % x;
    return ans * cal(n / p, p, t) % x;
}

long long C2(long long n, long long m, long long p, long long t)
{
    long long x = POW(p, t);
    long long a, b, c, ap = 0, bp = 0, cp = 0, temp;
    for (temp = n; temp; temp /= p) ap += temp / p;
    for (temp = m; temp; temp /= p) bp += temp / p;
    for (temp = n - m; temp; temp /= p) cp += temp / p;
    ap = ap - bp - cp;
    long long ans = POW_mod(p, ap, x);
    a = cal(n, p, t);
    b = cal(m, p, t);
    c = cal(n - m, p, t);
    ans = ans * a % x * reverse(b, x) % x * reverse(c, x) % x;
    return ans;
}

//计算C(n,m)%mod
long long Lucas(long long n, long long m, long long mod)
{
    long long i, t, cnt = 0;
    long long A[205], M[205];
    for (i = 2; i * i <= mod; i++) if (mod % i == 0)
    {
        t = 0;
        while (mod % i == 0)
        {
            t++;
            mod /= i;
        }
        M[++cnt] = POW(i, t);
        if (t == 1) A[cnt] = C1(n, m, i);
        else A[cnt] = C2(n, m, i, t);
    }
    if (mod > 1)
    {
        M[++cnt] = mod;
        A[cnt] = C1(n, m, mod);
    }
    modular(A, M, cnt);
    return A[1];
}

void init()
{
    b[0] = 1, b[1] = 0, b[2] = 1;
    for (long long i = 3; i <= 500000; i++)
        b[i] = (b[i - 1] + b[i - 2]) % mod * (i - 1) % mod;

}


int main()
{
	return 0;
}