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

void 提款(ll x, ll f)
{
	ll i;
	if (x > zh[f].mon)
	{
		printf("余额不足\n");
		return;
	}
	zh[f].mon -= x;
	printf("你会得到...    ");
	for (i = 0; x > 0; i++)
	{
		x = x - 50;
	}
	printf("%lld 件 20 欧元纸币 %lld 件 50 欧元纸币 欢迎回来！\n", (x + 50) / 20, i - 1);
	return;
}

int main()
{
	ll z, m, f,q;
	char l;
	line3:printf("给帐号 > ");
	scanf_s("%lld", &z);
	line2:f = search(z);
	if (f == -1)
	{
		printf("此账户不存在\n");
		goto line3;
	}
	line1:printf("提供 PIN 码 > \n");
	scanf_s("%lld", &m);
	if (m != zh[f].pin)
	{
		printf("密码不正确\n");
		goto line1;
	}
	printf("W - 提款D - 存款 B -平衡您的选择 > \n");
	scanf_s("%c", &l);
	if (l == 'W')
	{
		printf("给金额 > ");
		scanf_s("%lld", &q);
		提款(q, f);
	}
	else if (l == 'D')
	{
		printf("给金额 > ");
		scanf_s("%lld", &q);
		zh[f].mon += q;
		printf("存款成功\n");
	}
	else
	{
		printf("您的账户余额为%lld\n", zh[f].mon);
	}
	printf("提供帐号 > ");
	if (scanf_s("%lld", &z) != EOF)
	{
		goto line2;
	}
	return 0;
}