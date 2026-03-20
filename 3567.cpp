
class Solution {
    multiset<int> window;

    int getMinDiff() {
        if (window.size() < 2) return 0;
        int diff = INT_MAX;
        auto it = window.begin();
        auto nxt = next(it);
        while (nxt != window.end() && diff != 1) {
            int d = *nxt - *it;
            if (d > 0 && d < diff) diff = d;
            ++it;
            ++nxt;
        }
        if (diff == INT_MAX) return 0;
        return diff;
    }

public:
    vector<vector<int>> minAbsDiff(vector<vector<int>>& grid, int k) {
        int m = grid.size(), n = grid[0].size();
        if (k == 1) {
            vector<vector<int>> res(m, vector<int>(n, 0));
            return res;
        }
        vector<vector<int>> res(m - k + 1, vector<int>(n - k + 1));
        for (int i = 0; i <= m - k; ++i) {
            window.clear();
            // Build first k*k window
            for (int r = i; r < i + k; ++r) {
                for (int c = 0; c < k; ++c) {
                    window.insert(grid[r][c]);
                }
            }
            int diff = getMinDiff();
            for (int j = 1; j <= n - k; ++j) {
                res[i][j - 1] = diff;
                // Remove left column: O(k log(k^2))
                for (int r = i; r < i + k; ++r) {
                    window.erase(window.find(grid[r][j - 1]));
                }
                // Add right column: O(k log(k^2))
                for (int r = i; r < i + k; ++r) {
                    window.insert(grid[r][j + k - 1]);
                }
                diff = getMinDiff();
            }
            res[i][n - k] = diff;
        }
        return res;
    }
};