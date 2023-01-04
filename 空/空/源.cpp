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
            if (u > v)  mp[v].push_back(u);	// һ��С�Ż���ֻ�ɱ��С�Ľڵ����ӵ���Ŵ�Ľڵ�
        }
        for (int i = 1; i <= n; i++) {
            sort(mp[i].begin(), mp[i].end());
            // ����������򣬾Ϳ��Ա�֤ÿ�η��ʵĽڵ㶼����С�ģ������жϸոս���˼·��˵������
            // ��Ҫ�öѣ��ײ��T������nt���ң�
        }
        vis[1] = true;
        dfs(1);
        cout << cnt << endl;
    }
    return 0;
}