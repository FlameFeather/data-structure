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
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define per(i,a,b) for(int i=(a);i>=(b);i--)
const int N = 1e5 + 5;
const int mod = 1e9 + 7;
int n, m, t, q;

char a[N];
int num[N];



typedef vector<ll> VI;
///BM: 解决递推式.请保证模数的平方不会爆long long!!!
///不用全抄,需要那一部分,就抄哪一部分.
class Linear_Seq {
public:
    static const ll N = 50010;///多项式系数最大值
    ll res[N], c[N], hu[N], COEF[N];///COEF是多项式系数
    ll mod;
    vector<ll> MD;
    inline static ll exgcd(ll a, ll b, ll& x, ll& y) {
        if (!b) { x = 1; y = 0; return a; }
        ll d = exgcd(b, a % b, y, x);
        y -= (a / b) * x;
        return d;
    }
    static ll inv(ll a, ll mod) {
        ll x, y;
        return exgcd(a, mod, x, y) == 1 ? (x % mod + mod) % mod : -1;
    };
    inline void mul(ll* a, ll* b, ll k) {///下边的线性齐次递推用的.
        fill(c, c + 2 * k, 0);
        for (ll i = 0; i < k; ++i) if (a[i]) for (ll j = 0; j < k; ++j)
            c[i + j] = (c[i + j] + a[i] * b[j]) % mod;
        for (ll i = 2 * k - 1; i >= k; --i) if (c[i])for (ll j = 0; j < MD.size(); ++j)
            c[i - k + MD[j]] = (c[i - k + MD[j]] - c[i] * hu[MD[j]]) % mod;
        copy(c, c + k, a);
    }
    ll solve(ll n, VI A, VI B) {///线性齐次递推:A系数,B初值B[n]=A[0]*B[n-1]+...
        ///这里可以可以单独用,给出递推系数和前几项代替矩阵快速幂求递推式第n项.
        ll ans = 0, cnt = 0;
        ll k(A.size());
        for (ll i = 0; i < k; ++i) hu[k - i - 1] = -A[i];
        hu[k] = 1; MD.clear();
        for (ll i = 0; i < k; ++i) {
            res[i] = 0;
            if (hu[i])MD.push_back(i);
        }
        res[0] = 1;
        while ((1ll << cnt) <= n) ++cnt;
        for (ll p = cnt; ~p; --p) {
            mul(res, res, k);
            if ((n >> p) & 1) {
                copy(res, res + k, res + 1); res[0] = 0;
                for (ll j = 0; j < MD.size(); ++j)
                    res[MD[j]] = (res[MD[j]] - res[k] * hu[MD[j]]) % mod;
            }
        }
        for (ll i = 0; i < k; ++i) ans = (ans + res[i] * B[i]) % mod;
        return ans + (ans < 0 ? mod : 0);
    }
    ///1-st***********模数是质数用这里*******************/
    VI BM(VI s) {///BM算法求模数是质数的递推式子的通项公式,可以单独用
        VI C(1, 1), B(1, 1);
        ll L = 0, m = 1, b = 1;
        for (ll n = 0; n < s.size(); ++n) {
            ll d = 0;
            for (ll i = 0; i <= L; ++i) d = (d + C[i] * s[n - i]) % mod;
            if (!d) ++m;
            else {
                VI T = C;
                ll c(mod - d * inv(b, mod) % mod);
                while (C.size() < B.size() + m) C.push_back(0);
                for (ll i = 0; i < B.size(); ++i)
                    C[i + m] = (C[i + m] + c * B[i]) % mod;
                if (2 * L <= n) { L = n + 1 - L; B = T; b = d; m = 1; }
                else ++m;
            }
        }
        /** //下边这样写能够输出递推式的系数. printf("F[n] = ") ; for(ll i(0);i<C.size();++i) { COEF[i+1] = min(C[i],mod-C[i]) ; // if(i>0) { if(i != 1) printf(" + ") ; printf("%lld*F[n-%d]",COEF[i+1],i+1) ; putchar(i+1==C.size()?'\n':' ') ; // } } */
        return C;
    }
    ///1-ed*************模数是质数用这里*******************/
    ///2-st*************模数非质数用这里*******************/
    inline static void extand(VI& a, ll d, ll value = 0) {
        if (d <= a.size()) return; a.resize(d, value);
    }
    static ll CRT(const VI& c, const VI& m) {///中国剩余定理合并
        ll n = c.size();
        ll M = 1, ans = 0;
        for (ll i = 0; i < n; ++i) M *= m[i];
        for (ll i = 0; i < n; ++i) {
            ll x, y, tM(M / m[i]);
            exgcd(tM, m[i], x, y);
            ans = (ans + tM * x * c[i] % M) % M;
        }
        return (ans + M) % M;
    }
    static VI ReedsSloane(const VI& s, ll mod) {///求模数不是质数的递推式系数
        auto L = [](const VI& a, const VI& b) {
            ll da = (a.size() > 1 || (a.size() == 1 && a[0])) ? a.size() - 1 : -1000;
            ll db = (b.size() > 1 || (b.size() == 1 && b[0])) ? b.size() - 1 : -1000;
            return max(da, db + 1);
        };
        auto prime_power = [&](const VI& s, ll mod, ll p, ll e) {
            vector<VI> a(e), b(e), an(e), bn(e), ao(e), bo(e);
            VI t(e), u(e), r(e), to(e, 1), uo(e), pw(e + 1);;
            pw[0] = 1;
            for (ll i = 1; i <= e; ++i) pw[i] = pw[i - 1] * p;
            for (ll i = 0; i < e; ++i) {
                a[i] = { pw[i] }; an[i] = { pw[i] };
                b[i] = { 0 }; bn[i] = { s[0] * pw[i] % mod };
                t[i] = s[0] * pw[i] % mod;
                if (!t[i]) { t[i] = 1; u[i] = e; }
                else for (u[i] = 0; t[i] % p == 0; t[i] /= p, ++u[i]);
            }
            for (ll k = 1; k < s.size(); ++k) {
                for (ll g = 0; g < e; ++g) {
                    if (L(an[g], bn[g]) > L(a[g], b[g])) {
                        ll id = e - 1 - u[g];
                        ao[g] = a[id]; bo[g] = b[id];
                        to[g] = t[id]; uo[g] = u[id];
                        r[g] = k - 1;
                    }
                }
                a = an; b = bn;
                for (ll o = 0; o < e; ++o) {
                    ll d = 0;
                    for (ll i = 0; i < a[o].size() && i <= k; ++i)
                        d = (d + a[o][i] * s[k - i]) % mod;
                    if (d == 0) { t[o] = 1; u[o] = e; }
                    else {
                        for (u[o] = 0, t[o] = d; !(t[o] % p); t[o] /= p, ++u[o]);
                        ll g = e - 1 - u[o];
                        if (!L(a[g], b[g])) {
                            extand(bn[o], k + 1);
                            bn[o][k] = (bn[o][k] + d) % mod;
                        }
                        else {
                            ll coef = t[o] * inv(to[g], mod) % mod * pw[u[o] - uo[g]] % mod;
                            ll m = k - r[g];
                            extand(an[o], ao[g].size() + m); extand(bn[o], bo[g].size() + m);
                            auto fun = [&](vector<VI>& vn, vector<VI>& vo, bool f) {
                                for (ll i = 0; i < vo[g].size(); ++i) {
                                    vn[o][i + m] -= coef * vo[g][i] % mod;
                                    if (vn[o][i + m] < 0)vn[o][i + m] += mod * (f ? 1 : -1);
                                }
                                while (vn[o].size() && !vn[o].back())vn[o].pop_back();
                            };
                            fun(an, ao, 1); fun(bn, bo, -1);
                        }
                    }
                }
            }
            return make_pair(an[0], bn[0]);
        };
        vector<tuple<ll, ll, ll> >fac;
        for (ll i = 2; i * i <= mod; ++i)
            if (!(mod % i)) {
                ll cnt = 0, pw = 1;
                while (!(mod % i)) { mod /= i; ++cnt; pw *= i; }
                fac.emplace_back(pw, i, cnt);
            }
        if (mod > 1)fac.emplace_back(mod, mod, 1);
        vector<VI> as;
        ll n = 0;
        for (auto&& x : fac) {
            ll mod, p, e;
            VI a, b;
            std::tie(mod, p, e) = x;
            auto ss = s;
            for (auto&& x : ss) x %= mod;
            std::tie(a, b) = prime_power(ss, mod, p, e);
            as.emplace_back(a);
            n = max(n, (ll)a.size());
        }
        VI a(n), c(as.size()), m(as.size());
        for (ll i = 0; i < n; ++i) {
            for (ll j = 0; j < as.size(); ++j) {
                m[j] = std::get<0>(fac[j]);
                c[j] = i < as[j].size() ? as[j][i] : 0;
            }
            a[i] = CRT(c, m);
        }
        return a;
    }
    ///2-ed***********模数非质数用这里*******************/
    ll solve(VI a, ll n, ll mod, bool prime = true) {
        VI c; this->mod = mod;
        if (prime) c = BM(a);///如果已经知道系数了,直接输入到c就行了,不用调用BM().
        else c = ReedsSloane(a, mod);
        c.erase(c.begin());
        for (ll i = 0; i < c.size(); ++i) c[i] = (mod - c[i]) % mod;
        return solve(n, c, VI(a.begin(), a.begin() + c.size()));
    }
}BMEX;
///BMEX.slove(初始值vector[从0开始],要得到的项数,模数,模数是不是质数)
///质数为1，非质数为0
ll f[2025], sum[2025];
ll quickpow(ll a, ll b, ll mod) {
    ll ans = 1;
    a %= mod;
    while (b) {
        if (b & 1)ans = ans * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return ans % mod;
}


int main() {
    ll res = 1;
    VI ans;
    ans.clear();
    ans.push_back(1);
    ans.push_back(1);
    ans.push_back(2);
    ans.push_back(3);

    res = (res * BMEX.solve(ans, num[1], mod, 1)) % mod;
    printf("%I64d\n", res);
    return 0;
}