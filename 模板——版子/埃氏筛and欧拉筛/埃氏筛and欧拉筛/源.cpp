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
ll prime[N] = { 0 }, num_prime = 0;  //prime����   
//ll bb[1000006];
int isNotPrime[N] = { 1, 1 };        // isNotPrime[i]���i������������Ϊ1 
int Prime()//ŷ��ɸ������ɸ����������������
{
	for (ll i = 2; i < N; i++)
	{
		if (!isNotPrime[i])
		{
			prime[num_prime++] = i;
			//bb[i] = 1;
		}
		//�����Ƿ�Ϊ������������
		for (ll j = 0; j < num_prime && i * prime[j] < N; j++)
		{
			isNotPrime[i * prime[j]] = 1;
			//bb[i * prime[j]] = bb[i] + bb[prime[j]];
			if (!(i % prime[j]))  //����i��С����������//�ؼ���1                  
			{
				break;
			}
		}
	}
	return 0;
}
//����ɸ���Ը�������� �������жϵ������Ƿ�������
//Ŀ�ģ��ҵ�N���ڵ���������
//�������ҵ�С�ڵ��ڸ���n���������� ��ȥ����Щ�����ı��� ʣ�µľͶ�������
bool prime[10000];
void sieve(int n)
{
	int i, j;
	for (i = 2; i <= n; i++)
		prime[i] = 1;//�����prime[i]��ʾi�Ƿ������� prime[i]=1 ˵��i������
	for (i = 2; i * i <= n; i++)
	{
		if (prime[i])
		{
			for (j = i * i; j <= n; j += i)//�����j��i*i��ʼ ������i+i �ҹ��ɿ��Կ���
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