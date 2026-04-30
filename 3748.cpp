
class Solution {
public:
    int maxPathScore(vector<vector<int>>& grid, int k) {
        ++k;
        const int n = grid.size(), m = grid[0].size();
        vector<vector<int>> dp(m, vector<int>(k));
        for(int i = 1; i != m; ++i){
            dp[i][0] = -1;
            for(int h = 0, b = grid[0][i] > 0; h != k - b; ++h){
                dp[i][h + b] = dp[i - 1][h] + grid[0][i] * (dp[i - 1][h] != -1);
            }
        }
        for(int i = 1; i != n; ++i){
            for(int j = 0; j != m; ++j){
                vector<int> v(k);
                v[0] = -1;
                if(!j){
                    for(int h = 0, b = grid[i][j] > 0; h != k - b; ++h){
                        v[h + b] = dp[j][h] + grid[i][j] * (dp[j][h] != -1);
                    }
                }else{
                    for(int h = 0, b = grid[i][j] > 0; h != k - b; ++h){
                        v[h + b] = max(dp[j - 1][h] + grid[i][j] * (dp[j - 1][h] != -1), dp[j][h] + grid[i][j] * (dp[j][h] != -1));
                    }
                }
                dp[j] = v;
            }
        }
        for(int i = k - 1; i >= 0; --i) if(dp[m - 1][i] != -1) return dp[m - 1][i];
        return -1;
    }
};