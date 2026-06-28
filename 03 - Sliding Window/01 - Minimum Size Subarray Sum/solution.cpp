// O(N)2 Time Complexity - TLE Caused
class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int n = nums.size();
        int minLen = INT_MAX;

        for(int i = 0; i < n; i++){
            int j = i;
            int sum = 0;

            while (j < n){
                sum += nums[j];

                if(sum >= target){
                    minLen = min(minLen, j - i + 1);
                    break;
                }
                j++;
            }
        }

        return minLen == INT_MAX ? 0 : minLen;
    }
};

// O(N) Time Complexity - Optimized Solution
class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int n = nums.size();
        int minLen = INT_MAX;
        int sum = 0;
        int j = 0;

        for(int i = 0; i < n; i++){
            sum += nums[i];

            while (sum >= target){
                minLen = min(minLen, i - j + 1);

                sum -= nums[j];
                j++;
            }
        }

        return minLen == INT_MAX ? 0 : minLen;
    }
};
