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
#include<set>
using namespace std;
typedef long long ll;
const ll mod = 1e9 + 7;
const ll N = 1000006;
ll prime[N] = { 0 }, num_prime = 0;  //prime素数   
//ll bb[1000006];
int isNotPrime[N] = { 1, 1 };        // isNotPrime[i]如果i不是素数，则为1 
int Prime()//欧拉筛（可以筛数的质因数个数）
{
	for (ll i = 2; i < N; i++)
	{
		if (!isNotPrime[i])
		{
			prime[num_prime++] = i;
			//bb[i] = 1;
		}
		//无论是否为素数都会下来
		for (ll j = 0; j < num_prime && i * prime[j] < N; j++)
		{
			isNotPrime[i * prime[j]] = 1;
			//bb[i * prime[j]] = bb[i] + bb[prime[j]];
			if (!(i % prime[j]))  //遇到i最小的素数因子//关键处1                  
			{
				break;
			}
		}
	}
	return 0;
}
//埃氏筛可以搞出素数表 而不是判断单个数是否是素数
//目的：找到N以内的所有素数
//方法：找到小于等于根号n的所有素数 再去掉这些素数的倍数 剩下的就都是素数
bool prime[10000];
void sieve(int n)
{
	int i, j;
	for (i = 2; i <= n; i++)
		prime[i] = 1;//这里的prime[i]表示i是否是素数 prime[i]=1 说明i是素数
	for (i = 2; i * i <= n; i++)
	{
		if (prime[i])
		{
			for (j = i * i; j <= n; j += i)//这里的j从i*i开始 而不是i+i 找规律可以看出
			{
				prime[j] = 0;
			}
		}
	}
}

int main()
{

	return 0;
}