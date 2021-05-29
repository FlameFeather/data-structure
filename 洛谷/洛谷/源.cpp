//#pragma GCC optimize(2)
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<ctype.h>
#include<cstdlib>
#include<vector>
#include<map>
#include<istream>
#include<iostream>
#include<algorithm>
#include<queue>
#include<memory.h>
#include<set>
#include<unordered_map>
#include<cstdlib>
using namespace std;
typedef long long ll;
unordered_map<string, pair<string, ll> >mp;
char a[100005];
priority_queue<ll>q;
int main()
{
	ios::sync_with_stdio(false);
	ll n; scanf("%lld", &n);
	while (n--)
	{
		string g;
		cin >> g;
		while (1)
		{
			scanf(" %[^\n]", a);
			ll len = strlen(a);
			if (len == 1 && a[0] == '#')break;
			string q = a;
			if (mp[a].second == 0)mp[a].first = g;
			mp[a].second++;
		}
	}
	ll m; scanf("%lld", &m);
	while (m--)
	{

	}
	return 0;
}