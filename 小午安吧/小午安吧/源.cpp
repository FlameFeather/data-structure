//ջ�Ļ����ṹʵ�֣����֣�


#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstring>
#include <cstdio>
#include <string>
#pragma warning(disable:4996)

using namespace std;

//����״̬�붨��
#define TRUE        1
#define FALSE       0
#define OK          1
#define ERROR       0
#define INFEASIBLE -1
#define OVERFLOW   -2

typedef int Status;
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
typedef char SElemtype;

typedef struct Sqstack {
	SElemtype* base;
	SElemtype* top;
	int stacksize;
}Sqstack;

//ջ�ĳ�ʼ��
Status InitStack_Sq(Sqstack& S)
{
	S.base = (SElemtype*)malloc(sizeof(SElemtype) * STACK_INIT_SIZE);
	if (!S.base) exit(OVERFLOW);
	S.top = S.base;
	S.stacksize = STACK_INIT_SIZE;
	return OK;
}
//��ջ��
int Stack_Length(Sqstack S)
{
	return S.top - S.base;
}
//��ջ��
bool Stack_Empty(Sqstack S) //��ջ��
{
	return S.top == S.base;
}
//���ջ
Status Stack_Clear(Sqstack& S)
{
	S.top = S.base;
	return OK;
}
//ѹջ
Status Push(Sqstack& S, SElemtype e)
{
	if ((S.top - S.top) == S.stacksize)
	{
		S.base = (SElemtype*)realloc(S.base, sizeof(SElemtype) * (S.stacksize + STACKINCREMENT));
		if (!S.base)exit(OVERFLOW);
		S.top = (S.base + S.stacksize);
		S.stacksize += STACKINCREMENT;
	}
	*S.top++ = e;
	return OK;
}
//��ջ
Status Pop(Sqstack& S, SElemtype& e)
{
	if (S.base == S.top) return ERROR;
	e = *(--S.top);
	return OK;
}
//����ջ
Status StackTraverse(Sqstack S, Status(*vist)(SElemtype))
{
	SElemtype* p = S.base;
	while (p < S.top)
	{
		if (vist(*p) == ERROR) return ERROR;
		++p;
	}
	return OK;
}
//���ջԪ��
Status visit(SElemtype e)
{
	cout << e << " ";
	return OK;
}
int main()
{
	ios::sync_with_stdio(false);
	int ok = 1, len;
	Sqstack S;
	string brackets_in_code, str, wrong_information;
	InitStack_Sq(S);
	str.clear();
	brackets_in_code.clear();
	wrong_information.clear();
	//��ȡ���ţ�����brackets_in_code
	while (getline(cin, str))
	{
		len = str.length();
		//if (len == 0 || (len == 1 && str[0] == '.')) break;
		//���Ե�4 �� û�д��룬ֻ��һ�� "."
		if (str == ".") break;

		for (int i = 0; i < len; i++)
		{
			if (str[i] == '(' || str[i] == ')' || str[i] == '[' || str[i] == ']' || str[i] == '{' || str[i] == '}')
				brackets_in_code += str[i];
			else if (str[i] == '/' && str[i + 1] == '*')
			{
				brackets_in_code += '<';
				i++;
			}
			else if (str[i] == '*' && str[i + 1] == '/')
			{
				brackets_in_code += '>';
				i++;
			}
		}
	}
	//cout << "#" << brackets_in_code << "#"<< endl;

	len = brackets_in_code.length();
	for (int i = 0; i < len; i++)
	{
		char ch1 = brackets_in_code[i], ch2;
		if (ch1 == '(' || ch1 == '[' || ch1 == '{' || ch1 == '<')
		{
			Push(S, ch1);
			continue;
		}
		else
		{
			if (Stack_Empty(S))
			{
				ok = 0;
				if (ch1 == '>')
					wrong_information = "?-*/";
				else
				{
					wrong_information = "?-";
					wrong_information += ch1;
				}
				break;
			}
			Pop(S, ch2);
			if ((ch2 == '(' && ch1 != ')') || (ch2 == '[' && ch1 != ']') || (ch2 == '{' && ch1 != '}') || (ch2 == '<' && ch1 != '>'))
			{
				ok = 0;
				if (ch2 == '<')
					wrong_information = "/*-?";
				else
				{
					wrong_information = ch2;
					wrong_information += "-?";
				}
				break;
			}
		}
	}
	//cout << "#" << Stack_Length(S) << "#" << endl;
	if (ok == 1 && Stack_Empty(S)) cout << "YES" << endl;
	else if (ok == 1 && !Stack_Empty(S))
	{
		cout << "NO" << endl;
		cout << *S.base << "-?" << endl;
	}
	else
	{
		cout << "NO" << endl;
		cout << wrong_information << endl;
	}
}
