# Best Time to Buy and Sell Stock II

## Problem Statement

You are given an integer array `prices` where `prices[i]` is the price of a given stock on the $i^{th}$ day.

On each day, you may decide to buy and/or sell the stock. You can only hold **at most one** share of the stock at any time. However, you can buy it and then immediately sell it on the **same day**.

Find and return *the **maximum profit** you can achieve*.

---

## Examples

### Example 1
* **Input:** `prices = [7, 1, 5, 3, 6, 4]`
* **Output:** `7`
* **Explanation:** * Buy on day 2 (price = 1) and sell on day 3 (price = 5), profit = $5 - 1 = 4$.
  * Then buy on day 4 (price = 3) and sell on day 5 (price = 6), profit = $6 - 3 = 3$.
  * Total profit = $4 + 3 = 7$.

### Example 2
* **Input:** `prices = [1, 2, 3, 4, 5]`
* **Output:** `4`
* **Explanation:** * Buy on day 1 (price = 1) and sell on day 5 (price = 5), profit = $5 - 1 = 4$.
  * Total profit = `4`.

### Example 3
* **Input:** `prices = [7, 6, 4, 3, 1]`
* **Output:** `0`
* **Explanation:** There is no way to make a positive profit, so we never buy the stock to achieve a maximum profit of `0`.

---

## Problem URL

[LeetCode - Best Time to Buy and Sell Stock II](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/description/?envType=study-plan-v2&envId=top-interview-150)

---

## Solution: Greedy Approach (Peak-Valley Standard Scan)

### Description
Unlike the first problem where you were restricted to a single transaction, this variation allows you to complete **as many transactions as you like**. 

Because you can buy and sell on the same day, any consecutive upward price trend can be broken down into day-to-day profits. The optimal strategy is to collect profit from **every single upward price movement**. If tomorrow's price is higher than today's price, we simulate buying today and selling tomorrow.

### Code (C++)
```cpp
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int profit = 0;
        int n = prices.size();
        
        for(int i = 0; i < n - 1; i++){
            if(prices[i+1] > prices[i]){
                profit += prices[i+1] - prices[i];
            }
        }

        return profit;
    }
};

```

## How It Works (with Example 1)

Instead of searching for a global minimum and maximum, the code looks exclusively at adjacent pairs. If the stock price goes up from day `i` to day `i+1`, that profit segment is safely added to the running total.

### Step-by-Step State Changes (`prices = [7, 1, 5, 3, 6, 4]`)

Initial state: `profit = 0`

| Day Pointer (`i`) | Price Today (`prices[i]`) | Price Tomorrow (`prices[i+1]`) | Condition (`prices[i+1] > prices[i]`) | Profit Added | Total Profit (`profit`) |
| --- | --- | --- | --- | --- | --- |
| **i = 0** | 7 | 1 | $1 > 7 \rightarrow \mathbf{False}$ | 0 | `0` |
| **i = 1** | 1 | 5 | $5 > 1 \rightarrow \mathbf{True}$ | $5 - 1 = 4$ | $0 + 4 = \mathbf{4}$ |
| **i = 2** | 5 | 3 | $3 > 5 \rightarrow \mathbf{False}$ | 0 | `4` |
| **i = 3** | 3 | 6 | $6 > 3 \rightarrow \mathbf{True}$ | $6 - 3 = 3$ | $4 + 3 = \mathbf{7}$ |
| **i = 4** | 6 | 4 | $4 > 6 \rightarrow \mathbf{False}$ | 0 | `7` |

**Final Output:** `7`

---

## Complexity Analysis

* **Time Complexity:** $O(N)$ — The algorithm loops through the array exactly once up to $n-1$, performing constant time comparisons and additions at each index.
* **Space Complexity:** $O(1)$ — Only a few integer primitives (`profit`, `n`, `i`) are initialized, requiring a constant amount of extra memory.
