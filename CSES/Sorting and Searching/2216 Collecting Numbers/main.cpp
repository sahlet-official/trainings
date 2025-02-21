#include <iostream>
#include <bits/stdc++.h>
 
using namespace std;

const int maxN = 2 * 1e5;
bool haveSeen[maxN + 2];
bool nextIsRight[maxN + 1];
 
void solve() {
    int n = 0;
    scanf("%d", &n);
 
    for (int i = 0; i < n; i++)
    {
        int v = 0;
        scanf("%d", &v);

        haveSeen[v] = true;
        nextIsRight[v] = !haveSeen[v + 1];
    }

    int res = 1;

    for (int i = 1; i < n; i++)
    {
        if (!nextIsRight[i])
        {
            res++;
        }
    }
 
    printf("%d", res);
}

void solve2() {
    int n = 0;
    scanf("%d", &n);

    int res = 1;
 
    for (int i = 0; i < n; i++)
    {
        int v = 0;
        scanf("%d", &v);

        haveSeen[v] = true;
        if (haveSeen[v + 1])
        {
            res++;
        }
    }
 
    printf("%d", res);
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
        solve2();
    }
 
    return 0;
}