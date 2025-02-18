#include <iostream>
#include <bits/stdc++.h>

using namespace std;

const int maxN = 2 * 1e5;
int memory[maxN];

void solve()
{
    int n = 0;
    scanf("%d", &n);
    
    int memorySize = 0;
    for (int i = 0; i < n; i++)
    {
        int num = 0;
        scanf("%d", &num);

        auto index = lower_bound(memory, memory + memorySize, num) - memory;
        memory[index] = num;

        if (index == memorySize)
        {
            memorySize++;
        }
    }

    printf("%d", memorySize);
}

int main()
{
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    long long testsNumber = 1;

    //cin >> testsNumber;
    //scanf("%lld", &testsNumber);

    for (int i = 0; i < testsNumber; i++)
    {
        solve();
    }

    return 0;
}