//栈的基本结构实现（部分）


#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstring>
#include <cstdio>
#include <string>
#pragma warning(disable:4996)

using namespace std;

//函数状态码定义
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

//栈的初始化
Status InitStack_Sq(Sqstack& S)
{
	S.base = (SElemtype*)malloc(sizeof(SElemtype) * STACK_INIT_SIZE);
	if (!S.base) exit(OVERFLOW);
	S.top = S.base;
	S.stacksize = STACK_INIT_SIZE;
	return OK;
}
//求栈长
int Stack_Length(Sqstack S)
{
	return S.top - S.base;
}
//判栈空
bool Stack_Empty(Sqstack S) //判栈空
{
	return S.top == S.base;
}
//清空栈
Status Stack_Clear(Sqstack& S)
{
	S.top = S.base;
	return OK;
}
//压栈
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
//出栈
Status Pop(Sqstack& S, SElemtype& e)
{
	if (S.base == S.top) return ERROR;
	e = *(--S.top);
	return OK;
}
//遍历栈
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
//输出栈元素
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
	//读取括号，存入brackets_in_code
	while (getline(cin, str))
	{
		len = str.length();
		//if (len == 0 || (len == 1 && str[0] == '.')) break;
		//测试点4 ： 没有代码，只有一个 "."
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
