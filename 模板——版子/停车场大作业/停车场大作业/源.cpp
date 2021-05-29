#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include <iostream>
#include <cstdio>
#include<string>
#include<time.h>
using namespace std;
typedef long long ll;
std::string;
FILE* fp;
struct vehicle
{
	ll position;
	time_t time;//声明time_t类型变量
	char num[1000];
	vehicle* next;
};
ll siz = sizeof(vehicle);
void add(vehicle* head)
{
	vehicle* p = head, * q = head->next, * sj;
	sj = (vehicle*)malloc(sizeof(vehicle));
	sj->next = NULL;
	cout << "请输入车牌号\n";
	scanf_s("%s", sj->num, sizeof(sj->num));
	time(&sj->time);//获取系统日期和时间
	while (q != NULL)
	{
		if (q->position - 1 != p->position)break;
		p = q;
		q = q->next;
	}
	sj->position = p->position + 1;
	p->next = sj;
	sj->next = q;
}
void Drive_out(vehicle* head)
{
	vehicle* p = head, * q = head->next;
	char num[1000];
	cout << "请输入车牌号\n";
	scanf_s("%s", num, sizeof(num));
	while (q!= NULL)
	{
		if (strcmp(q->num, num) == 0)break;
		p = q;
		q = q->next;
	}
	p->next = q->next;
	free(q);
}
void query(vehicle* head)
{
	vehicle* p = head, * q = head->next;
	char num[1000];
	cout << "请输入车牌号\n";
	scanf_s("%s", num, sizeof(num));
	while (q->next != NULL)
	{
		if (strcmp(q->num, num) == 0)break;
		p = q;
		q = q->next;
	}
	if (q->next == NULL && strcmp(q->num, num) != 0)
	{
		cout << "没找到你的车，可能被偷了，建议报警！！"<< endl;
		return;
	}
	tm t;  //tm结构指针
	time_t now;  //声明time_t类型变量
	time(&now);  //获取系统日期和时间
	localtime_s(&t, &q->time);  //获取当地日期和时间
	cout << q->position << endl;
	cout << "停入时间：" << asctime(&t);
	cout << "计费：" << (now - q->time) * 0.1 << endl;
}
void ergodic(vehicle* head)
{
	vehicle* p = head, * q = head->next;
	ll sj;
	while (q!= NULL)
	{
		p = q;
		tm t;  //tm结构指针
		time_t now;  //声明time_t类型变量
		time(&now);  //获取系统日期和时间
		localtime_s(&t, &q->time);  //获取当地日期和时间
		printf("车牌：%s\n", p->num);
		cout << "停车位置：" << q->position << endl;
		cout << "停入时间：" << asctime(&t);
		cout << "计费：" << (now - q->time) * 0.1 << "$" << endl;
		q = q->next;
	}
}
void 退出程序(vehicle* head)
{
	if ((fp = fopen("F:\\停车场流水账.txt", "wb")) == NULL)
	{
		printf("File open error!\n");
		exit(0);
	}
	vehicle* p = head, * q = head->next;
	ll sj;
	while (q != NULL)
	{
		fwrite(q, siz, 1, fp);
		q = q->next;
	}
}
void menu(vehicle* head)
{
	while (1)
	{
		cout << "回车以开始选择";
		char p;
		p = getchar();
		system("cls");
		ll choice;
		cout << "==============欢迎使用本系统=============" << endl;
		cout << "==============【1】车辆驶入==============" << endl;
		cout << "==============【2】车辆驶出==============" << endl;
		cout << "==============【3】车辆查询==============" << endl;
		cout << "==============【4】场内信息==============" << endl;
		cout << "==============【0】退出系统==============" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1: add(head); break;
		case 2: Drive_out(head); break;
		case 3: query(head); break;
		case 4: ergodic(head); break;
		case 0: goto line; break;
		default:printf("error\n"); break;
		}
	}
	line:退出程序(head);
}
void Read(vehicle* head)
{
	vehicle* p, * q = head, * qw;
	if ((fp = fopen("F:\\停车场流水账.txt", "rb")) == NULL)
	{
		if ((fp = fopen("F:\\停车场流水账.txt", "wb")) == NULL)
		{
			printf("File open error!\n");
			exit(0);
		}
		fclose(fp);
		return;
	}
	while (feof(fp) == 0)
	{
		p = (vehicle*)malloc(sizeof(vehicle));
		fread(p, siz, 1, fp);
		if (ferror(fp))break;
		q->next = p;
		p->next = NULL;
		qw = q;
		q = p;
	}
	qw->next = NULL;
	fclose(fp);
}
int main()
{
	vehicle* head, * p;
	head = (vehicle*)malloc(sizeof(vehicle));
	head->next = NULL;
	head->position = 0;
	Read(head);
	menu(head);
	return 0;
}