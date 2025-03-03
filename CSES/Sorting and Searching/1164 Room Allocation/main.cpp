#include <iostream>
#include <bits/stdc++.h>
 
using namespace std;

struct Record
{
    int time;
    bool recordType;
    int customerId;

    bool operator<(const Record& r)
    {
        if (time == r.time)
        {
            return recordType < r.recordType;
        }

        return time < r.time;
    }
};

const int maxN = 2 * 1e5;
int customerToRoom[maxN];
Record schedule[maxN * 2];
 
void solve() {
    int n = 0;
    scanf("%d", &n);
 
    for (int i = 0; i < n; i++)
    {
        int a = 0, b = 0;
        scanf("%d%d", &a, &b);

        Record& record1 = schedule[2*i];
        Record& record2 = schedule[2*i + 1];
        
        record1.customerId = i;
        record1.time = a;
        record1.recordType = 0;

        record2.customerId = i;
        record2.time = b;
        record2.recordType = 1;
    }

    sort(schedule, schedule + 2*n);

    int rooms = 0;

    unordered_set<int> freeRooms;

    for (int i = 0; i < 2*n; i++)
    {
        auto& record = schedule[i];

        if (record.recordType == 0)
        {
            int room = 0;
            if (freeRooms.empty())
            {
                rooms++;
                room = rooms;
            }
            else
            {
                room = *freeRooms.begin();
                freeRooms.erase(room);
            }

            customerToRoom[record.customerId] = room;
        }
        else if (record.recordType == 1)
        {
            freeRooms.insert(customerToRoom[record.customerId]);
        }
    }

    printf("%d\n", rooms);
    for (int i = 0; i < n; i++)
    {
        printf("%d ", customerToRoom[i]);
    }
}
 
 
int main()
{
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
 
    long long testsNumber = 1;
 
    //cin >> testsNumber;
 
    for (int i = 0; i < testsNumber; i++)
    {
        solve();
    }
 
    return 0;
}