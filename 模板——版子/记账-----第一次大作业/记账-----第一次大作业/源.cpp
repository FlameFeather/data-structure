#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
typedef long long ll;

struct account
{
	ll id;
	char time[11], thing[15];
	double charge, balance;
};
const ll siz = sizeof(account);
ll find(FILE* fp)
{
	fseek(fp, 0, 0);
	ll be = ftell(fp);
	fseek(fp, 0, 2);
	ll end = ftell(fp);
	return (end - be) * siz;
}

void record(FILE* fp)
{
	account ac;
	printf("请输入日期:");
	scanf_s("%s", ac.time, sizeof(ac.time));
	printf("请输入消费项目:");
	scanf_s("%s", ac.thing, sizeof(ac.thing));
	printf("请输入金额:");
	scanf_s("%lf", &ac.charge);
	fseek(fp, 0, 2);
	if (ftell(fp) == 0)
	{
		ac.id = 1;
		ac.balance = ac.charge;
	}
	else
	{
		account ass;
		fseek(fp, -siz, 2);
		fread(&ass, siz, 1, fp);
		ac.id = ass.id + 1;
		ac.balance = ass.balance + ac.charge;
	}
	fseek(fp, 0, 2);
	fwrite(&ac, siz, 1, fp);
}

void revise(FILE* fp)
{
	ll id;
	printf("请输入您需要修改的记录ID：");
	scanf_s("%lld", &id);
	fseek(fp, siz * (id - 1), 0);
	account acc;
	printf("请输入日期:");
	scanf_s("%s", acc.time, sizeof(acc.time));
	printf("请输入消费项目:");
	scanf_s("%s", acc.thing, sizeof(acc.thing));
	printf("请输入金额:");
	scanf_s("%lf", &acc.charge);
	if (ftell(fp) == 0)
	{
		acc.id = 1;
		acc.balance = acc.charge;
		//fseek(fp, -siz, 1);
	}
	else
	{
		account ass;
		fseek(fp, -siz, 1);
		fread(&ass, siz, 1, fp);
		acc.id = ass.id + 1;
		acc.balance = ass.balance + acc.charge;
	}
	fseek(fp, siz * (id - 1), 0);
	fwrite(&acc, siz, 1, fp);
	fseek(fp, -siz, 1);
	ll i;
	account a[1000];
	for (i = 0; feof(fp) != 1; i++)
	{
		fread(&a[i], siz, 1, fp) != 0;
		if (i > 0)
		{
			a[i].id = a[i - 1].id + 1;
			a[i].balance = a[i - 1].balance + a[i].charge;
		}
	}
	fseek(fp, siz * (id - 1), 0);
	fwrite(a, siz, i - 1, fp);
}

void display(FILE* fp)
{
	account a;
	fseek(fp, 0, 0);
	while (fread(&a, siz, 1, fp) != 0)
	{
		printf("%-6lld%-11s%-15s%10.2lf%10.2lf\n", a.id, a.time, a.thing, a.charge, a.balance);
	}
}

void last(FILE* fp)
{
	fseek(fp, -siz, 2);
	account a;
	fread(&a, siz, 1, fp);
	printf("%-6lld%-11s%-15s%10.2lf%10.2lf\n", a.id, a.time, a.thing, a.charge, a.balance);
}

int main()
{
	FILE* fp;
	ll function;
	if ((fp = fopen("F:\\流水账.bat", "rb+")) == NULL)
	{
		printf("File open error!\n"); exit(0);
	}
	while (scanf_s("%lld", &function) != EOF)
	{
		printf("1--添加收入支出信息\n2--显示所有记录\n3--查询余额\n4--修改记录\n");
		if (function == 1)
		{
			record(fp);
		}
		else if (function == 2)
		{
			display(fp);
		}
		else if(function == 3)
		{
			last(fp);
		}
		else
		{
			revise(fp);
		}
	}
	if (fclose(fp))
	{
		printf("Can not close the file!\n"); exit(0);
	}
	return 0;
}