#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
int p[1000006];
int main()
{
    int n, m;
    while (cin >> n >> m)
    {
        int cnt = 0, a, b, ans = 0;
        while (n--)
        {
            scanf("%d%d", &a, &b);
            if (a < m || b)
                p[cnt++] = a;
            else if (a >= m)
                ans++;
        }
        sort(p, p + cnt);
        int l = 0, r = cnt - 1;
        while (l <= r)
        {
            if (p[l] + p[r] >= m * 2)
            {
                if (l == r)
                    ans++;
                else
                    ans += 2;
                l++, r--;
            }
            else
                l++;
        }
        printf("%d\n", ans);
    }
    return 0;
}