#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include <iostream>
#include <algorithm>
typedef long long ll;
struct account
{
	ll acc;
	ll pin;
	ll mon;
}zh[1000];

ll search(ll x)
{
	for (ll i = 0; i < 1000; i++)
	{
		if (zh[1000].acc == x)
		{
			return i;
		}
	}
	return -1;
}

void ���(ll x, ll f)
{
	ll i;
	if (x > zh[f].mon)
	{
		printf("����\n");
		return;
	}
	zh[f].mon -= x;
	printf("���õ�...    ");
	for (i = 0; x > 0; i++)
	{
		x = x - 50;
	}
	printf("%lld �� 20 ŷԪֽ�� %lld �� 50 ŷԪֽ�� ��ӭ������\n", (x + 50) / 20, i - 1);
	return;
}

int main()
{
	ll z, m, f,q;
	char l;
	line3:printf("���ʺ� > ");
	scanf_s("%lld", &z);
	line2:f = search(z);
	if (f == -1)
	{
		printf("���˻�������\n");
		goto line3;
	}
	line1:printf("�ṩ PIN �� > \n");
	scanf_s("%lld", &m);
	if (m != zh[f].pin)
	{
		printf("���벻��ȷ\n");
		goto line1;
	}
	printf("W - ���D - ��� B -ƽ������ѡ�� > \n");
	scanf_s("%c", &l);
	if (l == 'W')
	{
		printf("����� > ");
		scanf_s("%lld", &q);
		���(q, f);
	}
	else if (l == 'D')
	{
		printf("����� > ");
		scanf_s("%lld", &q);
		zh[f].mon += q;
		printf("���ɹ�\n");
	}
	else
	{
		printf("�����˻����Ϊ%lld\n", zh[f].mon);
	}
	printf("�ṩ�ʺ� > ");
	if (scanf_s("%lld", &z) != EOF)
	{
		goto line2;
	}
	return 0;
}