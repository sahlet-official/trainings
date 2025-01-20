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

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        if (!head) {
            return nullptr;
        }

        ListNode* newList = nullptr;
        ListNode* tmp = nullptr;
        ListNode* last = head;


        for (int i = 0; i < k; i++) {
            if (!head) {
                newList = reverseKGroup(newList, i);
                return newList;
            }
            tmp = head->next;
            head->next = newList;
            newList = head;
            head = tmp;
        }

        if (head)
        {
            last->next = reverseKGroup(head, k);
        }

        return newList;
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


void solve(std::istream& in, std::ostream& out)
{
    Solution s;
    vector<int> v;

    v = {2, 3};
    auto l = new ListNode(1, new ListNode(2, new ListNode(3, new ListNode(4, new ListNode(5, nullptr)))));
    auto l2 = s.reverseKGroup(l, 2);
    out << l2->val << std::endl << l2->next->val << std::endl << l2->next->next->val << std::endl << l2->next->next->next->val << std::endl << l2->next->next->next->next->val << std::endl;
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