// 扩展欧几里得（最小解）.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

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
//freopen("in.txt", "r", stdin);

using namespace std;
typedef double dou;
typedef long long ll;
typedef pair<ll, ll> pii;

#define M 1050
#define inf 0x3f3f3f3f
#define mod 1000000007
#define W(a) while(a)
#define lowbit(a) a&(-a)
#define left k<<1
#define right k<<1|1
#define ms(a,b) memset(a,b,sizeof(a))
#define debug(a) cout<<#a<<" == "<<a<<endl
#define false_stdio ios::sync_with_stdio(false),cin.tie(0),cout.tie(0)

ll exgcd(ll a, ll b, ll& x, ll& y) {
    if (!b) {
        x = 1, y = 0;
        return a;
    }
    ll ans = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return ans;
}

ll solve(ll a, ll b, ll c) {
    ll x, y, z;
    z = exgcd(a, b, x, y);
    if (c % z)return -1;//不成立
    //return x; //不需要最小正整数的话直接返回x
    x *= c / z;
    b = abs(b / z);
    return (x % b + b) % b;
}

int main() {
    false_stdio;
    ll a, b, c;
    cin >> a >> b >> c;

    ll x = solve(a, b, c);
    ll y = (c - x * a) / b;

    if (x >= 0)//看x大小要求而定
        cout << x << ' ' << y << endl;



    return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
