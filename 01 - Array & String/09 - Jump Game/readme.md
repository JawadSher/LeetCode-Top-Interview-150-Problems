# Jump Game

## Problem Statement

You are given an integer array `nums`. You are initially positioned at the array's **first index**, and each element in the array represents your maximum jump length at that position.

Return `true` *if you can reach the last index, or* `false` *otherwise*.

**Problem URL:** [LeetCode - Jump Game](https://leetcode.com/problems/jump-game/description/?envType=study-plan-v2&envId=top-interview-150)

---

## Examples

### Example 1
> **Input:** `nums = [2, 3, 1, 1, 4]`  
> **Output:** `true`  
> **Explanation:** Jump 1 step from index 0 to 1, then 3 steps to the last index.

### Example 2
> **Input:** `nums = [3, 2, 1, 0, 4]`  
> **Output:** `false`  
> **Explanation:** You will always arrive at index 3 no matter what. Its maximum jump length is 0, which makes it impossible to reach the last index.

---

## Deep-Dive Problem Explanation

At first glance, this problem looks like it requires you to find the *exact* sequence of jumps to reach the end. 

### 1. The Core Challenge: "Maximum" Jump Length
The most important phrase in the problem description is **"maximum jump length"**. If `nums[i]` is `3`, it doesn't mean you *must* jump 3 steps. It means you can choose to jump `1`, `2`, or `3` steps. This freedom of choice makes a naive simulation highly complex because every index presents multiple branching choices.

### 2. Why it is Tricky: The Danger of `0`
If an array contains no zeroes (or only positive integers), the answer is **always `true`** because you can always move forward by at least 1 step until you hit the end. 
The entire difficulty of this problem hinges on the number `0`. A `0` acts as a **dead-end trap**. 
* If you land on a `0`, and you have no remaining momentum from a previous jump, you are permanently stuck.
* Your goal is to determine if you can bypass, jump over, or completely avoid these zero-value "traps" to reach the final index.

---

## Solution (C++)

```cpp
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int reach = 0;
        
        for (int i = 0; i < nums.size(); i++) {
            // If the current index is beyond the maximum reachable index, we are stuck.
            if (i > reach) return false; 
            
            // Update the maximum reachable index from the current position
            reach = max(reach, i + nums[i]);
        }
        
        return true;
    }
};

```

---

## How the Solution Works (Greedy Intuition)

Instead of simulating every single choice (which leads to an expensive $O(2^n)$ Backtracking or $O(n^2)$ Dynamic Programming approach), we can solve this in a single pass using a **Greedy Strategy**.

### The "Horizon" Concept

Imagine driving a car through a series of refueling stations. `reach` is your **horizon**—the furthest point you can drive with your current fuel.

* As you drive forward to the next station `i`, you look at how much fuel it offers (`nums[i]`).
* If that station allows you to see *further* down the road than your current horizon (`i + nums[i] > reach`), you update your horizon.
* If you ever reach a point on the road that is *beyond* your horizon (`i > reach`), your car has run out of gas before making it to that station. You are stuck, and it's impossible to proceed.

### Step-by-Step Simulation

Let's trace **Example 2**: `nums = [3, 2, 1, 0, 4]`

| Index (`i`) | Value (`nums[i]`) | Is `i > reach`? | New Reach Calculation: `max(reach, i + nums[i])` | Status / Explanation |
| --- | --- | --- | --- | --- |
| **0** | `3` | `0 > 0` (No) | `max(0, 0 + 3) = 3` | We start at 0. From here, we can reach up to index 3. |
| **1** | `2` | `1 > 3` (No) | `max(3, 1 + 2) = 3` | At index 1, we can jump 2 steps to reach index 3. Horizon stays 3. |
| **2** | `1` | `2 > 3` (No) | `max(3, 2 + 1) = 3` | At index 2, we can jump 1 step to reach index 3. Horizon stays 3. |
| **3** | `0` | `3 > 3` (No) | `max(3, 3 + 0) = 3` | We land on the trap `0`. We can't jump any further from here. Horizon remains 3. |
| **4** | `4` | `4 > 3` (**Yes!**) | *Loop terminated early* | **Returns `false**`. We have reached index 4, but our maximum possible horizon was only 3. We cannot skip over the zero. |

---

## Complexity Analysis

* **Time Complexity:** $O(n)$
We only iterate through the array exactly once. At each element, we perform basic operations (a comparison and a `max` assignment) which take $O(1)$ constant time. Thus, the time scales linearly with the size of the array.
* **Space Complexity:** $O(1)$
We do not allocate any extra arrays, hash maps, or recursion stacks. The state is maintained purely inside a single integer variable (`reach`), utilizing optimal constant auxiliary space.
