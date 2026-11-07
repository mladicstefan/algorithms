
#include <algorithm>
#include <cstddef>
#include <iostream>
#include <numeric>
#include <vector>

int books(std::vector<int> &A, int B)
{
    if (B > A.size())
        return -1;

    long long hi = std::accumulate(A.begin(), A.end(), 0);
    long long lo = *std::max_element(A.begin(), A.end());

    while (lo < hi)
    {
        int mid = lo + (hi - lo) / 2;
        int students = 1;
        int sum = 0;
        for (int i = 0; i < A.size(); i++)
        {
            if (sum + A[i] > mid)
            {
                students++;
                sum = A[i];
            }
            else
                sum += A[i];
        }

        if (students > B)
            lo = mid + 1;
        else
            hi = mid;
    }
    return lo;
}

int main()
{
    std::vector<int> a1 = {12, 34, 67, 90};
    int b1 = 2;
    std::vector<int> a2 = {5, 17, 100, 11};
    int b2 = 4;
    std::cout << books(a1, b1) << "\n";
    std::cout << books(a2, b2) << "\n";
}
