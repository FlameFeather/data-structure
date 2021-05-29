#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include <ctype.h>
#include<stdio.h>
typedef long long ll;
int n, m, len, nx, ny, sx, sy, flag, lng = 1;
char c, opt[1000005];
int mx[4] = { -1,0,1,0 }, my[4] = { 0,-1,0,1 };
int mp[405][405];
char op[4] = { 'W','A','S','D' };
bool checkxy() {
	if (nx <= 0 || ny <= 0 || nx > n || ny > m)return 1;
	return 0;
}
int main() 
{
	scanf_s("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j) 
		{
			c = getchar(); while (c != '.' && c != '+' && c != '-' && c != '@')c = getchar();
			if (c == '.')mp[i][j] = 0;
			else if (c == '+')mp[i][j] = 1;
			else if (c == '-')mp[i][j] = 2;
			else 
			{
				mp[i][j] = 0;
				nx = i; ny = j;
			}
		}
	scanf_s("%s", opt,sizeof(opt));
	len = strlen(opt);
	for (int i = 0; i < len; ++i) 
	{
		for (int j = 0; j < 4; ++j) 
		{
			if (opt[i] == op[j]) 
			{
				nx += mx[j]; ny += my[j];
				if (checkxy()) 
				{ 
					flag = 1; break; 
				}
				if (mp[nx][ny] == 1) 
				{
					mp[nx][ny] = 0;
					lng++;
				}
				if (mp[nx][ny] == 2) 
				{
					mp[nx][ny] = 0;
					lng--;
					if (lng == 0) 
					{ 
						flag = 1; break; 
					}
				}
			}
			if (flag)break;
		}
		if (flag)break;
	}
	if (flag)puts("GG");
	else 
	{
		sx = nx, sy = ny;
		for (int i = 1; i < lng; ++i) 
		{
			for (int j = 0; j < 4; ++j) 
			{
				if (opt[len - i] == op[j]) 
				{
					sx -= mx[j]; sy -= my[j];
					mp[sx][sy] = 3;
				}
			}
		}
		mp[nx][ny] = 4;
		for (int i = 1; i <= n; ++i) 
		{
			for (int j = 1; j <= m; ++j) 
			{
				if (mp[i][j] == 0)printf(".");
				if (mp[i][j] == 1)printf("+");
				if (mp[i][j] == 2)printf("-");
				if (mp[i][j] == 3)printf("X");
				if (mp[i][j] == 4)printf("@");
			}
			puts("");
		}
	}
	return 0;
}