class Solution {
public:
    int maxDifference(string s) {
        int oddMax = INT_MIN;
        int evenMin = INT_MAX;
        vector<int> freq(26, 0); // Frequency array for 26 lowercase letters

        // Count frequencies of each character
        for (char c : s) {
            freq[c - 'a']++;
        }

        // Determine the maximum odd frequency and minimum even frequency
        for (int f : freq) {
            if (f % 2 == 1) {
                oddMax = max(oddMax, f);
            } else if (f > 0) {
                evenMin = min(evenMin, f);
            }
        }

        // If no odd frequency was found, set oddMax to 0
        if (oddMax == INT_MIN) {
            oddMax = 0;
        }
        // If no even frequency was found, set evenMin to 0
        if (evenMin == INT_MAX) {
            evenMin = 0;
        }

        return oddMax - evenMin;
    }
};

**********************************************************************************************************************************88

class Solution {
public:
    int maxDifference(string s) {
        unordered_map<char, int> mp;
        for (char c : s) {
            mp[c]++;
        }
        int a1 = INT_MIN, a2 = INT_MAX;
        for (auto [c, freq] : mp) {
            if (freq % 2)
                a1 = max(a1, freq);
            else
                a2 = min(a2, freq);
        }
        return a1 - a2;
    }
};