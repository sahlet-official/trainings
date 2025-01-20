#include <iostream>
#include <bits/stdc++.h>

// didnt solve

using namespace std;

const int alphabetSize = 10;
const int nMax = 1000;

int storage[alphabetSize][nMax][nMax];

bool initer = false;

int countFormula(int as, int n, int k)
{
    if (n == 0 || k == 0 || as == 0)
    {
        return 0;
    }

    if (k * as < n)
    {
        return 0;
    }

    if (k * as == n)
    {
        return 1;
    }

    if (as == 1 && n <= k)
    {
        return 1;
    }

    if (k < nMax)
    {
        auto value = storage[as][n][k];
        if (value != 0)
        {
            return value;
        }
    }

    if (k > n)
    {
        return countFormula(as, n, n);
    }

    int res = 0;

    int limit = k;

    if (k == n)
    {
        res += 1;
        limit--;
    }

    for (int i = 0; i <= limit; i++)
    {
        res += countFormula(as - 1, n - i, k);
    }

    if(k < nMax)
    {
        storage[as][n][k] = res;
    }

    return res;
}

int countFormula(int n, int k)
{
    int res = 0;

    if (k > n)
    {
        k = n;
    }

    for (int i = 0; i <= k - 1; i++)
    {
        res += countFormula(9, n - i, k);
    }

    res *= 9;

    return res;
}

int solve(int n, int k) {
    if (!initer)
    {
        for (int i = 0; i < alphabetSize; i++)
        {
            for (int j = 0; j < nMax; j++)
            {
                for (int k = 0; k < nMax; k++)
                {
                    storage[i][j][k] = 0;
                }
            }
        }
    }

    return countFormula(n, k);
}

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

void solve(std::istream& in, std::ostream& out)
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string t_temp;
    getline(in, t_temp);

    int t = stoi(ltrim(rtrim(t_temp)));

    for (int t_itr = 0; t_itr < t; t_itr++) {
        string first_multiple_input_temp;
        getline(in, first_multiple_input_temp);

        vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

        int n = stoi(first_multiple_input[0]);

        int k = stoi(first_multiple_input[1]);

        int result = solve(n, k);

        out << result << "\n";
    }

    fout.close();
}

int main()
{
    //std::ios::sync_with_stdio(false);

    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");

    // solve(std::cin, std::cout);
    // solve(std::cin, fout);
    solve(fin, std::cout);
    // solve(fin, fout);
    

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}
