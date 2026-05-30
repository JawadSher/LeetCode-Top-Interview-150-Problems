# Remove Duplicates from Sorted Array

## 📝 Problem Statement

Given an integer array `nums` sorted in **non-decreasing order**, remove the duplicates **in-place** such that each unique element appears only **once**. The relative order of the elements should be kept the same. Then return the number of unique elements in `nums`.

Consider the number of unique elements of `nums` to be `k`. To get accepted, you need to do the following things:
1. Modify the array `nums` such that the first `k` elements of `nums` contain the unique elements in the order they were initially present in `nums`.
2. Return `k`.

### 🔗 Problem Link
For a full description of the problem and to test your solution, visit [LeetCode - Remove Duplicates from Sorted Array](https://leetcode.com/problems/remove-duplicates-from-sorted-array/?envType=study-plan-v2&envId=top-interview-150).

---

## ⚡ Edge Cases & Examples

When dealing with arrays sorted in non-decreasing order, keep these key scenarios in mind:

### 1. Minimal Array Size (Single Element)
* **Input:** `nums = [1]`
* **Behavior:** The loop shouldn't perform any swaps since there are no duplicates possible. 
* **Output:** `k = 1`, `nums = [1]`

### 2. All Elements Are Identical
* **Input:** `nums = [2, 2, 2, 2]`
* **Behavior:** The algorithm skips every element after the first one because no adjacent element is different.
* **Output:** `k = 1`, `nums = [2, _, _, _]` *(remaining elements do not matter)*

### 3. No Duplicates Present
* **Input:** `nums = [1, 2, 3, 4]`
* **Behavior:** The algorithm continually overwrites elements with themselves as every element is unique.
* **Output:** `k = 4`, `nums = [1, 2, 3, 4]`

---

## 💻 C++ Solution

```cpp
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int k = 1; // Pointer to place the next unique element
        
        for(int i = 1; i < nums.size(); i++){
            // If the current element is different from the previous one, it is unique
            if(nums[i] != nums[i-1]){
                nums[k] = nums[i]; // Move the unique element to the 'k' index
                k++;               // Increment the count of unique elements
            }
        }

        return k;
    }
};

```

---

## 🔍 How the Solution Works (Step-by-Step Execution)

This solution utilizes the **Two-Pointer Technique**.

* Pointer `i` scans through the array to find new unique elements.
* Pointer `k` tracks the position where the next unique element should be written.

### Trace Example: `nums = [0, 0, 1, 1, 1, 2, 2]`

Initial Setup: `k = 1`, `i = 1`

| Step | `i` | `nums[i]` | `nums[i-1]` | Condition (`nums[i] != nums[i-1]`) | Action Taken | Modified Array State | `k` |
| --- | --- | --- | --- | --- | --- | --- | --- |
| **1** | 1 | `0` | `0` | ❌ `0 != 0` (False) | Skip duplicate | `[0, 0, 1, 1, 1, 2, 2]` | 1 |
| **2** | 2 | `1` | `0` | `1 != 0` (True) | `nums[k] = nums[i]`, `k++` | `[0, 1, 1, 1, 1, 2, 2]` | 2 |
| **3** | 3 | `1` | `1` | ❌ `1 != 1` (False) | Skip duplicate | `[0, 1, 1, 1, 1, 2, 2]` | 2 |
| **4** | 4 | `1` | `1` | ❌ `1 != 1` (False) | Skip duplicate | `[0, 1, 1, 1, 1, 2, 2]` | 2 |
| **5** | 5 | `2` | `1` | `2 != 1` (True) | `nums[k] = nums[i]`, `k++` | `[0, 1, 2, 1, 1, 2, 2]` | 3 |
| **6** | 6 | `2` | `2` | ❌ `2 != 2` (False) | Skip duplicate | `[0, 1, 2, 1, 1, 2, 2]` | 3 |

**Final Return Value:** `k = 3`

The first 3 elements of `nums` are now `[0, 1, 2]`, which correctly contains all unique values in order.

---

## 📊 Complexity Analysis

### Time Complexity: $O(N)$

* **Reasoning:** The algorithm passes through the array exactly once with a single `for` loop, where $N$ is the number of elements in `nums`. Each element is evaluated a single time, making the runtime linear.

### Space Complexity: $O(1)$

* **Reasoning:** No additional or auxiliary data structures (like maps or sets) are allocated. All operations and modifications happen strictly **in-place** within the input array, maintaining constant space overhead.
