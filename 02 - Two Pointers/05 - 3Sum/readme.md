# 3Sum

## Problem Statement

Given an integer array `nums`, return all the triplets `[nums[i], nums[j], nums[k]]` such that `i != j`, `i != k`, and `j != k`, and `nums[i] + nums[j] + nums[k] == 0`.

**Important Note:** The solution set must not contain duplicate triplets.

### Example

**Input:** `nums = [-1, 0, 1, 2, -1, -4]`
**Output:** `[[-1, -1, 2], [-1, 0, 1]]`

#### Problem URL [3Sum - LeetCode](https://leetcode.com/problems/3sum/description/?envType=study-plan-v2&envId=top-interview-150)

## Solution

```cpp
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> triplets;
        sort(nums.begin(), nums.end());
        int n = nums.size();
        
        for(int i = 0; i < n-2; i++){
            // Skip duplicate values for the first element
            if(i > 0 && nums[i] == nums[i-1]) continue;
            
            int j = i + 1;
            int k = n-1;

            while (j < k){
                int sum = nums[i] + nums[j] + nums[k];

                if(sum == 0){
                    triplets.push_back({nums[i], nums[j], nums[k]});
                    j++;
                    k--;

                    // Skip duplicate values for second and third elements
                    while(j < k && nums[j] == nums[j-1]) j++;
                    while(j < k && nums[k] == nums[k+1]) k--;
                } else if(sum > 0) {
                    k--; // Sum too large, decrease k
                } else {
                    j++; // Sum too small, increase j
                }
            }
        }

        return triplets;
    }
};

```

## Explanation

### How it works

This solution uses the **Sorting + Two Pointers** technique:

1. **Sorting:** First, we sort the array. This allows us to easily handle duplicates and use two pointers to find pairs that sum up to a target value.
2. **Iteration:** We iterate through the array with a fixed index `i`.
3. **Two Pointers:** For each `i`, we set a left pointer `j = i + 1` and a right pointer `k = n - 1`.
* If the sum is `0`, we store the triplet and move both pointers inward, while skipping any identical values to avoid duplicate triplets.
* If the sum is `> 0`, we need a smaller sum, so we move the right pointer `k` to the left.
* If the sum is `< 0`, we need a larger sum, so we move the left pointer `j` to the right.



### Dry Run Example

Input: `nums = [-1, 0, 1, 2, -1, -4]`

1. **Sort:** `[-4, -1, -1, 0, 1, 2]`
2. **Loop `i = 0` (val -4):**
* `j = 1 (-1)`, `k = 5 (2)`. Sum = -3 (< 0). `j` moves to 2.
* ... no triplets found for -4.


3. **Loop `i = 1` (val -1):**
* `j = 2 (-1)`, `k = 5 (2)`. Sum = 0. **Match!** Add `[-1, -1, 2]`.
* Skip duplicates for `j` and `k`.
* `j = 3 (0)`, `k = 4 (1)`. Sum = 0. **Match!** Add `[-1, 0, 1]`.


## Complexity Analysis

* **Time Complexity:** $O(n^2)$
* Sorting takes $O(n \log n)$. The loop runs $O(n)$ times, and inside the loop, the two-pointer search takes $O(n)$. Therefore, the overall complexity is $O(n^2)$.


* **Space Complexity:** $O(1)$ (or $O(n)$ depending on the sorting implementation's space usage), as we only store the output triplets and use a few pointers.
