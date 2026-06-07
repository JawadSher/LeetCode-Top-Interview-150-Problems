# H-Index

## Problem Statement
Given an array of integers `citations` where `citations[i]` is the number of citations a researcher received for their $i$-th paper, return the researcher's **h-index**.

According to the definition of h-index on Wikipedia: A scientist has an index $h$ if $h$ of their $n$ papers have at least $h$ citations each, and the other $n - h$ papers have no more than $h$ citations each.

If there are multiple possible values for $h$, the **maximum** one is taken as the h-index.

### What the problem actually wants:
You need to find a maximum threshold number $h$ such that there are at least $h$ papers in the array that have a citation count greater than or equal to $h$. 

* **Example:** `citations = [3, 0, 6, 1, 5]`
  * If we choose $h = 3$, there are 3 papers with at least 3 citations (`3`, `6`, and `5`). The remaining papers (`0` and `1`) have fewer than 3 citations. 
  * Thus, the output is `3`.

**Problem Link:** [LeetCode - H-Index](https://leetcode.com/problems/h-index/description/?envType=study-plan-v2&envId=top-interview-150)

---

## Source Code

```cpp
class Solution {
public:
    int hIndex(vector<int>& citations) {
        int n = citations.size();

        for(int h = 1; h <= n; h++){
            int cites = 0;
            for(int j = 0; j < n; j++){
                if(citations[j] >= h) cites++;
            }

            if(cites < h) return h-1;
        }

        return n;
    }
};

```

---

## Code Explanation

This approach uses a **brute-force linear search** to find the correct h-index:

1. **Outer Loop (`h` from 1 to `n`):** We test every possible h-index value starting from 1 up to the total number of papers $n$ (since a researcher cannot have an h-index greater than their total number of published papers).
2. **Inner Loop (`j` from 0 to `n-1`):** For each hypothetical value of `h`, we loop through the entire `citations` array to count how many papers have citations greater than or equal to `h`. This count is stored in the variable `cites`.
3. **Condition Check:** If at any point the number of papers found (`cites`) is strictly less than the target value `h`, it means it's impossible to achieve an h-index of `h`. Since we are checking sequentially upwards, the maximum valid h-index achieved prior to this failure must be `h - 1`.
4. **Fallback Return:** If the loop completes successfully for all values up to `n`, it means all papers have at least `n` citations, so we return `n`.

---

## Dry Run / Iteration Example

Let's trace the execution with **`citations = [3, 0, 6, 1, 5]`** (Total papers $n = 5$).

| Iteration (`h`) | Paper Citations Checked (`citations[j] >= h`) | Count (`cites`) | Condition Checked (`cites < h`) | Action |
| --- | --- | --- | --- | --- |
| **h = 1** | 3 $\ge$ 1 (Yes), 0 $\ge$ 1 (No), 6 $\ge$ 1 (Yes), 1 $\ge$ 1 (Yes), 5 $\ge$ 1 (Yes) | **4** | 4 < 1 (False) | Continue loop |
| **h = 2** | 3 $\ge$ 2 (Yes), 0 $\ge$ 2 (No), 6 $\ge$ 2 (Yes), 1 $\ge$ 2 (No), 5 $\ge$ 2 (Yes) | **3** | 3 < 2 (False) | Continue loop |
| **h = 3** | 3 $\ge$ 3 (Yes), 0 $\ge$ 3 (No), 6 $\ge$ 3 (Yes), 1 $\ge$ 3 (No), 5 $\ge$ 3 (Yes) | **3** | 3 < 3 (False) | Continue loop |
| **h = 4** | 3 $\ge$ 4 (No), 0 $\ge$ 4 (No), 6 $\ge$ 4 (Yes), 1 $\ge$ 4 (No), 5 $\ge$ 4 (Yes) | **2** | 2 < 4 (**True**) | **Stop & Return `h - 1` (4 - 1 = 3)** |

**Final Output Returned:** `3`

---

## Complexity Analysis

### Time Complexity: 

$$O(n^2)$$

* The outer loop runs $n$ times (from $1$ to $n$).
* For each iteration of the outer loop, the inner loop traverses the entire array of size $n$.
* Total operations roughly equal 
$$n \times n = n^2$$


, which leads to a quadratic time complexity.

### Space Complexity: 

$$O(1)$$

* The algorithm uses a constant amount of extra space (`n`, `h`, `cites`, and `j`) regardless of the size of the input array. No dynamic tracking or extra arrays are allocated.
