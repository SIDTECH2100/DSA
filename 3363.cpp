class Solution {
public:
    int maxCollectedFruits(vector<vector<int>>& fruits) {
        int n = fruits.size();
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            ans += fruits[i][i];
        }

        auto dp = [&]() -> int {
            vector<int> prev(n, INT_MIN), curr(n, INT_MIN);
            prev[n - 1] = fruits[0][n - 1];
            for (int i = 1; i < n - 1; ++i) {
                for (int j = max(n - 1 - i, i + 1); j < n; ++j) {
                    int best = prev[j];
                    if (j - 1 >= 0) {
                        best = max(best, prev[j - 1]);
                    }
                    if (j + 1 < n) {
                        best = max(best, prev[j + 1]);
                    }
                    curr[j] = best + fruits[i][j];
                }
                swap(prev, curr);
            }
            return prev[n - 1];
        };

        ans += dp();

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < i; ++j) {
                swap(fruits[j][i], fruits[i][j]);
            }
        }

        ans += dp();
        return ans;
    }
};



**********************************************************************************************************************************************************************
class Solution {
public:
    int maxCollectedFruits(vector<vector<int>>& grid) {
        int n = grid.size(), res = 0;

        for (int i = 0; i < n; i++) {
            res += grid[i][i];
        }

        for (int pass = 0; pass < 2; pass++) {
            if (pass == 1) {
                for (int i = 0; i < n; i++) {
                    for (int j = i + 1; j < n; j++) {
                        swap(grid[i][j], grid[j][i]);
                    }
                }
            }

            vector<int> prev(n, -1), curr(n, -1);
            prev[n - 1] = grid[0][n - 1];

            for(int row = 1; row < n - 1; row++) {
                fill(curr.begin(), curr.end(), -1);
                for (int i = 0; i < n; i++) {
                    if (prev[i] < 0) continue;
                    if (i > 0) 
                        curr[i - 1] = max(curr[i - 1], prev[i] + grid[row][i - 1]);
                    if (i < n - 1) 
                        curr[i + 1] = max(curr[i + 1], prev[i] + grid[row][i + 1]);
                    curr[i] = max(curr[i], prev[i] + grid[row][i]);
                }
                swap(prev, curr);
            }
            res += prev[n - 1];
        }
        return res;
    }
};