//#pragma GCC optimize(2)
//std::ios::sync_with_stdio(false)
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<ctype.h>
#include<cstdlib>
#include<string>
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
cd a[maxl], b[maxl], P[maxl];
void get_rev(ll bit)//bit表示二进制位数,计算一个数在二进制翻转之后形成的新数
{
	for (int i = 0; i < bit; i++) {
		rev[i] = (i & 1) * (bit >> 1) + (rev[i >> 1] >> 1);
	}
}
void fft(cd* a, ll n, ll dft)//n表示我的多项式位数
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
string s1, s2, ss;
ll A[1048576], B[1048576];
int main()
{
	//while (1) {
	memset(P, 0, sizeof P);
	ll n, k, m;
	cin >> n >> k >> m;
	cin >> s1 >> s2;
	ll cot = 1;
	ss = s1;
	while (s1.size() < s2.size() && cot < k)s1 += ss, cot++;
	ll xot = cot;
	if (s1.size() < s2.size()) {
		cout << "0" << endl;
		return 0;
	}
	while (xot-- && cot < k)s1 += ss, cot++;
	ll lim = 1;
	while (lim < (ll)s1.size() + s2.size()) {
		lim <<= 1;
	}

	get_rev(lim);
	reverse(s2.begin(), s2.end());
	ll N = lim;
	for (ll i = 0; i < s1.size(); i++) A[i] = (s1[i] != '*') ? (s1[i] - 'a' + 1) : 0;
	for (ll i = 0; i < m; i++) B[i] = (s2[i] != '*') ? (s2[i] - 'a' + 1) : 0;
	for (ll i = 0; i < N; i++)a[i].real(0), a[i].imag(0), b[i].real(0), b[i].imag(0);

	for (ll i = 0; i < N; i++) a[i].real(A[i] * A[i] * A[i]), b[i].real(B[i]);
	fft(a, N, 1);
	fft(b, N, 1);
	for (ll i = 0; i < N; i++) P[i] = a[i] * b[i];
	for (ll i = 0; i < N; i++)a[i].real(0), a[i].imag(0), b[i].real(0), b[i].imag(0);


	for (ll i = 0; i < N; i++) a[i].real(A[i]), b[i].real(B[i] * B[i] * B[i]);
	fft(a, N, 1);
	fft(b, N, 1);
	for (ll i = 0; i < N; i++) P[i] = P[i] + a[i] * b[i];
	for (ll i = 0; i < N; i++)a[i].real(0), a[i].imag(0), b[i].real(0), b[i].imag(0);

	for (ll i = 0; i < N; i++) a[i].real(A[i] * A[i]), b[i].real(B[i] * B[i]);
	fft(a, N, 1);
	fft(b, N, 1);
	complex<double> xxx;
	xxx.real(2), xxx.imag(0);
	for (ll i = 0; i < N; i++) P[i] = P[i] - a[i] * b[i] * xxx;

	fft(P, N, -1);
	ll res = 0;
	if (cot == k) {
		for (ll i = m - 1; i < s1.size(); i++)
			if (fabs(P[i].real()) <= 0.5)res++;
	}
	else {
		for (ll i = s1.size() / 2; i < s1.size(); i++)
			if (fabs(P[i].real()) <= 0.5)res++;
		res += (k - cot) / (cot / 2) * res;
		ll pos = ((k - cot) - (k - cot) / (cot / 2) * (cot / 2)) * n;
		for (ll i = s2.size() - 1; i < s1.size() / 2; i++) {
			//if (i < pos && fabs(P[i].real()) <= 0.5)res += 2;
			if (fabs(P[i].real()) <= 0.5)res += 1;
		}
		for (ll i = s1.size() / 2; i < s1.size() / 2 + pos; i++) {
			if (fabs(P[i].real()) <= 0.5)res += 1;
		}
	}
	cout << res << endl;
	//}
	return 0;
}
//https://www.nitacm.com/problem_show.php?pid=25521
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