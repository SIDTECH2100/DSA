#include <string>
#include <stack>
#include <vector>

using namespace std;

class Solution {
public:
    string robotWithString(string s) {
        vector<int> last(26, -1);
        for (int i = 0; i < s.size(); ++i) {
            last[s[i] - 'a'] = i; // Record the last occurrence of each character
        }

        string ans;
        stack<char> stk;
        int nextIndex = 0; // Pointer to track the next character in the input string

        for (int i = 0; i < s.size(); ++i) {
            stk.push(s[i]);

            // While we can pop from the stack
            while (!stk.empty()) {
                char topChar = stk.top();
                bool canPop = true;

                // Check if there are any characters left in the input that are less than the top character
                for (int ch = 0; ch < topChar - 'a'; ++ch) {
                    if (last[ch] > i) {
                        canPop = false; // If there's a smaller character left, we can't pop
                        break;
                    }
                }

                if (canPop) {
                    ans.push_back(topChar);
                    stk.pop();
                } else {
                    break; // Stop popping if we can't pop the top character
                }
            }
        }

        // Pop any remaining characters in the stack
        while (!stk.empty()) {
            ans.push_back(stk.top());
            stk.pop();
        }

        return ans;
    }
};



********************************************************************************************************************************************************8
class Solution
{
public:
    string robotWithString(string s)
    {
        vector<int> last(26, -1);
        for (int i = 0; i < s.size(); ++i)
            last[s[i] - 'a'] = i;

        string ans;
        stack<char> stk;
        for (int i = 0; i < s.size(); ++i)
        {
            stk.push(s[i]);
            while (stk.size())
            {
                bool exist = false;
                for (int ch = 0; ch < stk.top() - 'a'; ++ch)
                {
                    if (i < last[ch])
                    {
                        exist = true;
                        break;
                    }
                }
                if (exist)
                    break;
                ans.push_back(stk.top());
                stk.pop();
            }
        }
        while (stk.size())
        {
            ans.push_back(stk.top());
            stk.pop();
        }
        return ans;
    }
};