#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<ctype.h>
#include<cstdlib>
#include<vector>
#include<map>
#include<iostream>
#include<algorithm>
#include<queue>
#include<memory.h>
#include<set>
//#include<unordered_map>
#include<cstdlib>
using namespace std;
typedef long long ll;
const int N = 1e5 + 5;
using namespace std;
vector<int> mp[N];
bool vis[N];
int cnt;
int n, m, nxt;

void dfs(int u) {
    nxt++;
    for (int i = 0; i < mp[u].size(); i++) {
        int to = mp[u][i];
        if (vis[to]) continue;
        if (to == nxt) {	// [1]
            vis[nxt] = true;
            dfs(nxt);
        }
        else {			// [2]
            cnt++;
            vis[nxt] = true;
            dfs(nxt);
            i--;
        }
    }
    if (u == 1) {			// [3] [4]
        while (nxt <= n) {
            vis[nxt] = true;
            dfs(nxt);
            cnt++;
        }
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int T;	cin >> T;
    while (T--) {
        cin >> n >> m;
        for (int i = 1; i <= n; i++) {
            mp[i].clear();
            vis[i] = false;
        }
        nxt = 1;
        cnt = 0;
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            if (u < v)  mp[u].push_back(v);
            if (u > v)  mp[v].push_back(u);	// 一个小优化，只由编号小的节点连接到编号大的节点
        }
        for (int i = 1; i <= n; i++) {
            sort(mp[i].begin(), mp[i].end());
            // 这里进行排序，就可以保证每次访问的节点都是最小的，方便判断刚刚解题思路中说的条件
            // 不要用堆，亲测会T（场上nt的我）
        }
        vis[1] = true;
        dfs(1);
        cout << cnt << endl;
    }
    return 0;
}