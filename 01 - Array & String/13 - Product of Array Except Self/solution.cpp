class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
       int n = nums.size();
        
        vector<int> ans(n);
        ans[0] = 1;
        
        int prefix = 1;
        int suffix = 1;
        for(int i = 1; i < n; i++){
            ans[i] = prefix * nums[i-1];
            prefix = prefix * nums[i-1];
        }
        
        for(int i = n-2; i >= 0; i--){
            ans[i] = (suffix * nums[i+1]) * ans[i];
            suffix = suffix * nums[i+1];
        }
        
        return ans;
    }
};
