class Solution {
public:
    int minimumDeletions(string word, int k) {
        unordered_map<char, int> cnt;
        for (auto &ch : word) {
            cnt[ch]++;
        }
        int res = word.size();
        for (auto &[_, a] : cnt) {
            int deleted = 0;
            for (auto &[_, b] : cnt) {
                if (a > b) {
                    deleted += b;
                } else if (b > a + k) {
                    deleted += b - (a + k);
                }
            }
            res = min(res, deleted);
        }
        return res;
    }
};

************************************************************************************************************************************************
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <string>
#include <limits.h>

class Solution {
public:
    int minimumDeletions(std::string word, int k) {
        std::unordered_map<char, int> cnt;
        for (char ch : word) {
            cnt[ch]++;
        }

        // Store frequencies in a vector
        std::vector<int> frequencies;
        for (const auto& entry : cnt) {
            frequencies.push_back(entry.second);
        }

        // Sort frequencies in descending order
        std::sort(frequencies.rbegin(), frequencies.rend());

        int res = word.size();
        int totalDeletions = 0;

        // Iterate through the sorted frequencies
        for (int i = 0; i < frequencies.size(); ++i) {
            // Calculate the number of deletions needed
            if (i > 0) {
                // If the current frequency is greater than the previous frequency + k
                if (frequencies[i] > frequencies[i - 1] + k) {
                    totalDeletions += frequencies[i] - (frequencies[i - 1] + k);
                }
            }
            // Update the result with the total deletions
            res = std::min(res, totalDeletions);
        }

        return res;
    }
};
