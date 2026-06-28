# Minimum Size Subarray Sum

## Problem Statement

Given an array of positive integers `nums` and a positive integer `target`, find the **minimal length** of a contiguous subarray of which the sum is greater than or equal to `target`. If no such subarray exists, return `0` instead.

### Examples

**Example 1:**

* **Input:** `target = 7`, `nums = [2, 3, 1, 2, 4, 3]`
* **Output:** `2`
* **Explanation:** The subarray `[4, 3]` has the minimal length (`2`) under the problem constraints.

**Example 2:**

* **Input:** `target = 4`, `nums = [1, 4, 4]`
* **Output:** `1`
* **Explanation:** The subarray `[4]` has a sum equal to the target, yielding a minimal length of `1`.

**Example 3:**

* **Input:** `target = 11`, `nums = [1, 1, 1, 1, 1, 1, 1, 1]`
* **Output:** `0`
* **Explanation:** No subarray can sum up to $\ge 11$.

#### Problem URL [LeetCode - Minimum Size Subarray Sum](https://leetcode.com/problems/minimum-size-subarray-sum/description/?envType=study-plan-v2&envId=top-interview-150)

## Brute Force Approach ($O(N^2)$ Time Complexity - TLE)

This approach checks every possible contiguous subarray by fixing a starting index `i` and expanding the ending index `j` until the running sum meets or exceeds the `target`.

```cpp
class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int n = nums.size();
        int minLen = INT_MAX;

        // Loop through each possible starting element
        for(int i = 0; i < n; i++){
            int j = i;
            int sum = 0;

            // Expand the window forward from index i
            while (j < n){
                sum += nums[j];

                // As soon as sum matches or exceeds target, track minimum length
                if(sum >= target){
                    minLen = min(minLen, j - i + 1);
                    break; // Break since further expansion only increases subarray length
                }
                j++;
            }
        }

        return minLen == INT_MAX ? 0 : minLen;
    }
};

```

### Line-by-Line Code Explanation

1. `int n = nums.size(); int minLen = INT_MAX;`: Initializes the size of the array and sets the tracking length to maximum possible value.
2. `for(int i = 0; i < n; i++)`: The outer loop establishes the start index `i` for a potential subarray.
3. `int j = i; int sum = 0;`: For every new starting index `i`, we reset our scanning index `j` and our current running `sum` to zero.
4. `while (j < n)`: The inner loop extends the end index `j` to accumulate subsequent elements into `sum`.
5. `if(sum >= target)`: Tests if the window `[i...j]` satisfies the target sum requirement.
6. `minLen = min(minLen, j - i + 1); break;`: Updates `minLen` if the current subarray window size (`j - i + 1`) is smaller than previous matches. It then breaks early because adding more positive integers would only lengthen the subarray.

### Dry Run Example

Given `target = 7`, `nums = [2, 3, 1, 2]`

* **Iteration `i = 0`:**
* `j = 0`, `sum = 2`
* `j = 1`, `sum = 5`
* `j = 2`, `sum = 6`
* `j = 3`, `sum = 8` ($\ge 7$) $\rightarrow$ `minLen = min(INT_MAX, 3 - 0 + 1) = 4`. Loop breaks.


* **Iteration `i = 1`:**
* `j = 1`, `sum = 3`
* `j = 2`, `sum = 4`
* `j = 3`, `sum = 6` $\rightarrow$ End of array reached, target not met.


* **Final Output:** `minLen = 4`.

### Complexity Analysis

* **Time Complexity:** $O(N^2)$ — In the worst-case scenario (e.g., when the target is never reached), the inner loop runs for every element, mimicking a triangular iteration space matching $\frac{N(N+1)}{2}$ steps. This results in a Time Limit Exceeded (TLE) error on LeetCode.
* **Space Complexity:** $O(1)$ — No auxiliary data structures are used.

## Optimized Approach ($O(N)$ Time Complexity - Sliding Window)

Instead of discarding previous computations and starting from scratch for each index, we keep a dynamic "sliding window" defined by a left pointer `j` and a right pointer `i`.

```cpp
class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int n = nums.size();
        int minLen = INT_MAX;
        int sum = 0;
        int j = 0; // Left pointer of the sliding window

        // Move the right pointer to expand the window
        for(int i = 0; i < n; i++){
            sum += nums[i];

            // Contract the window from the left while the condition holds true
            while (sum >= target){
                minLen = min(minLen, i - j + 1);

                sum -= nums[j];
                j++; // Shrink window
            }
        }

        return minLen == INT_MAX ? 0 : minLen;
    }
};

```

### Line-by-Line Code Explanation

1. `int j = 0;`: Defines the left boundary (`j`) of our sliding window.
2. `for(int i = 0; i < n; i++)`: The loop acts as the right boundary (`i`) of our sliding window, continuously adding elements to `sum`.
3. `while (sum >= target)`: Once our current window sum satisfies the condition, this loop aggressively shrinks the window size from the left side to look for smaller valid combinations.
4. `minLen = min(minLen, i - j + 1);`: Records the minimum size of the current valid window.
5. `sum -= nums[j]; j++;`: Shrinks the window dynamically by subtracting the trailing left element and incrementing `j`.

### Dry Run Example

Given `target = 7`, `nums = [2, 3, 1, 2, 4]`

* **`i = 0`**: `sum = 2`
* **`i = 1`**: `sum = 5`
* **`i = 2`**: `sum = 6`
* **`i = 3`**: `sum = 8`. Condition (`8 >= 7`) met!
* `minLen = min(INT_MAX, 3 - 0 + 1) = 4`
* `sum` becomes `8 - 2 = 6`, `j` increments to `1`. Loop terminates (`6 < 7`).


* **`i = 4`**: `sum = 6 + 4 = 10`. Condition (`10 >= 7`) met!
* `minLen = min(4, 4 - 1 + 1) = 4`
* `sum` becomes `10 - 3 = 7`, `j` increments to `2`. Loop continues (`7 >= 7`)!
* `minLen = min(4, 4 - 2 + 1) = 3`
* `sum` becomes `7 - 1 = 6`, `j` increments to `3`. Loop terminates (`6 < 7`).


* **Final Output:** `minLen = 3`.

### Complexity Analysis

* **Time Complexity:** $O(N)$ — Although there is a nested `while` loop, both pointers `i` and `j` move strictly forward from left to right. Each element is added once and subtracted at most once, bounding the total operations to $2N$.
* **Space Complexity:** $O(1)$ — Space remains constant as operations are done in place.

## Why the Sliding Window Approach is Optimized

The core intuition behind optimizing this problem lies in the following principles:

* **Monotonicity of Positive Sums:** Because all elements in the input array are positive, expanding the window strictly increases the sum, and shrinking the window strictly decreases it.
* **Reusing Computations:** Instead of wiping out the cumulative sum sequence every time a subarray is processed, we keep the previous elements in memory and simply slice off the trailing edge (`nums[j]`).
* **Eliminating Redundant Searches:** Once we discover that a window `[j...i]` satisfies the target, searching for any larger windows ending at `i` (like `[j-1...i]`) is completely pointless because we are strictly seeking the **minimal length**.
* **Linear Execution Structure:** The two pointers crawl continuously forward without backtrack loops, compressing an exponential search path into a highly efficient single pass over the array.
