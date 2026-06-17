# Candy

## Problem Statement

There are $n$ children standing in a line. Each child is assigned a rating value given in the integer array `ratings`.

You are giving candies to these children subjected to the following requirements:

1. Each child must have at least **one** candy.
2. Children with a higher rating get more candies than their neighbors.

Return *the minimum number of candies you need to have to distribute the candies to the children.*

**Problem Link:** [LeetCode - Candy](https://leetcode.com/problems/candy/?envType=study-plan-v2&envId=top-interview-150)

---

### Examples

**Example 1:**

* **Input:** `ratings = [1, 0, 2]`
* **Output:** `5`
* **Explanation:** You can allocate to the first, second, and third child with `2, 1, 2` candies respectively. The total minimum candies required is $2 + 1 + 2 = 5$.

**Example 2:**

* **Input:** `ratings = [1, 2, 2]`
* **Output:** `4`
* **Explanation:** You can allocate to the first, second, and third child with `1, 2, 1` candies respectively. The third child gets 1 candy because it satisfies both conditions (equal ratings do not require more candies than neighbors).

---

## Source Code (C++)

```cpp
class Solution {
public:
    int candy(vector<int>& ratings) {
       int n = ratings.size();
       vector<int> c(n, 1);
       int min_candees = 0;

        // Left-to-Right Pass
        for(int i = 1; i < n; i++){
            if(ratings[i] > ratings[i-1]){
                c[i] = c[i-1] + 1;
            }
        }

        // Right-to-Left Pass
        for(int i = n-2; i >= 0; i--){
            if(ratings[i] > ratings[i+1]){
                c[i] = max(c[i], c[i+1] + 1);
            }
        }

        // Sum up total candies
        for(auto const i : c){
            min_candees += i;
        }

        return min_candees;
    }
};

```

---

## Solution Explanation

The problem requires us to satisfy relationships between a child and **both** of their neighbors (left and right). A greedy approach split into two separate 1-dimensional passes allows us to handle these conditions independently:

1. **Initialization:** We start by creating an array `c` of size $n$ initialized to `1`, because every child must receive at least one candy.
2. **Left-to-Right Pass:** We iterate through the array from left to right. If a child has a higher rating than their left neighbor (`ratings[i] > ratings[i-1]`), they must receive more candies than the left neighbor (`c[i] = c[i-1] + 1`). This ensures the left-neighbor condition is fully satisfied.
3. **Right-to-Left Pass:** We iterate backward from right to left. If a child has a higher rating than their right neighbor (`ratings[i] > ratings[i+1]`), we must ensure they have more candies than the right neighbor. To keep both left and right conditions valid, we take the maximum value between their current candy count and the right neighbor's candy count plus one (`max(c[i], c[i+1] + 1)`).
4. **Final Accumulation:** Summing all values in the `c` array gives the absolute minimum candy distribution required.

---

## Iteration Walkthrough

Let's dry-run the code using the input array: `ratings = [1, 3, 4, 5, 2]`

### 1. Initialization

Each child gets `1` candy initially.

* `c = [1, 1, 1, 1, 1]`

### 2. Left-to-Right Pass

We look at each element starting from index `1` to `4`:

* **i = 1:** `ratings[1] (3) > ratings[0] (1)` $\rightarrow$ True. `c[1] = c[0] + 1 = 1 + 1 = 2`
* **i = 2:** `ratings[2] (4) > ratings[1] (3)` $\rightarrow$ True. `c[2] = c[1] + 1 = 2 + 1 = 3`
* **i = 3:** `ratings[3] (5) > ratings[2] (4)` $\rightarrow$ True. `c[3] = c[2] + 1 = 3 + 1 = 4`
* **i = 4:** `ratings[4] (2) > ratings[3] (5)` $\rightarrow$ False. `c[4]` remains `1`.

*State of candies after Left Pass:* `c = [1, 2, 3, 4, 1]`

### 3. Right-to-Left Pass

We look at each element backward starting from index `3` down to `0`:

* **i = 3:** `ratings[3] (5) > ratings[4] (2)` $\rightarrow$ True. `c[3] = max(c[3], c[4] + 1) = max(4, 1 + 1) = 4`
* **i = 2:** `ratings[2] (4) > ratings[3] (5)` $\rightarrow$ False. `c[2]` remains `3`.
* **i = 1:** `ratings[1] (3) > ratings[2] (4)` $\rightarrow$ False. `c[1]` remains `2`.
* **i = 0:** `ratings[0] (1) > ratings[1] (3)` $\rightarrow$ False. `c[0]` remains `1`.

*State of candies after Right Pass:* `c = [1, 2, 3, 4, 1]`

### 4. Sum Up

* `min_candees = 1 + 2 + 3 + 4 + 1 = 11`

---

## Complexity Analysis

### Time Complexity: $O(n)$

* **Left-to-Right pass:** Takes $O(n)$ to traverse the array once.
* **Right-to-Left pass:** Takes $O(n)$ to traverse the array backward once.
* **Summation loop:** Takes $O(n)$ to accumulate the results.
* **Total Time Complexity:** $O(n) + O(n) + O(n) = O(n)$, where $n$ is the number of children.

### Space Complexity: $O(n)$

* An extra array `c` of size $n$ is allocated to store the number of candies assigned to each child. Thus, the auxiliary space complexity is $O(n)$.
