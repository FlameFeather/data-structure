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
const ll maxn = 2e5 + 5;
ll v[maxn];
struct L
{
	ll x, y1, y2, state;
}line[maxn];
struct Node
{
	ll l, r, cover;
	ll len;
}sgt[maxn << 3];
void pushup(ll k)
{
	if (sgt[k].cover)sgt[k].len = sgt[k].r - sgt[k].l;
	else sgt[k].len = sgt[k * 2].len + sgt[k * 2 + 1].len;
}
void build(ll l, ll r, ll k = 1)
{
	sgt[k].l = v[l], sgt[k].r = v[r];
	if (r - l <= 1)return;
	ll mid = (l + r) / 2;
	build(l, mid, k * 2);
	build(mid, r, k * 2 + 1);
}
void modify(ll x, ll y, ll z, ll k = 1)
{
	ll l = sgt[k].l, r = sgt[k].r;
	if (x <= l && y >= r)
	{
		sgt[k].cover += z;
		pushup(k);
		return;
	}
	if (x < sgt[k * 2].r)modify(x, y, z, k * 2);
	if (y > sgt[k * 2 + 1].l)modify(x, y, z, k * 2 + 1);
	pushup(k);
}
bool cmp(L a, L b) { return a.x < b.x; }
int main() {
	ll n; scanf("%lld", &n);
	for (ll i = 1; i <= n; i++)
	{
		ll x1, y1, x2, y2;
		scanf("%lld%lld%lld%lld", &x1, &y1, &x2, &y2);
		v[i] = y1, v[i + n] = y2;
		line[i] = { x1,y1,y2,1 };
		line[i + n] = { x2,y1,y2,-1 };
	}
	sort(v + 1, v + 1 + n * 2);
	sort(line + 1, line + 1 + n * 2, cmp);
	build(1, n * 2);
	ll res = 0;
	for (ll i = 1; i <= n * 2; i++)
	{
		res += sgt[1].len * (line[i].x - line[i - 1].x);
		modify(line[i].y1, line[i].y2, line[i].state);
	}
	printf("%lld\n", res);
	return 0;
}
//https://www.luogu.com.cn/problem/P5490
/*
 * ����������   ���������Щ������Щ������Щ������� ���������Щ������Щ������Щ������� ���������Щ������Щ������Щ������� ���������Щ������Щ�������  ��������  ��������  ��������
 * ��Esc��   �� F1�� F2�� F3�� F4�� �� F5�� F6�� F7�� F8�� �� F9��F10��F11��F12�� ��P/S��S L��P/B��  ��������  ��������  ��������
 * ����������   ���������ة������ة������ة������� ���������ة������ة������ة������� ���������ة������ة������ة������� ���������ة������ة�������  ��������  ��������  ��������
 * ���������Щ������Щ������Щ������Щ������Щ������Щ������Щ������Щ������Щ������Щ������Щ������Щ������Щ��������������� ���������Щ������Щ������� ���������Щ������Щ������Щ�������
 * ��~ `��! 1��@ 2��# 3��$ 4��% 5��^ 6��& 7��* 8��( 9��) 0��_ -��+ =�� BacSp �� ��Ins��Hom��PUp�� ��Num�� / �� * �� - ��
 * ���������ة��Щ��ة��Щ��ة��Щ��ة��Щ��ة��Щ��ة��Щ��ة��Щ��ة��Щ��ة��Щ��ة��Щ��ة��Щ��ة��Щ��ة��Щ����������� ���������੤�����੤������ ���������੤�����੤�����੤������
 * �� Tab �� Q �� W �� E �� R �� T �� Y �� U �� I �� O �� P ��{ [��} ]�� | \ �� ��Del��End��PDn�� �� 7 �� 8 �� 9 ��   ��
 * �������������ةЩ����ةЩ����ةЩ����ةЩ����ةЩ����ةЩ����ةЩ����ةЩ����ةЩ����ةЩ����ةЩ����ةЩ����ة����������� ���������ة������ة������� ���������੤�����੤������ + ��
 * �� Caps �� A �� S �� D �� F �� G �� H �� J �� K �� L ��: ;��" '�� Enter  ��               �� 4 �� 5 �� 6 ��   ��
 * ���������������ة��Щ��ة��Щ��ة��Щ��ة��Щ��ة��Щ��ة��Щ��ة��Щ��ة��Щ��ة��Щ��ة��Щ��ة��Щ��ة�����������������     ����������     ���������੤�����੤�����੤������
 * �� Shift  �� Z �� X �� C �� V �� B �� N �� M ��< ,��> .��? /��  Shift   ��     �� �� ��     �� 1 �� 2 �� 3 ��   ��
 * �������������Щ����ة��Щ��ة����Щة������ة������ة������ة������ة������ة����Щة������੤�����ةЩ��������Щ��������� ���������੤�����੤������ ���������ة������੤������ E����
 * �� Ctrl�� Win�� Alt��         Space         �� Alt�� Win��Menu��Ctrl�� �� �� �� �� �� �� �� ��   0   �� . ����������
 * �������������ة��������ة��������ة����������������������������������������������ة��������ة��������ة��������ة��������� ���������ة������ة������� �����������������ة������ة�������
 */
