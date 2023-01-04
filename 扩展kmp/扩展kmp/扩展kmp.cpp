//#pragma GCC optimize(2)
//std::ios::sync_with_stdio(false)
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<ctype.h>
#include<cstdlib>
#include<string>
#include<string.h>
#include<vector>
#include<map>
#include<list>
#include<istream>
#include<iostream>
#include<string>
#include<algorithm>
#include<queue>
#include<memory.h>
#include<time.h>
#include<set>
#include<stack>
#include<unordered_map>
#include<complex>
#include<cassert>
#include<bitset>
using namespace std;
typedef long long ll;
char p[100005], s[100005];
int nexts[100005], extend[100005];
void getNEXT(char* p, int& plen, int* nexts) {
    int a = 0, k = 0;
    nexts[0] = plen;

    for (int i = 1; i < plen; i++) {
        if (i >= k || i + nexts[i - a] >= k) {
            if (i >= k) k = i;

            while (k < plen && p[k] == p[k - i])
                k++;

            nexts[i] = k - i;
            a = i;
        }
        else
            nexts[i] = nexts[i - a];
    }
}

void extendkmp(char* s, int& slen, char* p, int& plen, int* extend, int* next) {
    int a = 0, k = 0;
    getNEXT(p, plen, next);

    for (int i = 0; i < slen; i++) {
        if (i >= k || i + nexts[i - a] >= k) {
            if (i >= k) k = i;

            while (k < slen && k - i < plen && s[k] == p[k - i])
                k++;

            extend[i] = k - i;
            a = i;
        }
        else
            extend[i] = nexts[i - a];
    }
}

void solve() {
    int slen, plen;
    while (scanf("%s", p) != EOF) {
        plen = strlen(p);//模式串
        for (ll i = plen - 1; i >= 0; i--)
            s[plen - 1 - i] = p[i];
        slen = strlen(s);//文本串
       
        extendkmp(s, slen, p, plen, extend, nexts);
        pair<ll, ll>x; x.second = 0;
        for (ll i = 0; i <= slen; i++)
        {
            if (extend[i] > x.second && extend[i] == slen - i) {
                x.second = extend[i];
                x.first = i;
            }
        }
        for (ll i = 0; i < x.first; i++)printf("%c", s[i]);
        printf("%s\n", p);
    }
}
int main()
{
    solve();
    return 0;
}
/*
给定一个字符串 s，你可以通过在字符串前面添加字符将其转换为回文串。找到并返回可以用这种方式转换的最短回文串。
示例 1：

输入：s = "aacecaaa"
输出："aaacecaaa"
示例 2：

输入：s = "abcd"
输出："dcbabcd"
*/
// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
