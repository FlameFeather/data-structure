//#pragma GCC optimize(2)
//std::ios::sync_with_stdio(false)
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<ctype.h>
#include<cstdlib>
#include<vector>
#include<map>
#include<list>
#include<istream>
#include<iostream>
#include<string>
#include<algorithm>
#include<queue>
#include<memory.h>
#include<set>
#include<stack>
#include<unordered_map>
#include<complex>
using namespace std;
typedef long long ll;
typedef complex<double> cd;//复数类的定义
const ll maxl = 2094153;//nlogn的最大长度(来自leo学长的博客)
const double PI = acos(-1);//圆周率,不解释
ll rev[maxl];
cd a[maxl], b[maxl];
void get_rev(ll bit)//bit表示二进制位数,计算一个数在二进制翻转之后形成的新数
{
   /* for (ll i = 0; i < ((ll)1 << bit); i++)
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (bit - 1));*/
    for (int i = 0; i < bit; i++) {
        rev[i] = (i & 1) * (bit >> 1) + (rev[i >> 1] >> 1);
    }
}
void fft(cd* a, ll n, ll dft)//n表示我的多项式位数
{
    for (ll i = 0; i < n; i++) if (i < rev[i]) swap(a[i], a[rev[i]]);
    //中间的那个if保证了每个数做多只被交换了1次
    //如果不写那么会有一些数被交换两次,导致最终的位置没有变
    for (ll step = 1; step < n; step <<= 1)//模拟一个合并的过程
    {
        cd wn = exp(cd(0, dft * PI / step));//计算当前单位复根
        for (ll j = 0; j < n; j += step << 1)
        {
            cd wnk(1, 0);//计算当前单位复根
            for (ll k = j; k < j + step; k++)
            {//蝴蝶🦋操作
                cd x = a[k];
                cd y = wnk * a[k + step];
                a[k] = x + y;//这就是上文中F(x)=G(x)+ωH(x)的体现
                a[k + step] = x - y;
                //后半个“step”中的ω一定和“前半个”中的成相反数
                //“红圈”上的点转一整圈“转回来”，转半圈正好转成相反数
                //一个数相反数的平方与这个数自身的平方相等..
                wnk *= wn;
            }
        }
    }
    if (dft == -1) for (ll i = 0; i < n; i++) a[i] /= n;
    //考虑到如果是IDFT操作,整个矩阵中的内容还要乘上1/n  
}
ll output[maxl];
int main()
{
    ll n; scanf("%lld", &n);
    for (ll i = 1; i <= n; i++)
    {
        ll x; scanf("%lld", &x);
        a[x].real(1), b[500002 - x].real(1);
    }
    get_rev(20); fft(a, 1048576, 1); fft(b, 1048576, 1);
    for (ll i = 0; i < 1048576; i++)a[i] *= b[i];
    fft(a, 1048576, -1);//idft,ifft
    for (ll i = 0; i < 1048576; i++) {//还原成十进制数
        output[abs(500002 - i)] = (ll)(a[i].real() + 0.5) > 0 ? 1 : 0;//注意精度误差
    }
    for (ll i = n; i < 500002; i++)
    {
        for (ll j = 1; j * i < 500002; j++)
        {
            if (output[j * i])goto line1;
        }
        printf("%lld\n", i);
        return 0;
    line1:;
    }
    return 0;
}
//题目：https://ac.nowcoder.com/acm/contest/11166/H
//学习博客：https://blog.csdn.net/ggn_2015/article/details/68922404