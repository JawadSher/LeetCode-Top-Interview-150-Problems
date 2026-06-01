# Majority Element

## Problem Statement
Given an array `nums` of size `n`, return *the majority element*.

The majority element is the element that appears more than $\lfloor n / 2 \rfloor$ times. You may assume that the majority element always exists in the array.

**Problem URL:** [LeetCode - Majority Element](https://leetcode.com/problems/majority-element/?envType=study-plan-v2&envId=top-interview-150)


## Edge Cases & Examples

### Example 1: Standard Majority
* **Input:** `nums = [3, 2, 3]`
* **Output:** `3`
* **Explanation:** The size of the array is 3. $\lfloor 3 / 2 \rfloor = 1$. The element `3` appears 2 times, which is greater than 1.

### Example 2: Mixed Dispersed Majority
* **Input:** `nums = [2, 2, 1, 1, 1, 2, 2]`
* **Output:** `2`
* **Explanation:** The size of the array is 7. $\lfloor 7 / 2 \rfloor = 3$. The element `2` appears 4 times, which is greater than 3.

### Edge Case: Single Element Array
* **Input:** `nums = [1]`
* **Output:** `1`
* **Explanation:** The only element is automatically the majority.

---

## Solution (C++)

This solution implements **Boyer-Moore Voting Algorithm**, which finds the majority element in linear time and constant space.

```cpp
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int n = nums.size();
        int k = -1; // Stores the current candidate
        int c = 0;  // Count tracker

        for(int i = 0; i < n; i++){
            if(c == 0) k = nums[i];

            if(k == nums[i]) c++;
            else c--;
        }

        return k;
    }
};

```

---

## How It Works (Dry Run)

The Boyer-Moore Voting Algorithm works on a simple principle: if we replace each occurrence of the majority element with $+1$ and all other elements with $-1$, the overall sum will safely be greater than $0$.

We maintain a `candidate` (`k`) and a `counter` (`c`). As we iterate through the array:

1. If the counter reaches `0`, we pick the current element as our new candidate.
2. If the current element matches our candidate, we increment the counter.
3. If it doesn't match, we decrement the counter (effectively pairing it up with a non-matching element to cancel each other out).

### Step-by-Step Dry Run

Let's trace the algorithm with `nums = [2, 2, 1, 1, 1, 2, 2]`:

| Index (`i`) | Element | Condition | Candidate (`k`) | Counter (`c`) | Reason / Action |
| --- | --- | --- | --- | --- | --- |
| *Before loop* | — | — | `-1` | `0` | Initialization |
| `0` | `2` | `c == 0` | `2` | `1` | `c` was 0, so `k` becomes 2. Match found, `c++`. |
| `1` | `2` | `k == nums[i]` | `2` | `2` | Match found, `c++`. |
| `2` | `1` | `k != nums[i]` | `2` | `1` | Mismatch, `c--`. |
| `3` | `1` | `k != nums[i]` | `2` | `0` | Mismatch, `c--`. |
| `4` | `1` | `c == 0` | `1` | `1` | `c` was 0, so `k` resets to 1. Match found, `c++`. |
| `5` | `2` | `k != nums[i]` | `1` | `0` | Mismatch, `c--`. |
| `6` | `2` | `c == 0` | `2` | `1` | `c` was 0, so `k` resets to 2. Match found, `c++`. |

**Final Returned Value:** `2`

---

## Complexity Analysis

* **Time Complexity:** $\mathcal{O}(n)$
We only iterate through the array exactly once, making the time complexity linear with respect to the size of the input array.
* **Space Complexity:** $\mathcal{O}(1)$
The algorithm only utilizes two integer variables (`k` and `c`) to track the state, ensuring constant extra memory allocation regardless of input size.
