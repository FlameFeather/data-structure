#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<ctype.h>
#include<cstdlib>
#include <iostream>
#include <algorithm>
#include<queue>
#include <windows.h>
#include <fstream>
#include <vector>
#include<time.h>
using namespace std;
typedef long long ll;
string password;
FILE* fp, * mima;
struct employee
{
	char name[100], gender[100], edu[100];
	ll 销售额;
};
struct goods
{
	ll stock, price, 销售额;
	char name[100];
};
struct order
{
	ll date, id, employee_id, good_id, quantity, 总价;
	struct tm* tm_now;
	char emp_name[100], good_name[100];
};
vector<employee>emp;
vector<goods>goo;
vector<order>ord;
bool cmp1(const employee& a, const employee& b)
{
	return a.销售额 > b.销售额;
}
bool cmp2(const goods& a, const goods& b)
{
	return a.销售额 > b.销售额;
}
ll secret(ll mm)
{
	if (mm == 404)
	{
		if ((fp = fopen("F:\\密码.txt", "wb+")) == NULL)
		{
			printf("File open error!\n");
			exit(0);
		}
		cout << "请设置管理员密码！\n";
		cin >> mm;
		fwrite(&mm, sizeof(mm), 1, mima);
		fclose(mima);
		return 0;
	}
	if ((mima = fopen("F:\\密码.txt", "rb")) == NULL)
	{
		if ((mima = fopen("F:\\密码.txt", "wb+")) == NULL)
		{
			printf("File open error!\n");
			exit(0);
		}
		fwrite(&mm, sizeof(ll), 1, mima);
		fclose(mima);
		return 0;
	}
	ll mi;
	fread(&mi, sizeof(ll), 1, mima);
	fclose(mima);
	return mi;
}
void Write()
{
	if ((fp = fopen("F:\\人员.txt", "wb")) == NULL)
	{
		printf("File open error!\n");
		exit(0);
	}
	for (vector<employee>::iterator it = emp.begin(); it < emp.end(); ++it)
	{
		employee x;
		x = *it;
		fwrite(&x, sizeof(employee), 1, fp);
	}
	fclose(fp);
	if ((fp = fopen("F:\\货物.txt", "wb")) == NULL)
	{
		printf("File open error!\n");
		exit(0);
	}
	for (vector<goods>::iterator it = goo.begin(); it < goo.end(); ++it)
	{
		goods x;
		x = *it;
		fwrite(&x, sizeof(goods), 1, fp);
	}
	fclose(fp);
	if ((fp = fopen("F:\\账单.txt", "wb")) == NULL)
	{
		printf("File open error!\n");
		exit(0);
	}
	for (vector<order>::iterator it = ord.begin(); it < ord.end(); ++it)
	{
		order x;
		x = *it;
		fwrite(&x, sizeof(order), 1, fp);
	}
	fclose(fp);
}
void addorder()
{
	order x; ll x1 = 0, x2 = 0;
	cout << "销售员：";
	cin >> x.emp_name;
	cout << "请输入货物名称：";
	cin >> x.good_name;
	cout << "售出__吨\b\b\b";
	cin >> x.quantity;
	time_t now; time(&now); x.tm_now = localtime(&now);
	for (vector<employee>::iterator it = emp.begin(); it < emp.end(); ++it)
	{
		if (strcmp((it->name), x.emp_name) == 0)
		{
			x1 = 1;
		}
	}
	if (x1 == 0)
	{
		cout << "不存在此销售员！！\n"; return;
	}
	for (vector<goods>::iterator it = goo.begin(); it < goo.end(); ++it)
	{
		if (strcmp((it->name), x.good_name) == 0)
		{
			x2 = 1; x.总价 = x.quantity * it->price;
			if (it->stock - x.quantity < 0)
			{
				cout << "\n库存都没了你是怎么卖出的ー(￣～￣)ξ\n"; return;
			}
		}
	}
	if (x2 == 0)
	{
		cout << "不存在这种商品！！\n";
		return;
	}
	for (vector<employee>::iterator it = emp.begin(); it < emp.end(); ++it)
	{
		if (strcmp((it->name), x.emp_name) == 0)
		{
			it->销售额 += x.总价; x1 = 1;
		}
	}
	for (vector<goods>::iterator it = goo.begin(); it < goo.end(); ++it)
	{
		if (strcmp((it->name), x.good_name) == 0)
		{
			it->销售额 += x.总价;
			it->stock -= x.quantity;
		}
	}
	ord.push_back(x);
	cout << "添加订单成功\n";
}
void addgoods()
{
	goods x;
	cout << "请输入货物名称：";
	cin >> x.name, 100;
	cout << "存入__吨\b\b\b\b";
	cin >> x.stock;
	cout << "单价：__$\b\b\b";
	cin >> x.price;
	x.销售额 = 0;
	goo.push_back(x);
}
void addpeople()
{
	employee x;
	cout << "请输入名字：";
	cin >> x.name;
	cout << "你的学历：";
	cin >> x.edu;
	cout << "你的性别：";
	cin >> x.gender;
	x.销售额 = 0;
	emp.push_back(x);
}
void delete_employee()
{
	employee x;
	cout << "请输入要解雇人员的姓名：";
	cin >> x.name;
	for (vector<employee>::iterator it = emp.begin(); it < emp.end(); ++it)
	{
		if (strcmp((it->name), x.name) == 0)
		{
			it = emp.erase(it);
			cout << "删除成功\n";
			return;
		}
	}
	cout << "查无此人！\n";
}
void delete_goods()
{
	goods x;
	cout << "请输入要删除的货物名称：";
	cin >> x.name, 100;
	for (vector<goods>::iterator it = goo.begin(); it < goo.end(); ++it)
	{
		if (strcmp((it->name), x.name) == 0)
		{
			it = goo.erase(it);
			cout << "删除成功\n";
			return;
		}
	}
	cout << "查无此商品！\n";
}
void achievement()
{
	sort(emp.begin(), emp.end(), cmp1);
	for (vector<employee>::iterator it = emp.begin(); it < emp.end(); ++it)
	{
		cout << "姓名：" << it->name << endl;
		cout << "业绩：" << it->销售额 << endl;
	}
}
void goods_stock()
{
	sort(goo.begin(), goo.end(), cmp2);
	for (vector<goods>::iterator it = goo.begin(); it < goo.end(); ++it)
	{
		cout << "货物名称："<<it->name << endl;
		cout << "单价：" << it->price << "$" << endl;
		cout << "销售金额：" << it->销售额 << "$" << endl;
		cout << "库存：" << it->stock << "吨" << endl << endl;
	}
}
void show()
{
	for (vector<order>::iterator it = ord.begin(); it < ord.end(); ++it)
	{
		printf("订单创建时间: %d-%d-%d %d:%d:%d\n", it->tm_now->tm_year + 1900, it->tm_now->tm_mon + 1, it->tm_now->tm_mday, it->tm_now->tm_hour, it->tm_now->tm_min, it->tm_now->tm_sec);
		cout << "销售员：" << it->emp_name << endl;
		cout << "物品：" << it->good_name << endl;
		cout << "销售量：" << it->quantity << "吨" << endl;
		cout << "销售金额：" << it->总价 << "$" << endl << endl;
	}
	if (ord.size() == 0)cout << "无销售记录\n";
}
void menu_2()
{
	while (1)
	{
		cout << "---------（1）增加商品------------" << endl;
		cout << "---------（2）减少商品------------" << endl;
		cout << "---------（3）销售情况------------" << endl;
		cout << "---------（4）库存情况------------" << endl;
		cout << "------（5）返回上一级菜单---------" << endl;
		ll x; cin >> x;
		switch (x)
		{
		case 1: addgoods(); break;
		case 2: delete_goods(); break;
		case 3: show(); break;
		case 4: goods_stock(); break;
		case 5: goto line1; break;
		default:printf("error\n"); break;
		}
	}
line1:;
}
void menu_1()
{
	while (1)
	{
	cout << "---------（1）招聘人员------------" << endl;
	cout << "---------（2）开除人员------------" << endl;
	cout << "---------（3）人员业绩------------" << endl;
	cout << "------（4）返回上一级菜单---------" << endl;
	ll x; cin >> x;
	switch (x)
	{
	case 1: addpeople(); break;
	case 2: delete_employee(); break;
	case 3: achievement(); break;
	case 4: goto line1; break;
	default:printf("error\n"); break;
	}
}
line1:;
}
void menu_secondary()
{
	while (1)
	{
		cout << "---------（1）人员管理------------" << endl;
		cout << "---------（2）商品管理------------" << endl;
		cout << "---------（3）密码管理------------" << endl;
		cout << "------（4）返回上一级菜单---------" << endl;
		ll y; cin >> y;
		if (y == 1)
		{
			menu_1();
		}
		else if (y == 2)
		{
			menu_2();
		}
		else if (y == 3)
		{
			secret(404);
		}
		else if (y == 4)
		{
			break;
		}
		else
		{
			cout << "error！\n";
		}
	}
}
void menu()
{
	while (1)
	{
		cout << "--------欢迎使用可能出错系统------" << endl;
		cout << "---------（1）创建订单------------" << endl;
		cout << "--------（2）管理员功能-----------" << endl;
		cout << "---------（3）退出系统------------" << endl;
		ll x; cin >> x;
		if (x == 1)
		{
			addorder();
		}
		else if (x == 2)
		{
			cout << "请输入管理员密码：" << endl; ll jh = 3;
			while (jh--)
			{
				ll 密码？; cin >> 密码？;
				if (密码？ == secret(0))
				{
					goto line1;
				}
				else
				{
					if (jh == 0)
					{
						cout << "你没机会啦\n"; break;
					}
					cout << "还剩余" << jh << "次尝试机会！" << endl;
				}
			}
			cout << "系统已进入自毁模式...." << endl;
			Sleep(1000); cout << "5....\n"; Sleep(1000); cout << "4....\n"; Sleep(1000); cout << "3....\n"; Sleep(1000); cout << "2....\n"; Sleep(1000); cout << "1....\n"; Sleep(1000);
			cout << "boml!!!!!!!!!!!!!!!!!!"; 
			Sleep(5000); system("cls");
			COORD screen_size;
			SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, &screen_size);
			system("color 97");
			cout << "A problem has been detected and windows has been shut down to prevent damage to your computer ." << endl << endl;
			cout << "If this is the first time you've seen this stop error screen,\nrestart your computer. If this screen appears again, follow\nthese steps :" << endl << endl;
			cout << "check for viruses on your computerRemove anyanewly instal1ed\nhard drives or hard drive control lers. Check your hard drive\nto make sure it is properly configured and terminated." << endl;
			cout << "Run CHKDSK /F to check for hard drive corruption, and then\nrestart your computer.\n" << endl;
			cout << "Technica1 informat ion:\n" << endl;
			cout << "www STOP: 0x00000076 (0XFFF FF880009A9928, OXFFFFFFC0000034 , 0X00000000000000, 0x0000000000000000)" << endl;
			return;
		line1:menu_secondary();
		}
		else
		{
			Write();
			break;
		}
	}
}
void Read()
{
	ll ff = 1;
	if ((fp = fopen("F:\\人员.txt", "rb")) == NULL)
	{
		if ((fp = fopen("F:\\人员.txt", "wb+")) == NULL)
		{
			printf("File open error!\n");
			exit(0);
		}
		fclose(fp);
		ff = 0;
	}
	if (ff)
	{
		while (feof(fp) == 0)
		{
			employee x;
			fread(&x, sizeof(employee), 1, fp);
			emp.push_back(x);
		}
		emp.pop_back();
	}
	fclose(fp);
	if ((fp = fopen("F:\\货物.txt", "rb")) == NULL)
	{
		if ((fp = fopen("F:\\货物.txt", "wb+")) == NULL)
		{
			printf("File open error!\n");
			exit(0);
		}
		fclose(fp);
		ff = 0;
	}
	if (ff)
	{
		while (feof(fp) == 0)
		{
			goods x;
			fread(&x, sizeof(goods), 1, fp);
			goo.push_back(x);
		}
		goo.pop_back();
	}
	fclose(fp);
	if ((fp = fopen("F:\\账单.txt", "rb")) == NULL)
	{
		if ((fp = fopen("F:\\账单.txt", "wb+")) == NULL)
		{
			printf("File open error!\n");
			exit(0);
		}
		fclose(fp);
		ff = 0;
	}
	if (ff)
	{
		while (feof(fp) == 0)
		{
			order x;
			fread(&x, sizeof(order), 1, fp);
			ord.push_back(x);
		}
		ord.pop_back();
	}
	fclose(fp);
	if (ff == 0)
	{
		cout << "请设置管理员密码！\n";
		ll mm;
		cin >> mm;
		secret(mm);
	}
}
int main()
{
	system("color 81");
	Read();
	menu();
	Write();
	cout << "欢迎使用！";
	return 0;
}