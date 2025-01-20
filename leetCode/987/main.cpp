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


  struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode() : val(0), left(nullptr), right(nullptr) {}
      TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
      TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 };

class Solution {
public:
    vector<vector<int>> verticalTraversal(TreeNode* root) {
        int minIndex = INT_MAX;
        int maxIndex = INT_MIN;

        std::vector<std::multiset<pair<int, int>>> storage;
        storage.resize(2001);
        const int shift = 1000;

        struct Args
        {
            TreeNode* node;
            int column;
            int row;
            Args(TreeNode* node, int column, int row) : node(node), column(column), row(row) {}
        };
        
        std::stack<Args> s;

        s.emplace(root, 0, 0);

        while (!s.empty())
        {
            auto [node, column, row] = s.top();
            s.pop();
            
            minIndex = min(minIndex, column);
            maxIndex = max(maxIndex, column);

            storage[column + shift].emplace(row, node->val);
            node->left ? s.emplace(node->left, column - 1, row + 1), 0 : 0;
            node->right ? s.emplace(node->right, column + 1, row + 1), 0 : 0;
        }
        

        // auto recur = std::function<void(TreeNode* node, int column, int row)>();

        // recur = [&](TreeNode* node, int column, int row)
        // {
        //     minIndex = min(minIndex, column);
        //     maxIndex = max(maxIndex, column);

        //     storage[column + shift].emplace(row, node->val);
        //     node->left ? recur(node->left, column - 1, row + 1), 0 : 0;
        //     node->right ? recur(node->right, column + 1, row + 1), 0 : 0;
        // };

        // recur(root, 0, 0);

        vector<vector<int>> res;
        res.reserve(maxIndex - minIndex + 1);
        for (int i = minIndex; i <= maxIndex; i++)
        {
            //sort(storage[i + shift].begin(), storage[i + shift].end());
            auto& vec = res.emplace_back();
            vec.reserve(storage[i + shift].size());
            for (auto& pair : storage[i + shift])
            {
                vec.push_back(pair.second);
            }
        }
        

        return std::move(res);
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
    vector<int> v;

    v = {2, 3};
    out << (s.kthSmallestPath(v, 1) == "HHHVV") << std::endl;
    v = {2, 3};
    out << (s.kthSmallestPath(v, 2) == "HHVHV") << std::endl;
    v = {2, 3};
    out << (s.kthSmallestPath(v, 3) == "HHVVH") << std::endl;
    v = {15,15};
    out << (s.kthSmallestPath(v, 1) == "HHHHHHHHHHHHHHHVVVVVVVVVVVVVVV") << std::endl;
    // v = {2, 3};
    // out << (s.kthSmallestPath(v, 1) == "HHHVV") << std::endl;
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