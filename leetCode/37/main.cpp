#include <iostream>
#include <bits/stdc++.h>

using namespace std;

long long MOD = 1e9 + 7;

inline long long modMult(long long a, long long b)
{
    return ((a % MOD) * (b % MOD)) % MOD;
}

inline long long modSum(long long a, long long b)
{
    return ((a % MOD) + (b % MOD) + MOD) % MOD;
}

inline long long modPow(long long a, long long b)
{
    long long res = 1;
    while(b)
    {
        if (b % 2)
        {
            res = modMult(res, a);
        }

        b /= 2;
        a = modMult(a, a);
    }

    return res;
}

inline long long modInverse(long long a)
{
    return modPow(a, MOD - 2);
}

inline long long modDivide(long long a, long long b)
{
    a %= MOD;
    b %= MOD;
    if (a % b == 0) {
        return a / b;
    }

    return modMult(a, modInverse(b));
}

const int primeNumbersSieveSize = 500;
bool primeNumbersSieve[primeNumbersSieveSize];
const int primeNumbersSize = 100;
std::vector<int> primeNumbers;
std::unordered_map<int, int> primeNumbersIds(primeNumbersSieveSize);

void sieveOfEratosthenes()
{
    primeNumbers.clear();
    primeNumbers.reserve(primeNumbersSize);

    for (size_t i = 0; i < primeNumbersSieveSize; i++)
    {
        primeNumbersSieve[i] = true;
    }

    primeNumbersSieve[0] = false;
    primeNumbersSieve[1] = false;

    for (size_t i = 2; i * i < primeNumbersSieveSize; i++)
    {
        if (!primeNumbersSieve[i])
        {
            continue;
        }

        for (size_t j = i * i; j < primeNumbersSieveSize; j += i)
        {
            primeNumbersSieve[j] = false;
        }
    }

    for (int i = 0; i < primeNumbersSieveSize; i++)
    {
        if (primeNumbersSieve[i])
        {
            primeNumbers.push_back(i);
        
            primeNumbersIds[i] = primeNumbers.size() - 1;
        }
    }
}

std::vector<int> createPrimeMultStorageVect()
{
    std::vector<int> res(primeNumbers.size());

    return res;
}

void addVecTo(std::vector<int>& a, const std::vector<int>& b)
{
    for (int i = 0; i < a.size(); i++)
    {
        a[i] += b[i];
    }
}

void subtractVecFrom(std::vector<int>& a, const std::vector<int>& b)
{
    for (int i = 0; i < a.size(); i++)
    {
        a[i] -= b[i];
    }
}

int collapseVec(const std::vector<int>& a)
{
    int res = 1;
    for (int i = 0; i < a.size(); i++)
    {
        for (int j = 0; j < a[i]; j++)
        {
            res *= primeNumbers[i];
        }
    }

    return res;
}

std::unordered_map<int, std::vector<int>> primeFactorizationMap(1000);

const std::vector<int>& primeFactorization(const int n)
{
    {
        auto& res = primeFactorizationMap[n];
        if (!res.empty())
        {
            return res;
        }
    }

    if (n <= 1)
    {
        auto& res = primeFactorizationMap[n] = createPrimeMultStorageVect();
        return res;
    }

    if (primeNumbersSieve[n])
    {
        auto& res = primeFactorizationMap[n] = createPrimeMultStorageVect();
        res[primeNumbersIds[n]] = 1;
        return res;
    }

    for (int primeNumber : primeNumbers)
    {
        int numberOfMults = 0;

        int m = n;

        while (m % primeNumber == 0)
        {
            numberOfMults++;
            m /= primeNumber;
        }

        if (numberOfMults)
        {
            auto& res = primeFactorizationMap[n] = std::vector<int>(primeFactorization(m));
            res[primeNumbersIds[primeNumber]] += numberOfMults;
            return res;
        }
    }

    return primeFactorizationMap[n];
}

std::list<int> primeFactorizationWithoutStorage(int n)
{
    auto res = std::list<int>();

    if (n <= 1)
    {
        return res;
    }

    if (primeNumbersSieve[n])
    {
        res.push_back(1);
        return res;
    }

    for (int primeNumber : primeNumbers)
    {
        if (primeNumber * primeNumber > n)
        {
            break;
        }

        int numberOfMults = 0;

        while (n % primeNumber == 0)
        {
            numberOfMults++;
            n /= primeNumber;
        }

        if (numberOfMults)
        {
            res.push_back(numberOfMults);
        }
    }

    if (n > 1)
    {
        res.push_back(1);
    }

    return res;
}

class Solution {
    inline bool findEmpty(vector<vector<char>>& board, int& i, int& j)
    {
        for(; i < 9; i++)
        {
            for(; j < 9; j++)
            {
                if (board[i][j] == '.')
                {
                    return true;
                }
            }
            
            j = 0;
        }

        return false;
    }

    bool solveSudoku(vector<vector<char>>& board, int i, int j) {
        if (!findEmpty(board, i, j))
        {
            return true;
        }

        bool available[9] = {true, true, true, true, true, true, true, true, true};

        for(int k = 0; k < 9; k++)
        {
            if (board[i][k] != '.')
            {
                available[board[i][k] - '1'] = false;
            }
        }

        for(int k = 0; k < 9; k++)
        {
            if (board[k][j] != '.')
            {
                available[board[k][j] - '1'] = false;
            }
        }

        for(int k = i - (i % 3); k < i - (i % 3) + 3; k++)
        {
            for(int z = j - (j % 3); z < j - (j % 3) + 3; z++)
            {
                if (board[k][z] != '.')
                {
                    available[board[k][z] - '1'] = false;
                }
            }
        }

        for (int k = 0; k < 9; k++)
        {
            if (available[k])
            {
                board[i][j] = k + '1';
                if (solveSudoku(board, i, j))
                {
                    return true;
                }
            }
        }

        board[i][j] = '.';

        return false;
    }
public:
    void solveSudoku(vector<vector<char>>& board) {
        solveSudoku(board, 0, 0);
    }
};

bool equal(int i1, int i2)
{
    return i1 == i2;
}

bool equal(const vector<int>& v1, const vector<int>& v2)
{
    if (v1.size() != v2.size())
    {
        return false;
    }

    for (size_t i = 0; i < v1.size(); i++)
    {
        if (v1[i] != v2[i])
        {
            return false;
        }
    }
    
    return true;
}

bool equal(const vector<double>& v1, const vector<double>& v2)
{
    if (v1.size() != v2.size())
    {
        return false;
    }

    for (size_t i = 0; i < v1.size(); i++)
    {
        if (v1[i] - v2[i] > 0.000006)
        {
            return false;
        }
    }
    
    return true;
}

bool equal(double a, double b)
{
    if (a - b > 0.000006)
    {
        return false;
    }
    
    return true;
}

template<typename T>
bool equal(const vector<T>& v1, const vector<T>& v2)
{
    if (v1.size() != v2.size())
    {
        return false;
    }

    for (size_t i = 0; i < v1.size(); i++)
    {
        if (!equal(v1[i], v2[i]))
        {
            return false;
        }
    }
    
    return true;
}


void solve(std::istream& in, std::ostream& out)
{
    Solution s;
    vector<vector<char>> v;
    vector<vector<char>> vout;


    v = {{'5','3','.','.','7','.','.','.','.'},{'6','.','.','1','9','5','.','.','.'},{'.','9','8','.','.','.','.','6','.'},{'8','.','.','.','6','.','.','.','3'},{'4','.','.','8','.','3','.','.','1'},{'7','.','.','.','2','.','.','.','6'},{'.','6','.','.','.','.','2','8','.'},{'.','.','.','4','1','9','.','.','5'},{'.','.','.','.','8','.','.','7','9'}};
    vout = {{'5','3','4','6','7','8','9','1','2'},{'6','7','2','1','9','5','3','4','8'},{'1','9','8','3','4','2','5','6','7'},{'8','5','9','7','6','1','4','2','3'},{'4','2','6','8','5','3','7','9','1'},{'7','1','3','9','2','4','8','5','6'},{'9','6','1','5','3','7','2','8','4'},{'2','8','7','4','1','9','6','3','5'},{'3','4','5','2','8','6','1','7','9'}};;
    out << (s.solveSudoku(v), equal(v, vout)) << std::endl;
}

int main()
{
    std::ios::sync_with_stdio(false);
    //std::cout << "hello dude";

    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");

    // solve(std::cin, std::cout);
    // solve(std::cin, fout);
    solve(fin, std::cout);
    // solve(fin, fout);
    

    return 0;
}