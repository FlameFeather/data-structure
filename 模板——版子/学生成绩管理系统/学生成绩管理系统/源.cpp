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
		printf("ѧ��ѧ�ţ�%lld ", head->nub);
		cout << "ѧУ������" << head->num;
		printf(" ѧ���ɼ���%lld \n", head->grade);
	}
}
void add(node* head)
{
	node* p, * q = head;
	p = (node*)malloc(sizeof(node));
	printf("������-ѧ��-�ɼ�-����-\n");
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
	printf("������Ҫ�޸�ѧ����ѧ�ţ�\n");
	scanf_s("%lld", &p->nub);
	printf("������ɼ���\n");
	scanf_s("%lld", &p->grade);
	printf("������������\n");
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
	printf("������-ѧ��-\n");
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
		printf("����ѧ����Ϣ--1\n");
		printf("����ѧ����Ϣ--2\n");
		printf("�޸�ѧ����Ϣ--3\n");
		printf("ɾ��ѧ����Ϣ--4\n");
		printf("�˳�ϵͳ--5\n");
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