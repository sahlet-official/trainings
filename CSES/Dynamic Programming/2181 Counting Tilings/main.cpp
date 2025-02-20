#include <iostream>
#include <bits/stdc++.h>

using namespace std;

const long long MOD = 1e9 + 7;

inline long long modSum(long long a, long long b)
{
    return ((a % MOD) + (b % MOD) + MOD) % MOD;
}

/*

const int maxN = 13;
const int maxM = 1000;
int dp[maxM + 1][1 << maxN];
vector<int> transfers[1 << maxN];

enum Symbols : char
{
    toTop = '1',
    toRight = '2',
    toBottom = '3',
    toLeft = '4',
};

//string states[1 << maxN];
int nextStateId = 1;
unordered_map<string, int> statesToId;

int n = 0, m = 0;

void fillStatesTransfers(const string& parentState, string& curState, int pos)
{
    if (pos >= curState.size())
    {
        if (statesToId.count(curState) == 0)
        {
            statesToId[curState] = nextStateId++;
        }

        //transfers[statesToId[curState]].push_back(statesToId[parentState]);

        int tmp = statesToId[curState];
        int tmp2 = statesToId[parentState];

        transfers[tmp].push_back(tmp2);

        return;
    }

    char prev = pos == 0 ? Symbols::toTop : curState[pos - 1];
    bool last = (pos + 1 == curState.size());

    char parentCh = parentState[pos];

    for (char ch = Symbols::toTop; ch <= Symbols::toLeft; ch++)
    {
        if (last && ch == Symbols::toRight)
        {
            continue;
        }

        if (prev == Symbols::toRight && ch != Symbols::toLeft)
        {
            continue;
        }

        if (ch == Symbols::toLeft && prev != Symbols::toRight)
        {
            continue;
        }

        if (parentCh == Symbols::toTop && ch != Symbols::toBottom)
        {
            continue;
        }

        if (ch == Symbols::toBottom && parentCh != Symbols::toTop)
        {
            continue;
        }

        curState[pos] = ch;

        fillStatesTransfers(parentState, curState, pos + 1);
    }
}

void fillStates(string& curState, int pos, bool goodForBottom, bool goodForTop)
{
    if (pos >= curState.size())
    {
        string childState(curState.size(), '0');
        if (statesToId.count(curState) == 0)
        {
            statesToId[curState] = nextStateId++;
        }

        fillStatesTransfers(curState, childState, 0);

        dp[1][statesToId[curState]] = goodForBottom ? 1 : 0;
        dp[m][statesToId[curState]] = goodForTop ? 0 : -1;

        return;
    }

    char prev = pos == 0 ? Symbols::toTop : curState[pos - 1];
    bool last = (pos + 1 == curState.size());

    for (char ch = Symbols::toTop; ch <= Symbols::toLeft; ch++)
    {
        if (last && ch == Symbols::toRight)
        {
            continue;
        }

        if (prev == Symbols::toRight && ch != Symbols::toLeft)
        {
            continue;
        }

        if (ch == Symbols::toLeft && prev != Symbols::toRight)
        {
            continue;
        }

        curState[pos] = ch;

        fillStates(curState, pos + 1, goodForBottom && (ch != Symbols::toBottom), goodForTop && (ch != Symbols::toTop));
    }
}

void solve()
{
    scanf("%d%d", &n, &m);

    if (n > m)
    {
        swap(n, m);
    }

    string state(n, '0');
    fillStates(state, 0, true, true);

    for (int i = 2; i <= m; i++)
    {
        for (int j = 1; j < nextStateId; j++)
        {
            if (dp[i][j] < 0)
            {
                continue;
            }

            for (int parent : transfers[j])
            {
                dp[i][j] = modSum(dp[i][j], dp[i - 1][parent]);
            }
            
        }
    }

    int res = 0;

    for (int j = 1; j < nextStateId; j++)
    {
        if (dp[m][j] < 0)
        {
            continue;
        }

        res = modSum(res, dp[m][j]);
    }

    printf("%d", res);
}

*/

const int maxN = 10;
const int maxM = 1000;
int dp[maxM + 2][1 << maxN];
deque<int> transfers[1 << maxN];

int n = 0, m = 0;

void fillTransfers()
{
    stack<pair<int, int>> childs;

    for (int parent = 0; parent < (1 << n); parent++)
    {
        childs.emplace(0, -1);

        while (!childs.empty())
        {
            auto curent = childs.top();
            childs.pop();

            curent.second++;

            while (curent.second < n && (parent & (1 << curent.second)))
            {
                curent.second++;
            }

            if (curent.second == n)
            {
                transfers[curent.first].emplace_back(parent);
                continue;
            }

            childs.emplace(curent.first | (1 << curent.second), curent.second);

            if (curent.second + 1 < n && (parent & (1 << curent.second + 1)) == 0)
            {
                childs.emplace(curent.first, curent.second + 1);
            }
        }
    }
}

void solve2()
{
    scanf("%d%d", &n, &m);

    if (n > m)
    {
        swap(n, m);
    }

    dp[1][0] = 1;

    fillTransfers();

    for (int i = 2; i <= m; i++)
    {
        for (int j = 0; j < (1 << n); j++)
        {
            for (int parent : transfers[j])
            {
                dp[i][j] = modSum(dp[i][j], dp[i - 1][parent]);
            }
            
        }
    }

    for (int parent : transfers[0])
    {
        dp[m + 1][0] = modSum(dp[m + 1][0], dp[m][parent]);
    }

    printf("%d", dp[m + 1][0]);
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
        //solve();
        solve2();
    }

    return 0;
}