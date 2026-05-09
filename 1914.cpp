class Solution {

   queue<int> getLayerKElements(int layer, int m, int n, int k,
                                vector<vector<int>>& grid) {

       deque<int> dq;

       for (int j = layer + 1; j < n && dq.size() < k; j++) {
           dq.push_front(grid[layer][j]);
       }

       for (int i = layer + 1; i < m && dq.size() < k; i++) {
           dq.push_front(grid[i][n - 1]);
       }

       for (int j = n - 2; j >= layer && dq.size() < k; j--) {
           dq.push_front(grid[m - 1][j]);
       }

       for (int i = m - 2; i > layer && dq.size() < k; i--) {
           dq.push_front(grid[i][layer]);
       }

       return queue<int>(dq);
   }

   void rotateLayer(int layer, int m, int n, int k,
                    vector<vector<int>>& grid) {

       queue<int> q = getLayerKElements(layer, m, n, k, grid);

       for (int i = layer; i < m; i++) {
           q.push(grid[i][layer]);
           grid[i][layer] = q.front();
           q.pop();
       }

       for (int j = layer + 1; j < n; j++) {
           q.push(grid[m - 1][j]);
           grid[m - 1][j] = q.front();
           q.pop();
       }

       for (int i = m - 2; i >= layer; i--) {
           q.push(grid[i][n - 1]);
           grid[i][n - 1] = q.front();
           q.pop();
       }

       for (int j = n - 2; j > layer; j--) {
           q.push(grid[layer][j]);
           grid[layer][j] = q.front();
           q.pop();
       }
   }

   vector<vector<int>> simulate(int m, int n, int k,
                                vector<vector<int>>& grid) {

       int layer = 0, cnt = 0;

       while (layer < min(m, n)) {
           int len = 2 * (m + n - (2 * layer)) - 4;
           int kth = k % len;

           if (kth != 0) {
               rotateLayer(layer, m, n, kth, grid);
               cnt++;
           }

           layer++, m--, n--;
       }

       // cout << "Rotated Layer Count: " << cnt << endl;

       return grid;
   }

public:
   vector<vector<int>> rotateGrid(vector<vector<int>>& grid, int k) {

       int m = grid.size();
       int n = grid[0].size();

       return simulate(m, n, k, grid);
   }
};