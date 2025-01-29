#include <iostream>
#include <bits/stdc++.h>

using namespace std;

std::deque<pair<char, char>> res;

vector<char> letters = {};
vector<int> lettersCount = {};
string s;

void solve(int left) {
    if (!left)
    {
        cout << s << endl;
        return;
    }

    for(int i = 0; i < lettersCount.size(); i++)
    {
        if (lettersCount[i])
        {
            lettersCount[i]--;
            s[s.size() - left] = letters[i];
            solve(left - 1);
            lettersCount[i]++;
        }
    }
}
 
void solve() {
    cin >> s;

    sort(s.begin(), s.end());

    int uniq = 1;

    for (int i = 1; i < s.size(); i++)
    {
        if (s[i] != s[i - 1])
        {
            uniq++;
        }
    }

    int index = 0;
    letters = vector<char>(uniq);
    lettersCount = vector<int>(uniq);
    letters[index] = s[0];
    lettersCount[index] = 1;

    for (int i = 1; i < s.size(); i++)
    {
        if (s[i] != s[i - 1])
        {
            index++;
            letters[index] = s[i];
        }

        lettersCount[index]++;
    }

    int count = 1;

    for (size_t i = 2; i <= s.size(); i++)
    {
        count *= i;
    }

    for (size_t i = 0; i < lettersCount.size(); i++)
    {
        for (size_t j = 2; j <= lettersCount[i]; j++)
        {
            count /= j;
        }
    }

    cout << count << endl;

    solve(s.size());
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