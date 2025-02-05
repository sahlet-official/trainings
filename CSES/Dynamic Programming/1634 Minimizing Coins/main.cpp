#include <iostream>
#include <bits/stdc++.h>

using namespace std;

int n = 0, x = 0;
int c[100];

int memory[(int)1e6 + 1] = {};

void solve() {
    cin >> n >> x;

    for (int i = 0; i < n; i++)
    {
        cin >> c[i];
    }

    memset(memory, -1, sizeof(memory));

    memory[0] = 0;

    for (int i = 0; i <= x; i++)
    {
        if (memory[i] != -1)
        {
            int count = memory[i] + 1;

            for (int j = 0; j < n; j++)
            {
                int nextIndex = i + c[j];
                if (nextIndex <= x)
                {
                    if (memory[nextIndex] == -1 || memory[nextIndex] > count)
                    {
                        memory[nextIndex] = count;
                    }
                }
            }
        }
    }

    cout << memory[x] << endl;
}

void solve2() {
    cin >> n >> x;

    memory[0] = 0;
    
    fill(memory + 1, memory + x + 1, INT_MAX);

    for (int i = 0; i < n; i++)
    {
        int coin = 0;
        cin >> coin;

        for (int j = 0; j <= x - coin; j++)
        {
            if (memory[j] != INT_MAX)
            {
                int nextIndex = j + coin;
                memory[nextIndex] = min(memory[nextIndex], memory[j] + 1);
            }
        }
    }

    cout << (memory[x] == INT_MAX ? -1 : memory[x]) << endl;
}

void solve3() {
    // scanf("%d %d", &n, &x);
    cin >> n >> x;
    fill(memory+1, memory+x+1, INT_MAX);
    for(int i = 0; i < n; i++){
        int c = 0;
        // scanf("%d", &c);
        cin >> c;
        for(int j = 0; j <= x-c; j++)
            if(memory[j] != INT_MAX)
                memory[j+c] = min(memory[j+c], memory[j]+1);
    }
    printf("%d\n", memory[x] == INT_MAX ? -1 : memory[x]);
}

int main()
{
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    // std::ios::sync_with_stdio(false);
    ios_base::sync_with_stdio(false);
    std::cin.tie(0);

    long long testsNumber = 1;

    //cin >> testsNumber;

    for (int i = 0; i < testsNumber; i++)
    {
        solve2();
    }

    return 0;
}