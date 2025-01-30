#include <iostream>
#include <bits/stdc++.h>

using namespace std;

long long res = 0;
char field[8][8] = {};
char verticals[8] = {};
char horizontals[8] = {};
char lDiagonals[15] = {};
char rDiagonals[15] = {};

bool underAttack(int i, int j)
{
    int vertical = i;
    int horizontal = j;
    int lDiagonal = 7 + i - j;
    int rDiagonal = j + i;

    return verticals[vertical] ||
    horizontals[horizontal] ||
    lDiagonals[lDiagonal] ||
    rDiagonals[rDiagonal];
}

bool freeSquare(int i, int j)
{
    return field[i][j] == '.';
}

bool placeQueen(int i, int j)
{
    if (!underAttack(i, j) && freeSquare(i, j))
    {
        int vertical = i;
        int horizontal = j;
        int lDiagonal = 7 + i - j;
        int rDiagonal = j + i;

        verticals[vertical]++;
        horizontals[horizontal]++;
        lDiagonals[lDiagonal]++;
        rDiagonals[rDiagonal]++;

        return true;
    }

    return false;
}

void replaceQueen(int i, int j)
{
    int vertical = i;
    int horizontal = j;
    int lDiagonal = 7 + i - j;
    int rDiagonal = j + i;

    verticals[vertical]--;
    horizontals[horizontal]--;
    lDiagonals[lDiagonal]--;
    rDiagonals[rDiagonal]--;
}

void backtracking(int column)
{
    if (column == 8)
    {
        res++;
        return;
    }

    for (int row = 0; row < 8; row++)
    {
        if (placeQueen(column, row))
        {
            backtracking(column + 1);
            replaceQueen(column, row);
        }
    }
}
 
void solve() {
    for (int row = 0; row < 8; row++)
    {
        for (int column = 0; column < 8; column++)
        {
            cin >> field[column][row];
        }
    }

    backtracking(0);

    cout << res;
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