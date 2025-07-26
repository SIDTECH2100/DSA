#include <vector>
#include <algorithm>

class Solution {
public:
    long long maxSubarrays(int n, std::vector<std::vector<int>>& conflictingPairs) {
        std::vector<std::vector<int>> right(n + 1);
        for (const auto& pair : conflictingPairs) {
            right[std::max(pair[0], pair[1])].push_back(std::min(pair[0], pair[1]));
        }

        long long ans = 0;
        std::vector<long long> left = {0, 0};
        std::vector<long long> bonus(n + 1, 0);

        for (int r = 1; r <= n; ++r) {
            for (int l_val : right[r]) {
                // Manually update top two values
                if (l_val > left[0]) {
                    left = {static_cast<long long>(l_val), left[0]};
                } else if (l_val > left[1]) {
                    left = {left[0], static_cast<long long>(l_val)};
                }
            }

            ans += r - left[0];
            
            if (left[0] > 0) {
                bonus[left[0]] += left[0] - left[1];
            }
        }
        
        long long max_bonus = 0;
        for(long long b : bonus) {
            max_bonus = std::max(max_bonus, b);
        }

        return ans + max_bonus;
    }
};

*************************************************************************************************************************************

class Solution {
public:
    long long maxSubarrays(int n, vector<vector<int>>& conflictingPairs) {
        vector<int> bMin1(n + 1, INT_MAX), bMin2(n + 1, INT_MAX);
        for (const auto& pair : conflictingPairs) {
            int a = min(pair[0], pair[1]), b = max(pair[0], pair[1]);
            if (bMin1[a] > b) {
                bMin2[a] = bMin1[a];
                bMin1[a] = b;
            } else if (bMin2[a] > b) {
                bMin2[a] = b;
            }
        }
        long long res = 0;
        int ib1 = n, b2 = INT_MAX;
        vector<long long> delCount(n + 1, 0);
        for (int i = n; i >= 1; i--) {
            if (bMin1[ib1] > bMin1[i]) {
                b2 = min(b2, bMin1[ib1]);
                ib1 = i;
            } else {
                b2 = min(b2, bMin1[i]);
            }
            res += min(bMin1[ib1], n + 1) - i;
            delCount[ib1] +=
                min(min(b2, bMin2[ib1]), n + 1) - min(bMin1[ib1], n + 1);
        }
        return res + *max_element(delCount.begin(), delCount.end());
    }
};