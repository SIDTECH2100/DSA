#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    // DFS to find the smallest lex character in the component
    void dfs(unordered_map<char, vector<char>>& adj, char cur, vector<int>& vis, vector<char>& componentChars, char& minChar) {
        vis[cur - 'a'] = 1;
        componentChars.push_back(cur);
        minChar = min(minChar, cur);
        for (char neighbor : adj[cur]) {
            if (vis[neighbor - 'a'] == 0) {
                dfs(adj, neighbor, vis, componentChars, minChar);
            }
        }
    }

    string smallestEquivalentString(string s1, string s2, string baseStr) {
        int n = s1.length();
        unordered_map<char, vector<char>> adj;

        // Build the equivalence graph
        for (int i = 0; i < n; ++i) {
            char u = s1[i];
            char v = s2[i];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        vector<int> vis(26, 0);
        vector<char> smallest(26);
        for (int i = 0; i < 26; ++i) {
            // Initialize smallest array as self
            smallest[i] = 'a' + i;
        }

        // Precompute the smallest equivalent character for each connected component
        for (char ch = 'a'; ch <= 'z'; ++ch) {
            if (vis[ch - 'a'] == 0) {
                vector<char> componentChars;
                char minChar = ch;
                dfs(adj, ch, vis, componentChars, minChar);
                // Assign the smallest character found to all characters in the component
                for (char c : componentChars) {
                    smallest[c - 'a'] = minChar;
                }
            }
        }

        // Build the result by replacing each character in baseStr with the smallest equivalent
        string result;
        result.reserve(baseStr.size());
        for (char ch : baseStr) {
            result.push_back(smallest[ch - 'a']);
        }

        return result;
    }
};

 

***************************************************************************************************************************************
class Solution {
public:
    // DFS to find the smallest lex character in the component
    char dfs(unordered_map<char, vector<char>>& adj, char cur, vector<int>& vis) {
        vis[cur - 'a'] = 1;
        char minChar = cur;
        for (char neighbor : adj[cur]) {
            if (vis[neighbor - 'a'] == 0) {
                minChar = min(minChar, dfs(adj, neighbor, vis));
            }
        }
        return minChar;
    }

    string smallestEquivalentString(string s1, string s2, string baseStr) {
        int n = s1.length();
        unordered_map<char, vector<char>> adj;

        // Step 1: Build the equivalence graph
        for (int i = 0; i < n; ++i) {
            char u = s1[i];
            char v = s2[i];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        // Step 2: Replace each character in baseStr with the smallest equivalent
        string result;
        for (char ch : baseStr) {
            vector<int> vis(26, 0);
            char minChar = dfs(adj, ch, vis);
            result.push_back(minChar);
        }

        return result;
    }
};








