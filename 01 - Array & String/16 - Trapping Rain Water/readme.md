# Trapping Rain Water
## Problem Statement

The **Trapping Rain Water** problem asks us to calculate how much rainwater can be trapped between a series of vertical bars (an elevation map) after a storm.

You are given an array of non-negative integers `height`, where each element represents the height of a bar of width `1`. When it rains, water fills up the gaps between these bars. However, water can only be trapped if it is bounded by taller bars on both its **left** and **right** sides. If there isn't a taller bar on both sides, the water will simply spill over the edges.

### Visualizing the Concept with an Example

Let's take a sample array: `height = [0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1]`

* **At index 2 (`height[2] = 0`):** To its left, the highest bar is `1` (at index 1). To its right, the highest bar in the entire array is `3` (at index 7). The limiting factor is the shorter of the two walls, which is `1`. Since the current bar height is `0`, it can hold $\min(1, 3) - 0 = 1$ unit of water.
* **At index 5 (`height[5] = 0`):** To its left, the highest bar so far is `2` (at index 3). To its right, the highest bar is `3` (at index 7). The water level here can rise up to $\min(2, 3) = 2$. Since the current floor is `0`, it traps $2 - 0 = 2$ units of water.
* **At index 7 (`height[7] = 3`):** This is the tallest peak. No water can ever be trapped on top of the highest peak because it cannot be bounded by anything taller on both sides.

By calculating the trapped water for every single index and adding them up, we get the total volume of trapped water. For this example, the total trapped water is `6` units.

---

**Problem Link:** [LeetCode - Trapping Rain Water](https://leetcode.com/problems/trapping-rain-water/description/?envType=study-plan-v2&envId=top-interview-150)

---

## C++ Source Code

```cpp
class Solution {
public:
    int trap(vector<int>& height) {
        int j = 0;
        int n = height.size();
        vector<int> l_max(n), r_max(n);
        l_max[0] = height[0];
        r_max[n-1] = height[n-1];

        // Precompute the maximum height to the left of each index
        for(int i = 1; i < n; i++) l_max[i] = max(l_max[i-1], height[i]);
        
        // Precompute the maximum height to the right of each index
        for(int i = n-2; i >= 0; i--) r_max[i] = max(r_max[i+1], height[i]);   
        
        // Calculate the trapped water at each index
        for(int i = 0; i < n; i++) j += min(l_max[i], r_max[i]) - height[i];

        return j;
    }
};

```

---

## Code Explanation

The logic of this solution relies on **Dynamic Programming / Precomputation**.

Instead of searching for the maximum left and right boundaries for every element over and over again, we scan the array ahead of time to build look-up tables:

1. **`l_max` Array:** Moving from left to right, we keep track of the tallest bar encountered so far. `l_max[i]` stores the highest bar from index `0` up to `i`.
2. **`r_max` Array:** Moving from right to left, we track the tallest bar encountered from the right side. `r_max[i]` stores the highest bar from index `n-1` down to `i`.
3. **Water Calculation Loop:** For any index `i`, the water level is bounded by $\min(l\_max[i], r\_max[i])$. The actual water trapped directly above that bar is that water level minus the height of the bar itself: `min(l_max[i], r_max[i]) - height[i]`.

---

## Dry Run with an Example

Let's trace the solution using a simple array: `height = [4, 2, 0, 3]`

### Step 1: Precompute `l_max` (Left to Right)

* `l_max[0] = height[0] = 4`
* `l_max[1] = max(l_max[0], height[1]) = max(4, 2) = 4`
* `l_max[2] = max(l_max[1], height[2]) = max(4, 0) = 4`
* `l_max[3] = max(l_max[2], height[3]) = max(4, 3) = 4`
* **`l_max` array result:** `[4, 4, 4, 4]`

### Step 2: Precompute `r_max` (Right to Left)

* `r_max[3] = height[3] = 3`
* `r_max[2] = max(r_max[3], height[2]) = max(3, 0) = 3`
* `r_max[1] = max(r_max[2], height[1]) = max(3, 2) = 3`
* `r_max[0] = max(r_max[1], height[0]) = max(3, 4) = 4`
* **`r_max` array result:** `[4, 3, 3, 3]`

### Step 3: Compute Trapped Water (`j`)

We iterate from `i = 0` to `3` using the formula: `j += min(l_max[i], r_max[i]) - height[i]`

* **`i = 0`:** `min(4, 4) - 4 = 4 - 4 = 0` (No water trapped on boundaries)
* **`i = 1`:** `min(4, 3) - 2 = 3 - 2 = 1` (Traps 1 unit of water)
* **`i = 2`:** `min(4, 3) - 0 = 3 - 0 = 3` (Traps 3 units of water)
* **`i = 3`:** `min(4, 3) - 3 = 3 - 3 = 0` (No water trapped on boundaries)

**Total Water (`j`)** = `0 + 1 + 3 + 0 = 4`

---

## Complexity Analysis

* **Time Complexity:** $O(n)$
The algorithm utilizes three separate loops that each run exactly $n$ times. Since these loops are sequential and not nested, the total execution time scales linearly with the size of the input array.
* **Space Complexity:** $O(n)$
The solution allocates two extra arrays (`l_max` and `r_max`), each of size $n$, to store the precomputed maximum heights.
