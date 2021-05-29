#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include <iostream>
#include <cstdio>
#include<string>
using namespace std;
typedef long long ll;
struct node
{
	ll nub, grade;
	char num[20];
	node* next;
};
void ergodic(node* head)
{
	while (head->next != NULL)
	{
		head = head->next;
		printf("学生学号：%lld ", head->nub);
		cout << "学校姓名：" << head->num;
		printf(" 学生成绩：%lld \n", head->grade);
	}
}
void add(node* head)
{
	node* p, * q = head;
	p = (node*)malloc(sizeof(node));
	printf("请输入-学号-成绩-姓名-\n");
	scanf_s("%lld ", &p->nub);
	scanf_s("%lld ", &p->grade);
	scanf_s("%s", p->num, sizeof(head->num));
	while (head->next != NULL)
	{
		head = head->next;
		if (head->nub > p->nub)
		{
			q->next = p;
			p->next = head;
			return;
		}
		q = head;
	}
	head->next = p;
	p->next = NULL;
}
void modify(node* head)
{
	node* p, * q = head;
	p = (node*)malloc(sizeof(node));
	printf("请输入要修改学生的学号：\n");
	scanf_s("%lld", &p->nub);
	printf("请输入成绩：\n");
	scanf_s("%lld", &p->grade);
	printf("请输入姓名：\n");
	scanf_s("%s", p->num, sizeof(head->num));
	while (head->next != NULL)
	{
		head = head->next;
		if (head->nub == p->nub)
		{
			q->next = p;
			p->next = head->next;
			free(head);
			return;
		}
		q = head;
	}
}
void Delete(node* head)
{
	node* p, * q = head;
	p = (node*)malloc(sizeof(node));
	printf("请输入-学号-\n");
	scanf_s("%lld", &p->nub);
	while (head->next != NULL)
	{
		head = head->next;
		if (head->nub == p->nub)
		{
			q->next = head->next;
			free(head);
			free(p);
			return;
		}
		q = head;
	}
}
int main()
{
	ll x;
	node* head, * p;
	head = (node*)malloc(sizeof(node));
	head->next = NULL;
	while (1)
	{
		printf("遍历学生信息--1\n");
		printf("插入学生信息--2\n");
		printf("修改学生信息--3\n");
		printf("删除学生信息--4\n");
		printf("退出系统--5\n");
		cin >> x;
		if (x == 1)
		{
			ergodic(head);
		}
		else if (x == 2)
		{
			add(head);
		}
		else if (x == 3)
		{
			modify(head);
		}
		else if (x == 4)
		{
			Delete(head);
		}
		else
		{
			break;
		}
	}
	return 0;
}