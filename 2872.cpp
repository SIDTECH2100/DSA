class Solution {
public:
    int maxKDivisibleComponents(int n, vector<vector<int>>& edges, vector<int>& values, int k) {
        vector<vector<int> > G(n);
        for(auto edge : edges){
            G[edge[0]].push_back(edge[1]);
            G[edge[1]].push_back(edge[0]);
        }
        stack <int> S;
        vector<int> parent(n);
        
        auto DFS = [&](int u, int p, auto &&DFS) -> void{
            parent[u] = p;
            S.push(u);
            for(auto v : G[u]){
                if(v == p) continue;
                DFS(v, u, DFS);
            }
        };
        DFS(0, -1, DFS);
        vector<long long> current_sum(n);
        for(int i = 0; i < n; i ++){
            current_sum[i] = values[i];
        }
        int ans = 0;
        while(!S.empty()){
            int u = S.top();
            S.pop();
            if(current_sum[u] % k == 0){
                ans += 1;
            }
            else{
                current_sum[parent[u]] += current_sum[u];
            }
        }
        return ans;
    }
};
************************************************************************************************************************************************
class Solution {
public:
    int maxKDivisibleComponents(int n, vector<vector<int>> &edges,
                                vector<int> &values, int k) {
        // Step 1: Create adjacency list from edges
        vector<int> adjList[n];
        for (auto edge : edges) {
            int node1 = edge[0];
            int node2 = edge[1];
            adjList[node1].push_back(node2);
            adjList[node2].push_back(node1);
        }
        // Step 2: Initialize component count
        int componentCount = 0;

        // Step 3: Start DFS traversal from node 0
        dfs(0, -1, adjList, values, k, componentCount);

        // Step 4: Return the total number of components
        return componentCount;
    }

private:
    int dfs(int currentNode, int parentNode, vector<int> adjList[],
            vector<int> &nodeValues, int k, int &componentCount) {
        // Step 1: Initialize sum for the current subtree
        int sum = 0;

        // Step 2: Traverse all neighbors
        for (auto neighborNode : adjList[currentNode]) {
            if (neighborNode != parentNode) {
                // Recursive call to process the subtree rooted at the neighbor
                sum += dfs(neighborNode, currentNode, adjList, nodeValues, k,
                           componentCount);
                sum %= k;  // Ensure the sum stays within bounds
            }
        }

        // Step 3: Add the value of the current node to the sum
        sum += nodeValues[currentNode];

        // Step 4: Check if the sum is divisible by k
        sum %= k;
        if (sum == 0) componentCount++;

        // Step 5: Return the computed sum for the current subtree
        return sum;
    }
};