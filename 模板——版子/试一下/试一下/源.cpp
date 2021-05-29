#include <iostream>
#include <cstdio>
#include <cstring>
typedef long long ll;
const ll maxn = 1000006;
ll num[maxn * 4];
ll lazy[maxn * 4];
bool judge[maxn * 4];
using namespace std;

void push_up(ll root)
{
    num[root] = num[root * 2] + num[root * 2 + 1];
}
void build(ll l, ll r, ll root)
{
    ll x;
    if (l == r)
    {
        scanf_s("%lld", &x);
        num[root] = x;
        return;
    }
    ll mid = (l + r) / 2;
    build(l, mid, root * 2);
    build(mid + 1, r, root * 2 + 1);
    push_up(root);
}

void push_down(ll root, ll len)
{
    if (judge[root] == 0)
        return;
    lazy[root * 2] = lazy[root];
    judge[root * 2] = 1;
    lazy[root * 2 + 1] = lazy[root];
    judge[root * 2 + 1] = 1;
    num[root * 2] = lazy[root * 2] * (len - (len) / 2);
    num[root * 2 + 1] = lazy[root * 2 + 1] * ((len) / 2);


    lazy[root] = 0;
    judge[root] = 0;
}

void upgrade(ll la, ll rb, ll l, ll r, ll val, ll root)
{
    if (la <= l && rb >= r)
    {
        num[root] = (r - l + 1) * val;
        lazy[root] = val;
        judge[root] = 1;
        return;
    }

    push_down(root, r - l + 1);

    ll mid = (l + r) / 2;
    if (la <= mid)
    {
        upgrade(la, rb, l, mid, val, root * 2);
    }
    if (rb > mid)
    {
        upgrade(la, rb, mid + 1, r, val, root * 2 + 1);
    }
    push_up(root);
}


ll query(ll la, ll rb, ll l, ll r, ll root)
{
    if (l >= la && r <= rb)
    {
        return num[root];
    }

    push_down(root, r - l + 1);

    ll mid = (l + r) / 2;
    ll ans = 0;
    if (la <= mid)
    {
        ans += query(la, rb, l, mid, root * 2);
    }
    if (rb > mid)
    {
        ans += query(la, rb, mid + 1, r, root * 2 + 1);
    }

    return ans;
}
int main()
{
    ll la, rb, val, p, x;
    ll N;
    scanf_s("%lld", &N);
    scanf_s("%lld", &x);
    //memset(num, 0, sizeof(num));
    memset(lazy, 0, sizeof(lazy));

    build(1, N, 1);
    while (x--)
    {
        scanf_s("%lld%lld", &la, &rb);
        p = query(la, rb, 1, N, 1);
        printf("%lld\n", p);
        upgrade(la, rb, 1, N, 0, 1);
    }
    return 0;
}