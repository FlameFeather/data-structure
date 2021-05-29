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
	time_t time;//����time_t���ͱ���
	char num[1000];
	vehicle* next;
};
ll siz = sizeof(vehicle);
void add(vehicle* head)
{
	vehicle* p = head, * q = head->next, * sj;
	sj = (vehicle*)malloc(sizeof(vehicle));
	sj->next = NULL;
	cout << "�����복�ƺ�\n";
	scanf_s("%s", sj->num, sizeof(sj->num));
	time(&sj->time);//��ȡϵͳ���ں�ʱ��
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
	cout << "�����복�ƺ�\n";
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
	cout << "�����복�ƺ�\n";
	scanf_s("%s", num, sizeof(num));
	while (q->next != NULL)
	{
		if (strcmp(q->num, num) == 0)break;
		p = q;
		q = q->next;
	}
	if (q->next == NULL && strcmp(q->num, num) != 0)
	{
		cout << "û�ҵ���ĳ������ܱ�͵�ˣ����鱨������"<< endl;
		return;
	}
	tm t;  //tm�ṹָ��
	time_t now;  //����time_t���ͱ���
	time(&now);  //��ȡϵͳ���ں�ʱ��
	localtime_s(&t, &q->time);  //��ȡ�������ں�ʱ��
	cout << q->position << endl;
	cout << "ͣ��ʱ�䣺" << asctime(&t);
	cout << "�Ʒѣ�" << (now - q->time) * 0.1 << endl;
}
void ergodic(vehicle* head)
{
	vehicle* p = head, * q = head->next;
	ll sj;
	while (q!= NULL)
	{
		p = q;
		tm t;  //tm�ṹָ��
		time_t now;  //����time_t���ͱ���
		time(&now);  //��ȡϵͳ���ں�ʱ��
		localtime_s(&t, &q->time);  //��ȡ�������ں�ʱ��
		printf("���ƣ�%s\n", p->num);
		cout << "ͣ��λ�ã�" << q->position << endl;
		cout << "ͣ��ʱ�䣺" << asctime(&t);
		cout << "�Ʒѣ�" << (now - q->time) * 0.1 << "$" << endl;
		q = q->next;
	}
}
void �˳�����(vehicle* head)
{
	if ((fp = fopen("F:\\ͣ������ˮ��.txt", "wb")) == NULL)
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
		cout << "�س��Կ�ʼѡ��";
		char p;
		p = getchar();
		system("cls");
		ll choice;
		cout << "==============��ӭʹ�ñ�ϵͳ=============" << endl;
		cout << "==============��1������ʻ��==============" << endl;
		cout << "==============��2������ʻ��==============" << endl;
		cout << "==============��3��������ѯ==============" << endl;
		cout << "==============��4��������Ϣ==============" << endl;
		cout << "==============��0���˳�ϵͳ==============" << endl;
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
	line:�˳�����(head);
}
void Read(vehicle* head)
{
	vehicle* p, * q = head, * qw;
	if ((fp = fopen("F:\\ͣ������ˮ��.txt", "rb")) == NULL)
	{
		if ((fp = fopen("F:\\ͣ������ˮ��.txt", "wb")) == NULL)
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