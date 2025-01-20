#include <iostream>
#include <bits/stdc++.h>

using namespace std;

int NOD(int a, int b){
    while (a != b){
        if (a > b){
            a -= b;
        } else {
            b -= a;
        }
    }
    return a;
}

int NOK(int a, int b){
    return abs(a * b)/NOD(a, b);
}

const int MOD = 1e9 + 7;

long long multMod(long long a, long long b)
{
    return ((a % MOD) * (b % MOD)) % MOD;
}

long long sumMod(long long a, long long b)
{
    return ((a % MOD) + (b % MOD)) % MOD;
}

vector<int> pices;
std::vector<long long> stored_values(360361);

long long F(long long h)
{
    if (h == 0)
    {
        return 0;
    }

    if (stored_values[h] > 0)
    {
        return stored_values[h];
    }

    if (stored_values[h] < 0)
    {
        return 0;
    }

    std::stack<std::pair<long long, int>> stack;

    stack.push(std::make_pair(h, 0));

    while (!stack.empty())
    {
        bool pop = true;

        for (size_t i = stack.top().second; i < pices.size(); i++)
        {
            stack.top().second = i;
            int local_h = stack.top().first;
            
            if (local_h == pices[i])
            {
                stored_values[local_h] = sumMod(stored_values[local_h], 1);
            }
            else if (local_h > pices[i])
            {
                if (stored_values[local_h - pices[i]] > 0)
                {
                    stored_values[local_h] = sumMod(stored_values[local_h], stored_values[local_h - pices[i]]);
                }
                else if (stored_values[local_h - pices[i]] == 0)
                {
                    stack.push(std::make_pair(local_h - pices[i], 0));
                    pop = false;
                    break;
                }
            }
        }

        if (pop)
        {
            if (stored_values[stack.top().first] == 0)
            {
                stored_values[stack.top().first] = -1;
            }

            stack.pop();
        }
    }

    return stored_values[h];
}

long long powMod(long long a, long long p)
{
    long long res = 1;

    while (p)
    {
        if (p % 2)
        {
            res = multMod(res, a);
            p--;
            continue;
        }
        else
        {
            a = multMod(a, a);
            p /= 2;
        }
    }

    return res;
}

int solve(long long n, vector<int> heights) {
    pices = heights;

    int pices_nok = 1;

    for (int i = 0; i < pices.size(); i++)
    {
        pices_nok = NOK(pices_nok, pices[i]);
    }

    long long g = n / pices_nok;
    long long q = n % pices_nok;

    long long permutationsQ = F(q);
    long long permutationsNok = F(pices_nok);

    long long res = 1;

    if (permutationsNok)
    {
        res = powMod(permutationsNok, g);
    }

    if (permutationsQ)
    {
        res = multMod(res, permutationsQ);
    }

    return multMod(res, 2);
}

// int main()
// {
//     std::ios::sync_with_stdio(false);
//     //std::cout << "hello dude";

//     std::ifstream fin("input.txt");
//     std::ofstream fout("output.txt");

//     // solve(std::cin, std::cout);
//     // solve(std::cin, fout);
//     solve(fin, std::cout);
//     // solve(fin, fout);
    

//     return 0;
// }

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);


int main()
{
    std::ifstream fin("input.txt");
    ostream& fout = std::cout; //(getenv("OUTPUT_PATH"));

    auto& cin = fin;

    string n_temp;
    //getline(fin, n_temp);

    //long long n = stol(ltrim(rtrim(n_temp)));
    long long n;
    cin >> n;

    int heights_count;
    cin >> heights_count;

    //string heights_temp_temp;
    //cin >> heights_temp_temp;

    //vector<string> heights_temp = split(rtrim(heights_temp_temp));

    vector<int> heights(heights_count);

    for (int i = 0; i < heights_count; i++) {
        int heights_item;
        cin >> heights_item;

        heights[i] = heights_item;
    }

    int result = solve(n, heights);

    fout << result << "\n";

    //fout.close();

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
