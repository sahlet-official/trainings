#include <iostream>
#include <bits/stdc++.h>

using namespace std;

const int n = 7;
char pattern[n*n] = {};
bool vis[n + 1][n + 1] = {};
int ans = 0;

bool isFree(int row, int col)
{
    return row >= 1 && row <= n && col >= 1 && col <= n && !vis[row][col];
}

void dfs(int row, int col, int step)
{
    bool finish = row == n && col == 1;
    bool lastStep = step == (n*n - 1);
    if (finish || lastStep)
    {
        ans += finish && lastStep;
        return;
    }

    vis[row][col] = true;

    if ((pattern[step] == 'D' || pattern[step] == '?'))
    {
        if (isFree(row + 1, col) &&
            !(!isFree(row + 1, col + 1) && isFree(row, col + 1)) &&
            !(!isFree(row + 1, col - 1) && isFree(row, col - 1)) &&
            !(
                !isFree(row, col - 1) && !isFree(row, col + 1) &&
                (isFree(row - 1, col) || isFree(row - 1, col - 1) || isFree(row - 1, col + 1))
            )
        )
        {
            dfs(row + 1, col, step + 1);
        }
    }

    if ((pattern[step] == 'R' || pattern[step] == '?'))
    {
        if (isFree(row, col + 1) &&
            !(!isFree(row + 1, col + 1) && isFree(row + 1, col)) &&
            !(!isFree(row - 1, col + 1) && isFree(row - 1, col)) &&
            !(
                !isFree(row - 1, col) && !isFree(row + 1, col) &&
                (isFree(row, col - 1) || isFree(row - 1, col - 1) || isFree(row + 1, col - 1))
            )
        )
        {
            dfs(row, col + 1, step + 1);
        }
    }

    if ((pattern[step] == 'U' || pattern[step] == '?'))
    {
        if (isFree(row - 1, col) &&
            !(!isFree(row - 1, col + 1) && isFree(row, col + 1)) &&
            !(!isFree(row - 1, col - 1) && isFree(row, col - 1)) &&
            !(
                !isFree(row, col - 1) && !isFree(row, col + 1) &&
                (isFree(row + 1, col) || isFree(row + 1, col - 1) || isFree(row + 1, col + 1))
            )
        )
        {
            dfs(row - 1, col, step + 1);
        }
    }

    if ((pattern[step] == 'L' || pattern[step] == '?'))
    {
        if (isFree(row, col - 1) &&
            !(!isFree(row + 1, col - 1) && isFree(row + 1, col)) &&
            !(!isFree(row - 1, col - 1) && isFree(row - 1, col)) &&
            !(
                !isFree(row - 1, col) && !isFree(row + 1, col) &&
                (isFree(row, col + 1) || isFree(row - 1, col + 1) || isFree(row + 1, col + 1))
            )
        )
        {
            dfs(row, col - 1, step + 1);
        }
    }
    
    vis[row][col] = false;
}
 
void solve() {
    cin >> pattern;
    dfs(1, 1, 0);
    cout << ans << endl;
}


int main()
{
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    long long testsNumber = 1;

    // cin >> testsNumber;

    for (int i = 0; i < testsNumber; i++)
    {
        solve();
    }

    return 0;
}