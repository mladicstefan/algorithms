#include <iostream>
#include <print>
#include <vector>

using namespace std;

namespace Solution
{

int max(vector<int> &v)
{
    if (v.empty())
        return 0;
    int mx = INT32_MIN;
    for (int num : v)
        if (num > mx)
            mx = num;
    return mx;
}

int minDays(vector<int> &bloomDay, int m, int k)
{
    if (static_cast<long long>(m * k) > static_cast<long long>(bloomDay.size()))
        return -1;

    int lo = 1;
    int hi = max(bloomDay);

    while (lo < hi)
    {
        int mid = lo + (hi - lo) / 2;

        auto it = cbegin(bloomDay);
        int bq = 0;
        int run = 0;

        for (; it < cend(bloomDay); ++it)
        {
            if (!(*it <= mid))
            {
                run = 0;
                continue;
            }
            ++run;
            if (run == k)
            {
                ++bq;
                run = 0;
            }
        }

        if (bq >= m)
            hi = mid;
        else
            lo = mid + 1;
    }
    return lo;
}
} // namespace Solution

void check(vector<int> bloomDay, int m, int k, int expected)
{
    int got = Solution::minDays(bloomDay, m, k);
    println("{}  bloomDay={} m={} k={} expected={} got={}",
            got == expected ? "PASS" : "FAIL", bloomDay, m, k, expected, got);
}

int main()
{
    check({1, 10, 3, 10, 2}, 3, 1, 3);
    check({1, 10, 3, 10, 2}, 3, 2, -1);
    check({7, 7, 7, 7, 12, 7, 7}, 2, 3, 12);
    return 0;
}
