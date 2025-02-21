#include <iostream>
#include <bits/stdc++.h>
 
using namespace std;

const int maxN = 2 * 1e5;
int pos[maxN + 2];
int arr[maxN + 2];

inline int resUpdater(int leftBefore, int rightBefore, int leftAfter, int rightAfter)
{
    int beforeSign = rightBefore - leftBefore > 0 ? 1 : -1;
    int afterSign = rightAfter - leftAfter > 0 ? 1 : -1;
    
    if (beforeSign == afterSign)
    {
        return 0;
    }
    else if (beforeSign > afterSign)
    {
        return +1;
    }
    else // if (beforeSign < afterSign)
    {
        return -1;
    }
}
 
void solve() {
    int n = 0, m = 0;
    scanf("%d%d", &n, &m);

    int res = 1;
 
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &arr[i]);

        pos[arr[i]] = i;

        if (pos[arr[i] + 1] != 0)
        {
            res++;
        }
    }

    pos[n + 1] = n + 1;

    for (int i = 0; i < m; i++)
    {
        int index1 = 0, index2 = 0;
        scanf("%d%d", &index1, &index2);

        int a = arr[index1], b = arr[index2];

        swap(arr[index1], arr[index2]);

        if (a > b)
        {
            swap(a, b);
        }

        int prevA = pos[a];
        int prevAL = pos[a-1];
        int prevAR = pos[a+1];

        int prevB = pos[b];
        int prevBL = pos[b-1];
        int prevBR = pos[b+1];

        swap(pos[a], pos[b]);

        int nextA = pos[a];
        int nextAL = pos[a-1];
        int nextAR = pos[a+1];

        int nextB = pos[b];
        int nextBL = pos[b-1];
        int nextBR = pos[b+1];

        res += resUpdater(prevAL, prevA, nextAL, nextA);
        res += resUpdater(prevA, prevAR, nextA, nextAR);
        if (a != b - 1)
        {
            res += resUpdater(prevBL, prevB, nextBL, nextB);
        }
        res += resUpdater(prevB, prevBR, nextB, nextBR);

        printf("%d\n", res);
    }
}
 
 
int main()
{
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
 
    long long testsNumber = 1;
 
    //cin >> testsNumber;
 
    for (int i = 0; i < testsNumber; i++)
    {
        solve();
    }
 
    return 0;
}