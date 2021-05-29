#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<ctype.h>
#include<cstdlib>
#include<vector>
#include<map>
#include<iostream>
#include<algorithm>
#include<queue>
#include<memory.h>
#include<set>
#include<stack>
#include<unordered_map>
#include<cstdlib>
using namespace std;
typedef long long ll;
//�߶��������������������޸ģ������ѯ
//���⣺һ���������飬���ϰ�ĳ�����ڵ�ֵ�޸ġ�Ϊ����һ������ֵ����ѯ�����ں͡�
#define maxn 1000006
ll num[maxn * 4];//���ı��ռ�
ll lazy[maxn * 4];

void push_up(ll root)//���ڵ�״̬����
{
	num[root] = num[root * 2] + num[root * 2 + 1];
}
void build(ll l, ll r, ll root)//�߶�������
{
	if (l == r)
	{
		scanf("%lld", &num[root]);
		return;
	}
	ll mid = (l + r) / 2;
	build(l, mid, root * 2);
	build(mid + 1, r, root * 2 + 1);
	push_up(root);
}

void push_down(ll root, ll len)//���룺root����±ꡢ��Ӧ�ĵ�ǰ[l,r]���䳤��
{
	if (lazy[root] == 0)//��������ڵ����û��lazy_tag
		return;
	//num[root] += len * lazy[root];
	lazy[root * 2] += lazy[root];
	lazy[root * 2 + 1] += lazy[root];
	num[root * 2] += lazy[root] * (len - (len) / 2);
	num[root * 2 + 1] += lazy[root] * ((len) / 2);

	lazy[root] = 0;
}

void upgrade(ll la, ll rb, ll l, ll r, ll val, ll root)//�߶θ���
//la��rbΪ����µ��������Ҷ˵㣬l��rΪ��ǰ�������Ҷ˵㣬rootΪ��ǰl��r��Ӧ�ĸ��洢λ��
{
	if (la <= l && rb >= r)
	{
		num[root] += (r - l + 1) * val;
		lazy[root] += val;
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

ll query(ll la, ll rb, ll l, ll r, ll root)//��ѯ����[la,rb]��ֵ
{
	push_down(root, r - l + 1);
	if (l >= la && r <= rb)
	{
		return num[root];
	}
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
	push_up(root);
	return ans;
}
int main()
{
	ll n, x;//ԭ����������
	scanf("%lld%lld", &n, &x);
	build(1, n, 1);//����
	while (x--)
	{
		ll ju;
		scanf("%lld", &ju);
		if (ju == 1)
		{
			ll la, rb, val;
			scanf("%lld%lld%lld", &la, &rb, &val);
			upgrade(la, rb, 1, n, val, 1);//����[l,r]�����㣬ÿ����㶼�����¡��ɡ�val
		}
		else
		{
			ll la, rb, val;
			scanf("%lld%lld", &la, &rb);
			printf("%lld\n", query(la, rb, 1, n, 1));//��ѯ����[la,rb]��ֵ
		}
	}
	return 0;
}