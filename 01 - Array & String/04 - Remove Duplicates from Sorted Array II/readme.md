

# Remove Duplicates from Sorted Array II

## Problem Statement

Given an integer array `nums` sorted in **non-decreasing order**, remove some duplicates **in-place** such that each unique element appears **at most twice**. The **relative order** of the elements should be kept the same.

Since it is impossible to change the length of the array in some languages, you must instead have the result be placed in the **first part** of the array `nums`. More formally, if there are `k` elements after removing the duplicates, then the first `k` elements of `nums` should hold the final result. It does not matter what you leave beyond the first `k` elements.

Return `k` *after placing the final result in the first* `k` *slots of* `nums`.

You must do this by **modifying the input array in-place** with $O(1)$ extra memory.

### Problem Link

[LeetCode - Remove Duplicates from Sorted Array II](https://leetcode.com/problems/remove-duplicates-from-sorted-array-ii/description/?envType=study-plan-v2&envId=top-interview-150)

---

## Examples

### Example 1

> **Input:** `nums = [1,1,1,2,2,3]`
> **Output:** `5`, `nums = [1,1,2,2,3,_]`
> **Explanation:** Your function should return $k = 5$, with the first five elements of nums being 1, 1, 2, 2 and 3 respectively. It does not matter what you leave beyond the returned k (hence they are underscores).

### Example 2

> **Input:** `nums = [0,0,1,1,1,1,2,3,3]`
> **Output:** `7`, `nums = [0,0,1,1,2,3,3,_,_]`
> **Explanation:** Your function should return $k = 7$, with the first seven elements of nums being 0, 0, 1, 1, 2, 3 and 3 respectively.

---

## Solution (C++)

```cpp
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int n = nums.size();

        // If the array has 2 or fewer elements, it already satisfies the condition
        if (n <= 2)
            return n;

        int k = 2; // Pointer to place the next valid element

        for (int i = 2; i < n; i++) {
            // Compare current element with the element two positions before the write pointer
            if (nums[i] != nums[k - 2]) {
                nums[k] = nums[i];
                k++;
            }
        }

        return k;
    }
};

```

---

## Step-by-Step Iteration Simulation

Let's trace the algorithm using **Example 1**: `nums = [1, 1, 1, 2, 2, 3]`

* **Initial Setup:** * `n = 6`
* `k = 2` (The first two elements `nums[0]` and `nums[1]` are always allowed)



### Dry Run Table:

| Iteration (`i`) | `nums[i]` | Condition: `nums[i] != nums[k - 2]` | Action | Array State (`nums`) | `k` Value |
| --- | --- | --- | --- | --- | --- |
| *Start* | — | — | — | `[1, 1, 1, 2, 2, 3]` | `2` |
| **`i = 2`** | `1` | `1 != nums[0]` $\rightarrow$ `1 != 1` (**False**) | Skip | `[1, 1, 1, 2, 2, 3]` | `2` |
| **`i = 3`** | `2` | `2 != nums[0]` $\rightarrow$ `2 != 1` (**True**) | `nums[2] = 2`, `k++` | `[1, 1, 2, 2, 2, 3]` | `3` |
| **`i = 4`** | `2` | `2 != nums[1]` $\rightarrow$ `2 != 1` (**True**) | `nums[3] = 2`, `k++` | `[1, 1, 2, 2, 2, 3]` | `4` |
| **`i = 5`** | `3` | `3 != nums[2]` $\rightarrow$ `3 != 2` (**True**) | `nums[4] = 3`, `k++` | `[1, 1, 2, 2, 3, 3]` | `5` |

**Final Return Value:** `k = 5`

**Modified Valid Prefix:** `[1, 1, 2, 2, 3]`

---

## Complexity Analysis

* **Time Complexity:** $O(n)$
The array is traversed exactly once using a single loop running from index `2` to `n - 1`, making the time complexity linear with respect to the size of the input array.
* **Space Complexity:** $O(1)$
The modification is performed completely in-place utilizing only a couple of integer tracking variables (`k`, `i`, `n`), satisfying the constant auxiliary space requirement.
