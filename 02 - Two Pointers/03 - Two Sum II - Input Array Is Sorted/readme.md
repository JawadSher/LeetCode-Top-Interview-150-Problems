# Two Sum II - Input Array Is Sorted

**Link:** [LeetCode - Two Sum II - Input Array Is Sorted](https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/description/?envType=study-plan-v2&envId=top-interview-150)

## Problem Statement

Given a **1-indexed** array of integers `numbers` that is already **sorted in non-decreasing order**, find two numbers such that they add up to a specific `target` number. Let these two numbers be `numbers[index1]` and `numbers[index2]` where `1 <= index1 < index2 <= numbers.length`.

Return *the indices of the two numbers, `index1` and `index2`, added by one as an integer array `[index1, index2]` of length 2.*

The tests are generated such that there is **exactly one solution**. You **may not** use the same element twice.

Your solution must use only constant extra space.

### Examples

**Example 1:**
* **Input:** `numbers = [2,7,11,15]`, `target = 9`
* **Output:** `[1,2]`
* **Explanation:** The sum of 2 and 7 is 9. Therefore, `index1 = 1`, `index2 = 2`. We return `[1, 2]`.

**Example 2:**
* **Input:** `numbers = [2,3,4]`, `target = 6`
* **Output:** `[1,3]`
* **Explanation:** The sum of 2 and 4 is 6. Therefore, `index1 = 1`, `index2 = 3`. We return `[1, 3]`.

**Example 3:**
* **Input:** `numbers = [-1,0]`, `target = -1`
* **Output:** `[1,2]`
* **Explanation:** The sum of -1 and 0 is -1. Therefore, `index1 = 1`, `index2 = 2`. We return `[1, 2]`.

## Solution (C++)

```cpp
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

```

## Detailed Code Explanation

Because the input array is already **sorted**, we can find the target sum efficiently using the **Two Pointers** approach without needing a hash map or nested loops.

1. **Initialization:**
* `indexes`: A vector initialized to `{1, 2}` to store our result.
* `s` (Start Pointer): Points to the first element of the array (`0`).
* `e` (End Pointer): Points to the last element of the array (`numbers.size() - 1`).


2. **The Two-Pointer Mechanics (`while` loop):**
* The loop runs as long as `s < e`.
* Inside the loop, we calculate the sum of the elements at both pointers: `numbers[s] + numbers[e]`.
* **Case 1: Exact Match (`== target`)**
* We have found our two elements. Since the problem asks for a **1-indexed** result, we convert our 0-based indices by setting `indexes[0] = s + 1` and `indexes[1] = e + 1`.
* We immediately return `indexes`.


* **Case 2: Sum is Too Large (`> target`)**
* Because the array is sorted, the only way to reduce our total sum is to move our right boundary inward. We decrement the end pointer (`e--`).


* **Case 3: Sum is Too Small (`< target`)**
* Conversely, to increase our total sum, we must move our left boundary outward. We increment the start pointer (`s++`).


## Dry Run Example

Let's do a dry run with the inputs: **`numbers = [2, 7, 11, 15]`** and **`target = 18`**

* Initial state: `s = 0`, `e = 3`. `indexes = {1, 2}`

**Iteration 1:**

* Check condition: `s < e` (0 < 3) is **True**.
* Current sum: `numbers[0] + numbers[3]` $\rightarrow$ `2 + 15 = 17`.
* Comparison:
* `17 == 18` is False.
* `17 > 18` is False.
* `17 < 18` is **True** $\rightarrow$ Increment `s`. `s` becomes `1`.



**Iteration 2:**

* Check condition: `s < e` (1 < 3) is **True**.
* Current sum: `numbers[1] + numbers[3]` $\rightarrow$ `7 + 15 = 22`.
* Comparison:
* `22 == 18` is False.
* `22 > 18` is **True** $\rightarrow$ Decrement `e`. `e` becomes `2`.



**Iteration 3:**

* Check condition: `s < e` (1 < 2) is **True**.
* Current sum: `numbers[1] + numbers[2]` $\rightarrow$ `7 + 11 = 18`.
* Comparison:
* `18 == 18` is **True**!
* Map to 1-indexed output: `indexes[0] = 1 + 1 = 2`, `indexes[1] = 2 + 1 = 3`.


* **Return Value:** `[2, 3]`

## Complexity Analysis

### Time Complexity: O(n)

* The algorithm uses a single `while` loop with two pointers moving toward each other.
* In each step of the loop, either `s` increases or `e` decreases. This means every element is looked at a maximum of one time.
* **Overall Time Complexity:** **O(n)**, where `n` is the number of elements in `numbers`.

### Space Complexity: O(1)

* The problem specifies that the solution must use only constant extra space.
* Apart from the small integer variables (`s`, `e`) and a fixed-size vector of 2 elements (`indexes`), no dynamic memory allocation or linear-growth data structures are used.
* **Overall Space Complexity:** **O(1)** (Constant space).
