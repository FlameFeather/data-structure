#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<ctype.h>
#include<cstdlib>
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>
#include<queue>
#include<memory.h>
using namespace std;
typedef long long ll;
ll fac[1000006];
bool vis[10004];
void fact()
{
	fac[0] = 1;
	ll s = 1;
	for (ll i = 1; i <= 100; i++)
	{
		fac[i] = s;
		s *= i + 1;
	}
}
ll cantor(char a[], ll len)//��������a[]�����еĳ���len,���������������ȫ�����д�С�����ǵڼ��� 
{
    ll i, j, ans, cnt;
    ans = 0;
    for (i = 1; i <= len; i++)
    {
        cnt = 0;
        for (j = i + 1; j <= len; j++)
        {
            if (a[j] < a[i])//����ʴӴ�С���ǵڼ��� ��С�ںŸĳɴ��ںż���
                cnt++;
        }
        ans += cnt * fac[len - i];
    }
    return ans + 1;//ansҪ��1 ��Ϊ֮ǰ��������Ǳ����ȫ����С���м���
}
void decantor(ll len, ll k)//��ӡ1��n��ȫ�����д�С�����k������
{
	for (ll i = 0; i < 10004; i++)vis[i] = 0;
	ll i, j, cnt;
	--k;
	for (i = 1; i <= len; i++)
	{
		cnt = k / fac[len - i];
		for (j = 1; j <= len; j++)
		{
			if (!vis[j])
			{
				if (cnt == 0) break;
				cnt--;
			}
		}
		printf("%c", j + 'a' - 1);
		vis[j] = 1;
		k %= fac[len - i];
	}
	cout << endl;
}
int main()
{
	fact();
	ll n, q;
	cin >> n >> q;
	char a[50];
	scanf("%s", a + 1);
	ll xx = cantor(a, n);
	while (q--)
	{
		ll x; cin >> x;
		if (x == 1)
		{
			char b[50]; scanf("%s", b + 1);
			printf("%lld\n", cantor(b, n) - xx);
		}
		else
		{
			ll y;
			cin >> y;
			decantor(n, xx + y);
			xx += y;
		}
	}
	return 0;
}