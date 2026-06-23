class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        vector<int> indexes = {1, 2};
        int s = 0;
        int e = numbers.size() - 1;

        while(s < e){
            if(numbers[s] + numbers[e] == target) {
                indexes[0] = s + 1;
                indexes[1] = e + 1;

                return indexes;
            }

            if(numbers[s] + numbers[e] > target) e--;
            if(numbers[s] + numbers[e] < target) s++;
        }

        return indexes;
    }
};
