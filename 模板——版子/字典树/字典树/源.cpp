#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include <iostream>
#include <cstdio>
#include <cstring>
typedef long long ll;
/*const int MAX_NODE = 100 + 10;
const int CHARSET = 60;
int trie[MAX_NODE][CHARSET] = { 0 };
int color[5005][MAX_NODE] = { 0 };
int k = 1;
int S[5005];

void insert(char* w, int P)
{
	int len = strlen(w);
	int p = 0;
	for (int i = 0; i < len; i++)
	{
		int c = w[i] - 'a';
		if (!trie[p][c])
		{
			trie[p][c] = k;
			k++;
		}
		p = trie[p][c];
	}
	for (int i = 1; i <= P; i++)
	{
		color[i][p]++;
	}
}
void search(int I, char* s, int P, int q)
{
	int len = strlen(s);
	int p = P;

	for (int i = I; i < len; i++)
	{
	line1:;
		if (s[i] == '?')
		{
			s[i] = 'a';
			search(i, s, p, q);
			s[i] = 'b';
			search(i, s, p, q);
			s[i] = 'c';
			search(i, s, p, q);
			s[i] = 'd';
			search(i, s, p, q);
			s[i] = 'e';
			search(i, s, p, q);
			s[i] = '?';
			i++;
		}
		if (s[i] == '?')
		{
			goto line1;
		}
		int c = s[i] - 'a';
		if (!trie[p][c])
		{
			return;
		}
		p = trie[p][c];
	}
	if (color[q][p] >= 1)
	{
		S[q]++;
	}
	color[q][p]--;
	return;
}

int main()
{
	int t, q;
	char s[60];

	scanf_s("%d%d", &t, &q);
	int T = t;
	while (t--)
	{
		scanf_s("%s", s, sizeof(s));
		insert(s, q);
	}
	while (q)
	{
		scanf_s("%s", s, sizeof(s));
		for (int i = 1; i <= T; i++)
		{
			search(0, s, 0, q);
		}
		printf("%d\n", S[q]);
		q--;
	}
	return 0;
}*/
long long i, j, k, m, M, n, ans, co, f, len, T, t;
int cnt, now, last_apr[500001], vis[500001];
char a[101];
//计算单词出现次数。

struct node
{
	node()
	{
		last_apr = 0;
		memset(next_ltr, 0, sizeof(next_ltr));
	}
	int last_apr;
	node* next_ltr[5];
}*root;

void insert(node*& p, char* s)
{
	if (!p)p = new node();
	if (!*s)
	{
		last_apr[cnt] = p->last_apr;
		p->last_apr = cnt;
		return;
	}
	insert(p->next_ltr[*s - 'a'], s + 1);
}

long long find(char* s, node* p)
{
	if (!p)
		return 0;
	if (!*s)
	{
		long long res = 0;
		for (int i = p->last_apr; i != 0; i = last_apr[i])
			if (vis[i] != cnt)
			{
				res++;
				vis[i] = cnt;
			}
		return res;
	}
	else
		return find(s + 1, p->next_ltr[*s - 'a']);
}

int main()
{
	root = new node();

	scanf_s("%lld %lld", &n, &m);
	for (i = 1; i <= n; i++)
	{
		cnt++;
		scanf_s("%s", a, sizeof(a));
		insert(root, a);
	}
	cnt = 0;
	for (i = 1; i <= m; i++)
	{
		scanf_s("%s", a, sizeof(a));
		cnt++;
		ans = find(a, root);
		printf("%lld\n", ans);
	}

	return 0;
}