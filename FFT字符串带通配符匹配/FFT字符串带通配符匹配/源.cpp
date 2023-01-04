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
typedef complex<double> cd;//������Ķ���
const ll maxl = 2094153;//nlogn����󳤶�(����leoѧ���Ĳ���)
const double PI = acos(-1);//Բ����,������
ll rev[maxl];
//cd a[maxl], b[maxl], P[maxl];
void get_rev(ll bit)//bit��ʾ������λ��,����һ�����ڶ����Ʒ�ת֮���γɵ�����
{
	/*for (ll i = 0; i < ((ll)1 << bit); i++)
		rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (bit - 1));*/
	for (int i = 0; i < bit; i++) {
		rev[i] = (i & 1) * (bit >> 1) + (rev[i >> 1] >> 1);
	}
}
void FFT(cd* a, ll n, ll dft)//n��ʾ�ҵĶ���ʽλ��
{
	for (ll i = 0; i < n; i++)
		if (i < rev[i]) swap(a[i], a[rev[i]]);
	//�м���Ǹ�if��֤��ÿ��������ֻ��������1��
	//�����д��ô����һЩ������������,�������յ�λ��û�б�
	for (ll step = 1; step < n; step <<= 1)//ģ��һ���ϲ��Ĺ���
	{
		cd wn = exp(cd(0, dft * PI / step));//���㵱ǰ��λ����
		for (ll j = 0; j < n; j += step << 1)
		{
			cd wnk(1, 0);//���㵱ǰ��λ����
			for (ll k = j; k < j + step; k++)
			{//����?����
				cd x = a[k];
				cd y = wnk * a[k + step];
				a[k] = x + y;//�����������F(x)=G(x)+��H(x)������
				a[k + step] = x - y;
				//������step���еĦ�һ���͡�ǰ������еĳ��෴��
				//����Ȧ���ϵĵ�תһ��Ȧ��ת��������ת��Ȧ����ת���෴��
				//һ�����෴����ƽ��������������ƽ�����..
				wnk *= wn;
			}
		}
	}
	if (dft == -1) for (ll i = 0; i < n; i++) a[i] /= n;
	//���ǵ������IDFT����,���������е����ݻ�Ҫ����1/n
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