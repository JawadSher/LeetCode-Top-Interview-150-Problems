class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int n = nums.size();
        int k = -1;
        int c = 0;

        for(int i = 0; i < n; i++){
            if(c == 0) k = nums[i];

            if(k == nums[i]) c++;
            else c--;
        }


        return k;
    }
};
