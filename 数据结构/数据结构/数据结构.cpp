//#pragma GCC optimize(2)
//std::ios::sync_with_stdio(false)
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<ctype.h>
#include<cstdlib>
#include<vector>
#include<map>
#include<list>
#include<istream>
#include<iostream>
#include<string>
#include<algorithm>
#include<queue>
#include<memory.h>
#include<set>
#include<stack>
#include<unordered_map>
#include<complex>
using namespace std;
typedef long long ll;
//struct node
//{
//	int elemrnt;
//	node* link;
//};
//struct Stack
//{
//	int* elemrnts;
//	int Max, s;
//};
//void A(node* head1, node* head2, Stack* st1, Stack* st2)
//{
//	int s1 = 0, s2 = 0;
//	for (node* i = head1; i != NULL; i = i->link)
//		st1->elemrnts[s1++] = i->elemrnt;
//	for (node* i = head2; i != NULL; i = i->link)
//		st2->elemrnts[s2++] = i->elemrnt;
//}
//void B(Stack* st1, Stack* st2, int* conclude)
//{
//	int s = 0;
//	for (int i = st1->s - 1, j = st2->s - 1; i >= -1 && j >= -1;)
//	{
//		if (i != -1 && j != -1 && st1->elemrnts[i] <= st2->elemrnts[j])
//		{
//			conclude[s++] = st2->elemrnts[j];
//			j--;
//		}
//		else if (i != -1 && j != -1)
//		{
//			conclude[s++] = st1->elemrnts[i];
//			i--;
//		}
//		else break;
//	}
//}
//int main() {
//	Stack st1,st2;
//	st1.elemrnts = (int*)malloc(sizeof(int) * 100);
//	st2.elemrnts = (int*)malloc(sizeof(int) * 100);
//	int* conclude = (int*)malloc(sizeof(int) * 200);
//	//A();
//
//	return 0;
//}
//struct edge
//{
//	int w, v;
//	edge* next;
//};
//typedef struct lGroup
//{
//	int n, e;
//	edge** a;
//}LGroup, * LG;
//void addedge(lGroup* lg, int u, int v, int w)
//{
//	edge* p;
//	if(u<0||v<0||u>lg->n||v>lg->n||u==v)return;
//	p = (edge*)malloc(sizeof(edge));
//	p->v = v;
//	p->w = w;
//	p->next = lg->a[u];
//	lg->a[u] = p;
//	lg->e++;
//	return;
//}
//void A(lGroup* lg1, lGroup* lg2)
//{
//	for (int i = 0; i < lg1->n; i++)
//	{
//		edge* p = lg1->a[i];
//		while (p != NULL)
//		{
//			addedge(lg2, p->v, i, p->w);
//		}
//	}
//}
ll pa(ll list[], int low, int high)
{
	int i = low, j = high + 1;
	int pivot = list[low];
	do {
		do i++; while (i <= high && list[i] < pivot);
		do j--; while (list[j] > pivot);
		if (i < j)swap(list[i], list[j]);
	} while (i < j);
	swap(list[low], list[j]);
	return j;
}
int main()
{
	ll a[8] = { 28,16,32,12,60,2,5,72 };
	pa(a, 0, 7);
	for (ll i = 0; i < 8; i++)printf("%lld ", a[i]);
	return 0;
}