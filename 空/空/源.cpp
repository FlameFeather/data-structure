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
	printf("不及格情况\n");
	for (node* p = head->next; p != NULL; p = p->next)
	{
		int f = 0, cot = 0;
		for (int i = 0; i < 4; i++)
		{
			if (p->student.ach[i] < 60)f = 1, cot++;
		}
		if (f)
		{
			printf("学号:%d 姓名:%s 不及格:%d门\n", p->student.sid, p->student.snam, cot);
			cnt++;
		}
	}
	printf("总共不及格%d人\n", cnt);
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
	strcpy((char*)"微积分", cnt[0].cname);
	strcpy((char*)"线性代数", cnt[1].cname);
	strcpy((char*)"物理", cnt[2].cname);
	strcpy((char*)"C语言", cnt[3].cname);
	int cot = 0;
	for (node* p = head->next; p != NULL; p = p->next)
	{
		cot++;
		for (int i = 0; i < 3; i++)
		{
			cnt[i].cnt += p->student.ach[i];
		}
	}
	printf("平均分: 微积分:%.2lf 线性代数:%.2lf 物理:%.2lf C语言:%.2lf\n", cnt[0].cnt / cot, cnt[1].cnt / cot, cnt[2].cnt / cot, cnt[3].cnt / cot);
	qsort(cnt, 4, sizeof(cnt[0]), cmp1);
	printf("平均成绩最高:%s 平均成绩最低:%s\n", cnt[3].cname, cnt[0].cname);
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
		printf("请选择功能\n");
		printf("1:增加学生信息\n");
		printf("2:查询学生信息\n");
		printf("3:修改学生信息\n");
		printf("4:删除学生信息\n");
		printf("5:查询该学期不及格人次及不及格门数\n");
		printf("6:查询每门课程的平均成绩，并求出平均成绩最高和最低的课程\n");
		printf("7:查询平均成绩排名班级前5名学生\n");
		printf("8:读取学生信息文件\n");
		printf("9:保存学生信息文件\n");
		int op;
		scanf("%d", &op);
		if (op == 1)
		{
			stu x;
			printf("请输入学号:"); printf("%d", x.sid);
			printf("请输入姓名:"); printf("%s", x.snam);
			printf("微积分成绩:"); printf("%lf", x.ach[0]);
			printf("线性代数成绩:"); printf("%lf", x.ach[1]);
			printf("物理成绩:"); printf("%lf", x.ach[2]);
			printf("C语言分成绩:"); printf("%lf", x.ach[3]);
			addstu(head, x);
		}
		else if (op == 2)
		{
			node* str;
			printf("1按学号查询2按姓名查询\n");
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
				printf("查无此人！！！\n");
			else
			{
				printf("学号为%s的学生信息如下\n sid:%s sname:%s 微积分成绩:%.2lf 线性代数成绩:%.2lf 物理成绩:%.2lf C语言分成绩:%.2lf\n", str->student.sid,
					str->student.sid, str->student.snam, str->student.ach[0],str->student.ach[1], str->student.ach[2], str->student.ach[3]);
			}
		}
		else if (op == 3)
		{
			printf("请输入学号\n");
			int sid; scanf("%d", sid);
			bool st = deleteStudent(head, sid);
			if (!st)printf("查无此人！！！\n");
			else
			{
				printf("请输入新的信息\n");
				stu x;
				scanf("%s%s%lf%lf%lf%lf", x.sid, x.snam, &x.ach[0], &x.ach[1], &x.ach[2], &x.ach[3]);
				addstu(head, x);
				printf("成功!\n");
			}
		}
		else if (op == 4)
		{
			printf("请输入学号\n");
			int sid; scanf("%d", sid);
			bool st = deleteStudent(head, sid);
			if (!st)
				printf("查无此人！！！\n");
			else
				printf("删除成功！\n");
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
			remove("D:\\学生信息管理系统.in");
			fp = fopen("D:\\学生信息管理系统.in", "w+");
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
	fp = fopen("D:\\学生信息管理系统.in", "r");
	if (fp == NULL)
	{
		printf("文件打开失败！\n");
		return 0;
	}
	node* head = (node*)malloc(sizeof(node));
	head->next = NULL;

	return 0;
}