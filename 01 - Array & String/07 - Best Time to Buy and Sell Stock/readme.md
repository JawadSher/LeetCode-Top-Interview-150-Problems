# Best Time to Buy and Sell Stock

## Problem Statement

You are given an array `prices` where `prices[i]` is the price of a given stock on the $i^{th}$ day.

You want to maximize your profit by choosing a **single day** to buy one stock and choosing a **different day in the future** to sell that stock.

Return *the maximum profit you can achieve from this transaction*. If you cannot achieve any profit, return `0`.

---

## Examples

### Example 1
* **Input:** `prices = [7, 1, 5, 3, 6, 4]`
* **Output:** `5`
* **Explanation:** Buy on day 2 (price = 1) and sell on day 5 (price = 6), profit = $6 - 1 = 5$. Note that buying on day 2 and selling on day 1 is not allowed because you must buy before you sell.

### Example 2
* **Input:** `prices = [7, 6, 4, 3, 1]`
* **Output:** `0`
* **Explanation:** In this case, no transactions are done and the max profit = 0.

---

## Problem URL

[LeetCode - Best Time to Buy and Sell Stock](https://leetcode.com/problems/best-time-to-buy-and-sell-stock/description/?envType=study-plan-v2&envId=top-interview-150)

---

## Solutions & Explanations

### Solution 1: Brute Force Approach (Optimized Loops)

#### Description
This approach uses nested loops to find the maximum possible profit. It optimizes slightly by only starting the inner loop if a new lower buying price is found, but it still suffers from quadratic time complexity in worst-case scenarios.

#### Code (C++)
```cpp
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        int profit = 0;
        int buy = INT_MAX;
        
        for(int i = 0; i < n; i++){
            if(prices[i] < buy){
                buy = prices[i];
                for(int j = i; j < n; j++){
                    int n_profit = prices[j] - buy;
                    if(n_profit > profit) profit = n_profit;
                }
            }
        }

        return profit;
    }
};

```

#### How It Works (with Example 1)

1. The outer loop iterates through each day, treating `prices[i]` as a potential **buying day**.
2. To save time, it only looks for a selling day if the current price `prices[i]` is strictly cheaper than any `buy` price it has previously used to start an inner loop (`if(prices[i] < buy)`).
3. Once a new low is found, the inner loop (`j`) scans all *subsequent* days to calculate the profit (`prices[j] - buy`). If that profit is higher than the global `profit`, it updates it.

**Trace Walkthrough (`prices = [7, 1, 5, 3, 6, 4]`):**

* **i = 0 (Price = 7):** `7 < INT_MAX` is true. `buy` becomes 7. The inner loop scans remaining elements, but no element is greater than 7, so `profit` stays `0`.
* **i = 1 (Price = 1):** `1 < 7` is true. `buy` becomes 1. The inner loop scans `[1, 5, 3, 6, 4]`.
* At `j = 2` (Price = 5): `5 - 1 = 4`. `profit = 4`.
* At `j = 4` (Price = 6): `6 - 1 = 5`. `profit = 5`.


* **i = 2 to 5:** None of these prices (`5, 3, 6, 4`) are less than our current `buy` price (`1`), so the inner loop is skipped entirely.

#### Complexity Analysis

* **Time Complexity:** $O(N^2)$ — In the worst-case scenario (e.g., a strictly decreasing array), the outer and inner loops can push the execution time to quadratic limits.
* **Space Complexity:** $O(1)$ — Only a few primitive variables are used, requiring constant extra memory.

---

### Solution 2: Two-Pointer Linear Approach

#### Description

An attempt to solve the problem in a single pass by looking ahead by one element (`i+1`) whenever a lower buying point is found, and checking standard index profit differentials on subsequent days.

#### Code (C++)

```cpp
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        int profit = 0;
        int buy = INT_MAX;
        
        for(int i = 0; i < n; i++){
            if(prices[i] < buy && i+1 < n) {
                buy = prices[i];
                if((prices[i+1] - buy) > profit) profit = prices[i+1] - buy;
            } else {
                if((prices[i] - buy) > profit) profit = prices[i] - buy;
            }
        }

        return profit;
    }
};

```

#### How It Works (with Example 1)

This approach attempts a single-pass solution by dynamically updating the base buy pointer and evaluating sequential pairs or long-term offsets.

1. If the current price `prices[i]` is cheaper than our recorded `buy` price, it updates `buy = prices[i]` and greedily checks if selling on the *very next day* (`prices[i+1]`) yields a higher profit.
2. If the current price is *not* cheaper than `buy`, it assumes we bought at our tracked `buy` price in the past and are checking the profit if we sell *today* (`prices[i] - buy`).

**Trace Walkthrough (`prices = [7, 1, 5, 3, 6, 4]`):**

* **i = 0 (Price = 7):** `7 < INT_MAX`. `buy = 7`. Checks `i+1` (Price = 1). Profit `1 - 7 = -6` (not > 0). `profit` stays `0`.
* **i = 1 (Price = 1):** `1 < 7`. `buy = 1`. Checks `i+1` (Price = 5). Profit `5 - 1 = 4`. `profit = 4`.
* **i = 2 (Price = 5):** `5 < 1` is false. Runs `else` block: Profit `5 - 1 = 4` (not > 4). `profit` stays `4`.
* **i = 3 (Price = 3):** `3 < 1` is false. Runs `else` block: Profit `3 - 1 = 2` (not > 4). `profit` stays `4`.
* **i = 4 (Price = 6):** `6 < 1` is false. Runs `else` block: Profit `6 - 1 = 5`. `profit = 5`.
* **i = 5 (Price = 4):** `4 < 1` is false. Runs `else` block: Profit `4 - 1 = 3` (not > 5). `profit` stays `5`.

#### Complexity Analysis

* **Time Complexity:** $O(N)$ — The array is traversed exactly once.
* **Space Complexity:** $O(1)$ — Constant space complexity.

---

### Solution 3: Standard Sliding Window / Greedy (Recommended)

#### Description

This is the cleanest and most optimal way to solve the problem. We maintain a running minimum price (`mini`) seen so far. As we iterate through the list, we calculate the potential profit if we sold at the current day's price. We then update the global maximum profit and the minimum buying price for subsequent iterations.

#### Code (C++)

```cpp
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int mini = prices[0];
        int profit = 0;
        
        for(int i = 1; i < prices.size(); i++){
            int diff = prices[i] - mini;
            profit = max(profit, diff);
            mini = min(mini, prices[i]);
        }

        return profit;
    }
};

```

#### How It Works (with Example 1)

Instead of worrying about forward-looking indexes or separate nested track indices, this mimics real life:

1. You walk through the days chronologically starting from day 2 (`i = 1`).
2. You always keep track of the absolute lowest price you've seen so far (`mini`).
3. For every day you visit, you ask: *"If I bought at my lowest historic price (`mini`) and sold today (`prices[i]`), how much money would I make?"* (`diff = prices[i] - mini`).
4. If that amount is the best you've seen, remember it (`profit`). Then update your history if today's price is a new low.

**Step-by-Step State Changes (`prices = [7, 1, 5, 3, 6, 4]`):**
Initial state: `mini = 7`, `profit = 0`

| Day (`i`) | Price | Potential Profit (`prices[i] - mini`) | Max Profit (`profit`) | Lowest Price Seen (`mini`) |
| --- | --- | --- | --- | --- |
| **Start** | - | - | `0` | `7` |
| **i = 1** | 1 | $1 - 7 = -6$ | `0` | $\min(7, 1) = \mathbf{1}$ |
| **i = 2** | 5 | $5 - 1 = 4$ | $\max(0, 4) = \mathbf{4}$ | $\min(1, 5) = `1`$ |
| **i = 3** | 3 | $3 - 1 = 2$ | $\max(4, 2) = `4`$ | $\min(1, 3) = `1`$ |
| **i = 4** | 6 | $6 - 1 = 5$ | $\max(4, 5) = \mathbf{5}$ | $\min(1, 6) = `1`$ |
| **i = 5** | 4 | $4 - 1 = 3$ | $\max(5, 3) = `5`$ | $\min(1, 4) = `1`$ |

#### Complexity Analysis

* **Time Complexity:** $O(N)$ — Linear scan through the array of prices exactly once.
* **Space Complexity:** $O(1)$ — Uses no extra space beyond a couple of tracking variables.
