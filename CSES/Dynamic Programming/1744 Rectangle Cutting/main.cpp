#include <iostream>
#include <bits/stdc++.h>

using namespace std;

const int maxL = 500;
int memory2[maxL + 1][maxL + 1];

struct Node
{
    int a1 = 0, a2 = 0;
    int b1 = 0, b2 = 0;
    std::shared_ptr<Node> next1;
    std::shared_ptr<Node> next2;
};


pair<int, std::shared_ptr<Node>>  memory[maxL + 1][maxL + 1];

int dp(int a, int b, std::shared_ptr<Node>& node)
{
    if (a == b)
    {
        return 0;
    }

    if (a > b)
    {
        swap(a, b);
    }

    // if (b % a == 0)
    // {
    //     memory[a][b] = b / a - 1;
    // }

    if (memory[a][b].first)
    {
        node = memory[a][b].second;

        return memory[a][b].first;
    }

    node = std::make_shared<Node>();

    int res = INT_MAX;

    std::shared_ptr<Node> next1;
    std::shared_ptr<Node> next2;

    for (int i = 1; i <= b / 2; i++)
    {
        next1 = nullptr;
        next2 = nullptr;
        int subres = min(res, dp(a, b - i, next1) + dp(a, i, next2) + 1);
        if (res != subres)
        {
            res = subres;
            node->a1 = a;
            node->a2 = a;
            node->b1 = i;
            node->b2 = b-i;
            node->next1 = next1;
            node->next2 = next2;
        }
    }

    for (int i = 1; i <= a / 2; i++)
    {
        next1 = nullptr;
        next2 = nullptr;
        int subres = min(res, dp(a - i, b, next1) + dp(i, b, next2) + 1);
        if (res != subres)
        {
            res = subres;
            node->a1 = i;
            node->a2 = a-i;
            node->b1 = b;
            node->b2 = b;
            node->next1 = next1;
            node->next2 = next2;
        }
    }

    memory[a][b] = {res, node};
    
    return res;
}

void print(std::shared_ptr<Node> node, int level = 0)
{
    if (!node)
    {
        return;
    }

    printf("level = %d, a1 = %d, b1 = %d, a2 = %d, b2 = %d\n", level, node->a1, node->b1, node->a2, node->b2);

    print(node->next1, level + 1);
    print(node->next2, level + 1);
}

void solve()
{
    int a = 0, b = 0;
    scanf("%d%d", &a, &b);

    std::shared_ptr<Node> root;
    printf("%d\n", dp(a, b, root));

    print(root);
}

void solve2()
{
    int a = 0, b = 0;
    scanf("%d%d", &a, &b);

    if (a > b)
    {
        swap(a, b);
    }

    for (int i = 1; i <= a; i++)
    {
        for (int j = 1; j <= b; j++)
        {
            if (j % i == 0)
            {
                memory2[i][j] = j / i - 1;
                continue;
            }

            memory2[i][j] = INT_MAX;

            for (int k = 1; k <= j / 2; k++)
            {
                memory2[i][j] = min(
                    memory2[i][j],
                    memory2[i][j-k] + memory2[i][k] + 1
                );
            }

            for (int k = 1; k <= i / 2; k++)
            {
                memory2[i][j] = min(
                    memory2[i][j],
                    memory2[i-k][j] + memory2[k][j] + 1
                );
            }
        }
    }
    
    printf("%d\n", memory2[a][b]);
}

int main()
{
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    long long testsNumber = 1;

    // cin >> testsNumber;
    // scanf("%lld", &testsNumber);

    for (int i = 0; i < testsNumber; i++)
    {
        solve2();
    }

    return 0;
}