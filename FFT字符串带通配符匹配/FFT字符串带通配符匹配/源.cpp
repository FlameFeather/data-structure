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
#include<time.h>
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
//cd a[maxl], b[maxl], P[maxl];
void get_rev(ll bit)//bit表示二进制位数,计算一个数在二进制翻转之后形成的新数
{
	/*for (ll i = 0; i < ((ll)1 << bit); i++)
		rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (bit - 1));*/
	for (int i = 0; i < bit; i++) {
		rev[i] = (i & 1) * (bit >> 1) + (rev[i >> 1] >> 1);
	}
}
void FFT(cd* a, ll n, ll dft)//n表示我的多项式位数
{
	for (ll i = 0; i < n; i++)
		if (i < rev[i]) swap(a[i], a[rev[i]]);
	//中间的那个if保证了每个数做多只被交换了1次
	//如果不写那么会有一些数被交换两次,导致最终的位置没有变
	for (ll step = 1; step < n; step <<= 1)//模拟一个合并的过程
	{
		cd wn = exp(cd(0, dft * PI / step));//计算当前单位复根
		for (ll j = 0; j < n; j += step << 1)
		{
			cd wnk(1, 0);//计算当前单位复根
			for (ll k = j; k < j + step; k++)
			{//蝴蝶?操作
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
// const int N = 1e6 + 10;

cd a[maxl], b[maxl], c[maxl];

char str1[maxl], str2[maxl];

int A[maxl], S[maxl], n, m, lim;

int main() {
	// freopen("in.txt", "r", stdin);
	// freopen("out.txt", "w", stdout);
	scanf("%d %d %s %s", &m, &n, str2, str1);
	for (int i = 0; i < n; i++) {
		A[i] = str1[i] == '*' ? 0 : str1[i] - 'a' + 1;
	}
	for (int i = 0; i < m; i++) {
		S[i] = str2[m - i - 1] == '*' ? 0 : str2[m - i - 1] - 'a' + 1;
	}
	lim = 1;
	while (lim < n + m) {
		lim <<= 1;
	}

	get_rev(lim);
	for (int i = 0; i < lim; i++) {
		b[i] = { (double)A[i], 0 };
		c[i] = { (double)S[i] * S[i] * S[i], 0 };
	}
	FFT(b, lim, 1), FFT(c, lim, 1);
	for (int i = 0; i < lim; i++) {
		a[i] = a[i] + b[i] * c[i];
	}
	for (int i = 0; i < lim; i++) {
		b[i] = { (double)A[i] * A[i] * A[i], 0 };
		c[i] = { (double)S[i], 0 };
	}
	FFT(b, lim, 1), FFT(c, lim, 1);
	for (int i = 0; i < lim; i++) {
		a[i] = a[i] + b[i] * c[i];
	}
	for (int i = 0; i < lim; i++) {
		b[i] = { (double)A[i] * A[i], 0 };
		c[i] = { (double)S[i] * S[i], 0 };
	}
	FFT(b, lim, 1), FFT(c, lim, 1);
	for (int i = 0; i < lim; i++) {
		cd xx; xx.real(2); xx.imag(0);
		a[i] = a[i] - xx * b[i] * c[i];
	}
	FFT(a, lim, -1);
	vector<int> ans;
	for (int i = m - 1; i < n; i++) {
		if ((long long)(a[i].real() + 0.5) == 0) {
			ans.push_back(i - m + 2);
		}
	}
	printf("%d\n", ans.size());
	for (auto it : ans) {
		printf("%d ", it);
	}
	puts("");
	return 0;
}
//https://www.luogu.com.cn/problem/P4173
/*
 * ┌───┐   ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┐ ┌───┬───┬───┐  ┌──┐  ┌──┐  ┌──┐
 * │Esc│   │ F1│ F2│ F3│ F4│ │ F5│ F6│ F7│ F8│ │ F9│F10│F11│F12│ │P/S│S L│P/B│  │┌┐│  │┌┐│  │┌┐│
 * └───┘   └───┴───┴───┴───┘ └───┴───┴───┴───┘ └───┴───┴───┴───┘ └───┴───┴───┘  └└┘┘  └└┘┘  └└┘┘
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐ ┌───┬───┬───┐ ┌───┬───┬───┬───┐
 * │~ `│! 1│@ 2│# 3│$ 4│% 5│^ 6│& 7│* 8│( 9│) 0│_ -│+ =│ BacSp │ │Ins│Hom│PUp│ │Num│ / │ * │ - │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤ ├───┼───┼───┤ ├───┼───┼───┼───┤
 * │ Tab │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │{ [│} ]│ | \ │ │Del│End│PDn│ │ 7 │ 8 │ 9 │   │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤ └───┴───┴───┘ ├───┼───┼───┤ + │
 * │ Caps │ A │ S │ D │ F │ G │ H │ J │ K │ L │: ;│" '│ Enter  │               │ 4 │ 5 │ 6 │   │
 * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────────┤     ┌───┐     ├───┼───┼───┼───┤
 * │ Shift  │ Z │ X │ C │ V │ B │ N │ M │< ,│> .│? /│  Shift   │     │ ↑ │     │ 1 │ 2 │ 3 │   │
 * ├─────┬──┴─┬─┴──┬┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤ ┌───┼───┼───┐ ├───┴───┼───┤ E││
 * │ Ctrl│ Win│ Alt│         Space         │ Alt│ Win│Menu│Ctrl│ │ ← │ ↓ │ → │ │   0   │ . │←─┘│
 * └─────┴────┴────┴───────────────────────┴────┴────┴────┴────┘ └───┴───┴───┘ └───────┴───┴───┘
 */