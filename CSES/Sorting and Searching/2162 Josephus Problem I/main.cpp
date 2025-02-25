#include <iostream>
#include <bits/stdc++.h>
 
using namespace std;

const int maxN = 2 * 1e5;
int indexList[maxN + 1];
 
void solve() {
    int n = 0;
    scanf("%d", &n);

    for (int i = 1; i < n; i++)
    {
        indexList[i] = i + 1;
    }

    indexList[n] = 1;

    int curIndex = 1;

    while (indexList[curIndex] != curIndex)
    {
        printf("%d ", indexList[curIndex]);
        indexList[curIndex] = indexList[indexList[curIndex]];
        curIndex = indexList[curIndex];
    }

    printf("%d ", curIndex);
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