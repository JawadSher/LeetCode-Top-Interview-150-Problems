# Jump Game II

## Problem Description

You are given a **0-indexed** array of integers `nums` of length `n`. You are initially positioned at `nums[0]`.

Each element `nums[i]` represents the maximum length of a forward jump from index `i`. In other words, if you are at `nums[i]`, you can jump to any `nums[i + j]` where:

* `0 <= j <= nums[i]` and
* `i + j < n`

Return *the minimum number of jumps to reach* `nums[n - 1]`. The test cases are generated such that you can always reach the last index.

[Problem Link on LeetCode](https://leetcode.com/problems/jump-game-ii/description/)

---

## Intuition & Approach

The problem is solved optimally using a **Greedy Strategy**. Instead of looking at every single combination of jumps, we can think of the process as moving through successive "windows" of maximum reachability.

We maintain three essential boundaries as we iterate through the array:

1. `reach`: The farthest index we can possibly reach from any of the positions visited so far.
2. `currEnd`: The outer boundary of our current jump window. Once we hit this index, we *must* make another jump to proceed further.
3. `steps`: The total number of jumps taken.

---

## Code Implementation (C++)

```cpp
class Solution {
public:
    int jump(vector<int>& nums) {
        int reach = 0, currEnd = 0, steps = 0;
        int n = nums.size();
        
        // Traverse the array except for the last element
        for(int i = 0; i < n - 1; i++){
            // Update the farthest point we can reach
            reach = max(reach, nums[i] + i);
            
            // If we've reached the end of the current jump window
            if(i == currEnd){
                steps++;         // Make another jump
                currEnd = reach; // Update the boundary to the farthest reachable point
            }
        }
        return steps;
    }
};

```

---

## Code Explanation with Iteration Walkthrough

To understand exactly how the variables update, let's trace the execution step-by-step using a classic example.

### Example: `nums = [2, 3, 1, 1, 4]`

* **Array size (`n`):** 5
* **Loop condition:** Loops from `i = 0` up to `i < 4` (stops before the last element at index 4).
* **Initial State:** `reach = 0`, `currEnd = 0`, `steps = 0`

#### **Iteration 1 (`i = 0`)**

* `nums[0] = 2`
* **Calculate Reach:** `reach = max(0, 2 + 0) = 2`
* **Check Window End:** `i == currEnd` ($0 == 0$) is **True**.
* We have exhausted our options for the initial position. We must jump!
* `steps` increments to `1`.
* `currEnd` updates to `reach` $\rightarrow$ `currEnd = 2`.


* *State at end of iteration:* `reach = 2`, `currEnd = 2`, `steps = 1`

#### **Iteration 2 (`i = 1`)**

* `nums[1] = 3`
* **Calculate Reach:** `reach = max(2, 3 + 1) = 4`
* **Check Window End:** `i == currEnd` ($1 == 2$) is **False**.
* We are still within our current jump window boundary. We just collect the maximum reach potential and move on.


* *State at end of iteration:* `reach = 4`, `currEnd = 2`, `steps = 1`

#### **Iteration 3 (`i = 2`)**

* `nums[2] = 1`
* **Calculate Reach:** `reach = max(4, 1 + 2) = 4`
* **Check Window End:** `i == currEnd` ($2 == 2$) is **True**.
* We reached the end of our first jump's window. We take our second jump using the best potential path discovered (`reach = 4`).
* `steps` increments to `2`.
* `currEnd` updates to `reach` $\rightarrow$ `currEnd = 4`.


* *State at end of iteration:* `reach = 4`, `currEnd = 4`, `steps = 2`

#### **Iteration 4 (`i = 3`)**

* `nums[3] = 1`
* **Calculate Reach:** `reach = max(4, 1 + 3) = 4`
* **Check Window End:** `i == currEnd` ($3 == 4$) is **False**.
* *State at end of iteration:* `reach = 4`, `currEnd = 4`, `steps = 2`

**Loop Ends:** The loop finishes because `i` reaches `n - 1` (4).
**Final Output:** Returns `steps = 2`.

---

## Complexity Analysis

| Complexity | Scale | Reason |
| --- | --- | --- |
| **Time Complexity** | $O(n)$ | We iterate through the array of size $n$ exactly once. |
| **Space Complexity** | $O(1)$ | No extra memory structures are used; the solution only relies on a few integer pointers. |
