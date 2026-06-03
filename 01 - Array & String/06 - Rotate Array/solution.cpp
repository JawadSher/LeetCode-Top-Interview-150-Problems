// Solution 1: TLE Caused
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
            k %= n;
            for(int i = 1; i <= k; i++){
                int l = nums[0];
                nums[0] = nums[n-1];
                
                for(int j = n-1; j > 1; j--){
                     nums[j] = nums[j-1];
                }
                nums[n-n+1] = l;
                
            }
    }
};

// Solution 2: O(n) Space Complexity
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();

        vector<int> rotated(n);

        for(int i = 0; i < n; i++){
            rotated[(i+k)%n] = nums[i];
        }

        nums = rotated;
    }
};

// Solution 3: Recommended Solution
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
            k %= n;
            for(int i = 0; i < n-i; i++){
                int t = nums[i];
                nums[i] = nums[n-i-1];
                nums[n-i-1] = t;
            }
            
            for(int i = 0; i < k/2; i++){
                 int t = nums[i];
                nums[i] = nums[k-i-1];
                nums[k-i-1] = t;
            }
            
            for(int i = k; i < k + (n-k)/2; i++){
                int t = nums[i];
                nums[i] = nums[n-(i-k)-1];
                nums[n-(i-k)-1] = t;
            }
    }
};
