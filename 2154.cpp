class Solution {
public:
    int findFinalValue(vector<int>& nums, int original) {
        sort(nums.begin(), nums.end());
        for (int num : nums) {
            if (original == num) {
                original *= 2;
            }
        }
        return original;
    }
};

***************************************************************************************************8

class Solution {
public:
    int findFinalValue(vector<int>& nums, int original) {
        unordered_set<int> s(nums.begin(), nums.end());
        while (s.count(original)) {
            original *= 2;
        }
        return original;
    }
};