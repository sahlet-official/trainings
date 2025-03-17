#include <iostream>
#include <bits/stdc++.h>

using namespace std;

namespace solve1
{
    enum CellState : char {
        Free = '.',
        A = 'A',
        Monster = 'M',
        Wall = '#',
    };

    const int maxN = 1000;
    CellState field[maxN + 1][maxN + 2];
    int distance[maxN + 1][maxN + 1];

    //bool visited[maxN + 1][maxN + 1];
    int dx[] = {0, +1, 0, -1}, dy[] = {-1, 0, +1, 0};
    int N, M;
    pair<int, int> start, end;
    vector<pair<int, int>> monsters;
    const int INF = 0x3F3F3F3F;
    
    bool canMoveTo(bool notMeButMonster, int x, int y)
    {
        return x <= M && x >= 1 && y <= N && y >= 1 && (field[x][y] == CellState::Free || (notMeButMonster && field[x][y] == CellState::A))/*  && !visited[x][y] */;
    }

    bool finish(int x, int y)
    {
        return x == M || x == 1 || y == N || y == 1;
    }

    void solve()
    {
        scanf("%d%d", &N, &M);

        for (int i = 1; i <= N; i++)
        {
            for (int j = 1; j <= M; j++)
            {
                scanf(" %c", &field[j][i]);

                if (field[j][i] == CellState::A)
                {
                    start = {j, i};
                }
                else if (field[j][i] == CellState::Monster)
                {
                    monsters.push_back({j, i});
                }
            }
        }

        memset(distance, INF, sizeof(distance));
        distance[start.first][start.second] = 0;

        queue<pair<int, int>> q;
        //visited[start.first][start.second] = true;

        q.push(start);
        for (auto& monster : monsters)
        {
            q.push(monster);
        }

        bool found = false;
            
        while (!q.empty() && !found)
        {
            auto cell = q.front();
            q.pop();

            bool itIsMe = field[cell.first][cell.second] == CellState::A;

            if (itIsMe)
            {
                if (finish(cell.first, cell.second))
                {
                    end = cell;
                    found = true;
                    break;
                }
            }

            for (int i = 0; i < 4; i++)
            {
                int x = cell.first + dx[i];
                int y = cell.second + dy[i];

                if (!canMoveTo(!itIsMe, x, y))
                {
                    continue;
                }

                field[x][y] = itIsMe ? CellState::A : CellState::Monster;

                if (itIsMe)
                {
                    distance[x][y] = distance[cell.first][cell.second] + 1;
                }
                
                q.push({x, y});
            }
        }
        
        if (found)
        {
            printf("YES\n");
            printf("%d\n", distance[end.first][end.second]);
            
            string res;
            res.reserve(distance[end.first][end.second]);

            auto cell = end;

            while (cell != start)
            {
                int i = 0;
                pair<int, int> prev;

                for (; i < 4; i++)
                {
                    prev = {cell.first + dx[i], cell.second + dy[i]};
                    if (distance[prev.first][prev.second] == (distance[cell.first][cell.second] - 1))
                    {
                        if (i == 0) res.push_back('D');
                        else if (i == 1) res.push_back('L');
                        else if (i == 2) res.push_back('U');
                        else if (i == 3) res.push_back('R');
                        break;
                    }
                }

                cell = prev;
            }
            

            reverse(res.begin(), res.end());
            printf("%s", res.c_str());
        }
        else
        {
            printf("NO\n");
        }
    }

}

int main()
{
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    std::ios::sync_with_stdio(false);
    // ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    // std::cout.tie(0);

    long long testsNumber = 1;

    // cin >> testsNumber;
    // scanf("%lld", &testsNumber);

    for (long long i = 0; i < testsNumber; i++)
    {
        solve1::solve();
    }

    return 0;
}