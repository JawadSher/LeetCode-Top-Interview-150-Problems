# Merge Sorted Array

## Problem Statement

You are given two integer arrays `nums1` and `nums2`, sorted in non-decreasing order, along with two integers `m` and `n`.

* `nums1` has a size of `m + n`
* The first `m` elements of `nums1` are valid elements
* The last `n` elements are `0` and are only placeholders
* `nums2` contains `n` valid elements

Your task is to merge `nums2` into `nums1` such that the final array remains sorted in non-decreasing order.

---

## LeetCode Problem Link

🔗 https://leetcode.com/problems/merge-sorted-array/

---

# Example

## Example 1

### Input

```cpp
nums1 = [1,2,3,0,0,0]
m = 3

nums2 = [2,5,6]
n = 3
```

### Output

```cpp
[1,2,2,3,5,6]
```

### Explanation

We merge:

```cpp
[1,2,3]
```

with

```cpp
[2,5,6]
```

The final sorted array becomes:

```cpp
[1,2,2,3,5,6]
```

---

# Approach

## Key Observation

Since `nums1` already has extra space at the end, we can fill the array from the back instead of the front.

This prevents overwriting important elements.

---

# Idea

We use **Three Pointers**:

| Pointer | Purpose                       |
| ------- | ----------------------------- |
| `i`     | Last valid element in `nums1` |
| `j`     | Last element in `nums2`       |
| `k`     | Last index of merged array    |

---

# Step-by-Step Strategy

1. Compare elements from the end of both arrays
2. Place the larger element at the end (`k`)
3. Move the corresponding pointer backward
4. Continue until one array becomes empty
5. If `nums2` still has elements left, copy them

---

# C++ Solution

```cpp
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int i = m - 1;
        int j = n - 1;
        int k = m + n - 1;

        while (i >= 0 && j >= 0){
            if(nums1[i] > nums2[j]){
                nums1[k] = nums1[i];
                i--;
            }else{
                nums1[k] = nums2[j];
                j--;
            }
            k--;
        }

        while(j >= 0){
            nums1[k] = nums2[j];
            j--;
            k--;
        }
    }
};
```

---

# Dry Run

## Initial Arrays

```cpp
nums1 = [1,2,3,0,0,0]
nums2 = [2,5,6]
```

### Initial Pointer Positions

```cpp
i = 2  -> nums1[i] = 3
j = 2  -> nums2[j] = 6
k = 5
```

---

## Iteration 1

Compare:

```cpp
3 and 6
```

Since `6` is larger:

```cpp
nums1[5] = 6
```

Updated array:

```cpp
[1,2,3,0,0,6]
```

Move pointers:

```cpp
j--
k--
```

---

## Iteration 2

Compare:

```cpp
3 and 5
```

Since `5` is larger:

```cpp
nums1[4] = 5
```

Updated array:

```cpp
[1,2,3,0,5,6]
```

---

## Iteration 3

Compare:

```cpp
3 and 2
```

Since `3` is larger:

```cpp
nums1[3] = 3
```

Updated array:

```cpp
[1,2,3,3,5,6]
```

---

## Iteration 4

Compare:

```cpp
2 and 2
```

Take element from `nums2`:

```cpp
nums1[2] = 2
```

Updated array:

```cpp
[1,2,2,3,5,6]
```

---

# Final Output

```cpp
[1,2,2,3,5,6]
```

---

# Time Complexity

| Operation      | Complexity |
| -------------- | ---------- |
| Merging Arrays | O(m + n)   |

---

# Space Complexity

```cpp
O(1)
```

No extra array is used.

---

# What I Learned

* How to merge two sorted arrays efficiently
* How to use the Two Pointer technique
* Why filling from the back avoids overwriting data
* In-place array manipulation

---

# Related Topics

* Arrays
* Two Pointers
* Sorting
* In-Place Algorithms
