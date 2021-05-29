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
#include<unordered_map>
#include<cstdlib>
using namespace std;
typedef long long ll;
struct stu
{
	int sid;
	double ach[4];
	char snam[20];
};
struct node
{
	stu student;
	node* next;
};

FILE* fp = NULL;
void addstu(node* head, stu stud)
{
	node* p = (node*)malloc(sizeof(node));
	p->student = stud;
	p->next = head->next;
	head->next = p;
}
node* getStuById(node* head, int sid)
{
	for (node* p = head->next; p != NULL; p = p->next)
	{
		if (p->student.sid == sid)return p;
	}
	return NULL;
}
node* getStuByName(node* head, char* sname)
{
	for (node* p = head->next; p != NULL; p = p->next)
	{
		if (strcmp(p->student.snam, sname) == 0)return p;
	}
	return NULL;
}
bool deleteStudent(node* head, int sid)
{
	for (node *p = head->next, *pre = head; p != NULL; p = p->next, pre = pre->next)
	{
		if (p->student.sid == sid)
		{
			pre->next = p->next;
			p->next = NULL;
			free(p);
			return true;
		}
	}
	return false;
}
void disqualified(node* head)
{
	int cnt = 0;
	printf("���������\n");
	for (node* p = head->next; p != NULL; p = p->next)
	{
		int f = 0, cot = 0;
		for (int i = 0; i < 4; i++)
		{
			if (p->student.ach[i] < 60)f = 1, cot++;
		}
		if (f)
		{
			printf("ѧ��:%d ����:%s ������:%d��\n", p->student.sid, p->student.snam, cot);
			cnt++;
		}
	}
	printf("�ܹ�������%d��\n", cnt);
}
struct cdsf
{
	double cnt;
	char cname[20];
};
int cmp1(const void* a, const void* b)
{
	return ((cdsf*)a)->cnt - ((cdsf*)b)->cnt;
}
void avr(node* head)
{
	cdsf cnt[4];
	for (int i = 0; i < 4; i++)cnt[i].cnt = 0;
	strcpy((char*)"΢����", cnt[0].cname);
	strcpy((char*)"���Դ���", cnt[1].cname);
	strcpy((char*)"����", cnt[2].cname);
	strcpy((char*)"C����", cnt[3].cname);
	int cot = 0;
	for (node* p = head->next; p != NULL; p = p->next)
	{
		cot++;
		for (int i = 0; i < 3; i++)
		{
			cnt[i].cnt += p->student.ach[i];
		}
	}
	printf("ƽ����: ΢����:%.2lf ���Դ���:%.2lf ����:%.2lf C����:%.2lf\n", cnt[0].cnt / cot, cnt[1].cnt / cot, cnt[2].cnt / cot, cnt[3].cnt / cot);
	qsort(cnt, 4, sizeof(cnt[0]), cmp1);
	printf("ƽ���ɼ����:%s ƽ���ɼ����:%s\n", cnt[3].cname, cnt[0].cname);
}
int cmp_poi(const void* a, const void* b)
{
	node** x = (node**)a;
	node** y = (node**)b;
	double A = 0, B = 0;
	for (int i = 0; i < 4; i++)A += (*x)->student.ach[i];
	for (int i = 0; i < 4; i++)B += (*y)->student.ach[i];
	if (A > B)return -1;
	else return 1;
}
void topFive(node* head)
{
	int cnt = 0;
	for (node *p = head->next; p != NULL; p = p->next)cnt++;
	node** pointer = (node**)malloc(cnt * sizeof(node*));
	int  i = 0;
	for (node *p = head->next; p != NULL; p = p->next)pointer[i++] = p;
	qsort(pointer, cnt, sizeof(pointer[0]), cmp_poi);
	for (int i = 0; i < 5; i++)
	{
		printf("sid:%d sname:%s\n", pointer[i]->student.sid, pointer[i]->student.snam);
	}
}
void option(node* head)
{
	while (1)
	{
		printf("��ѡ����\n");
		printf("1:����ѧ����Ϣ\n");
		printf("2:��ѯѧ����Ϣ\n");
		printf("3:�޸�ѧ����Ϣ\n");
		printf("4:ɾ��ѧ����Ϣ\n");
		printf("5:��ѯ��ѧ�ڲ������˴μ�����������\n");
		printf("6:��ѯÿ�ſγ̵�ƽ���ɼ��������ƽ���ɼ���ߺ���͵Ŀγ�\n");
		printf("7:��ѯƽ���ɼ������༶ǰ5��ѧ��\n");
		printf("8:��ȡѧ����Ϣ�ļ�\n");
		printf("9:����ѧ����Ϣ�ļ�\n");
		int op;
		scanf("%d", &op);
		if (op == 1)
		{
			stu x;
			printf("������ѧ��:"); printf("%d", x.sid);
			printf("����������:"); printf("%s", x.snam);
			printf("΢���ֳɼ�:"); printf("%lf", x.ach[0]);
			printf("���Դ����ɼ�:"); printf("%lf", x.ach[1]);
			printf("����ɼ�:"); printf("%lf", x.ach[2]);
			printf("C���Էֳɼ�:"); printf("%lf", x.ach[3]);
			addstu(head, x);
		}
		else if (op == 2)
		{
			node* str;
			printf("1��ѧ�Ų�ѯ2��������ѯ\n");
			int op; scanf("%d", &op);
			if (op == 1)
			{
				int sid;
				scanf("%d", sid);
				str = getStuById(head, sid);
			}
			else
			{
				char snam[6];
				scanf("%s", snam);
				str = getStuByName(head, snam);
			}
			if (str == NULL)
				printf("���޴��ˣ�����\n");
			else
			{
				printf("ѧ��Ϊ%s��ѧ����Ϣ����\n sid:%s sname:%s ΢���ֳɼ�:%.2lf ���Դ����ɼ�:%.2lf ����ɼ�:%.2lf C���Էֳɼ�:%.2lf\n", str->student.sid,
					str->student.sid, str->student.snam, str->student.ach[0],str->student.ach[1], str->student.ach[2], str->student.ach[3]);
			}
		}
		else if (op == 3)
		{
			printf("������ѧ��\n");
			int sid; scanf("%d", sid);
			bool st = deleteStudent(head, sid);
			if (!st)printf("���޴��ˣ�����\n");
			else
			{
				printf("�������µ���Ϣ\n");
				stu x;
				scanf("%s%s%lf%lf%lf%lf", x.sid, x.snam, &x.ach[0], &x.ach[1], &x.ach[2], &x.ach[3]);
				addstu(head, x);
				printf("�ɹ�!\n");
			}
		}
		else if (op == 4)
		{
			printf("������ѧ��\n");
			int sid; scanf("%d", sid);
			bool st = deleteStudent(head, sid);
			if (!st)
				printf("���޴��ˣ�����\n");
			else
				printf("ɾ���ɹ���\n");
		}
		else if (op == 5)
		{
			disqualified(head);
		}
		else if (op == 6)
		{
			avr(head);
		}
		else if (op == 7)
		{
			topFive(head);
		}
		else if (op == 8)
		{
			while (feof(fp) == 0)
			{
				stu a;
				fread(&a, sizeof(stu), 1, fp);
				addstu(head, a);
			}

		}
		else if (op == 9)
		{
			fclose(fp);
			remove("D:\\ѧ����Ϣ����ϵͳ.in");
			fp = fopen("D:\\ѧ����Ϣ����ϵͳ.in", "w+");
			if (fp == NULL)
				break;
			node* p;
			for (p = head->next; p != NULL; p = p->next)
			{
				fwrite(&(p->student), sizeof(p->student), 1, fp);
			}
		}
		else break;
	}
}
int main()
{
	fp = fopen("D:\\ѧ����Ϣ����ϵͳ.in", "r");
	if (fp == NULL)
	{
		printf("�ļ���ʧ�ܣ�\n");
		return 0;
	}
	node* head = (node*)malloc(sizeof(node));
	head->next = NULL;

	return 0;
}