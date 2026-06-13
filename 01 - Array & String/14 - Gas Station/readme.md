# Gas Station

## Problem Description

There are `n` gas stations along a circular route, where the amount of gas at the `i`-th station is `gas[i]`.

You have a car with an unlimited gas tank and it costs `cost[i]` of gas to travel from the `i`-th station to its next `(i + 1)`-th station. You begin the journey with an empty tank at one of the gas stations.

Given two integer arrays `gas` and `cost`, return *the starting gas station's index if you can travel around the circuit once in the clockwise direction, otherwise return `-1*`. If there exists a solution, it is **guaranteed** to be unique.

### Problem Link [LeetCode - Gas Station](https://leetcode.com/problems/gas-station/description/?envType=study-plan-v2&envId=top-interview-150)

---

## Solution Code (C++)

```cpp
class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int tank = 0;
        int index = 0;
        int n = gas.size();
        int i = 0;
        int total = 0;
        
        while (i < n ){
            total += gas[i] - cost[i]; 
            tank  += gas[i] - cost[i];
            if(tank < 0){
                index = i+1;
                tank = 0;
            }
            i++;
        }

        if(total < 0) return -1;

        return index;
    }
};

```

---

## Detailed Code Explanation

The solution utilizes a **Greedy Algorithm** approach based on two crucial observations:

1. **Total Gas vs. Total Cost:** If the sum of all elements in the `gas` array is less than the sum of all elements in the `cost` array ($\sum \text{gas} < \sum \text{cost}$), it is mathematically impossible to complete the circuit regardless of where you start.
2. **The Reset Rule:** If you start at station `A` and find yourself unable to reach station `B` (because your `tank` drops below `0`), then **no station between `A` and `B**` can be a valid starting point either. This allows us to safely reset our starting candidate to `B + 1` and reset our current `tank` to `0`.

### Key Variables:

* `total`: Keeps track of the net balance ($\sum (\text{gas}[i] - \text{cost}[i])$) across the entire trip.
* `tank`: Keeps track of the running gas balance from the current candidate starting `index`.
* `index`: Stores the potential starting gas station index.

---

## Step-by-Step Iteration Example

Let’s trace the algorithm using a standard example.

### Input:

* `gas`  = `[1, 2, 3, 4, 5]`
* `cost` = `[3, 4, 5, 1, 2]`

### Execution Trace:

| Iteration (`i`) | Station Net (`gas[i] - cost[i]`) | `total` balance | `tank` balance | Action / Observation |
| --- | --- | --- | --- | --- |
| **0** | $1 - 3 = -2$ | `-2` | `-2` | `tank < 0` $\rightarrow$ Reset `index = 1`, `tank = 0` |
| **1** | $2 - 4 = -2$ | `-4` | `-2` | `tank < 0` $\rightarrow$ Reset `index = 2`, `tank = 0` |
| **2** | $3 - 5 = -2$ | `-6` | `-2` | `tank < 0` $\rightarrow$ Reset `index = 3`, `tank = 0` |
| **3** | $4 - 1 = +3$ | `-3` | `3` | `tank >= 0` $\rightarrow$ Valid so far. Keep moving. |
| **4** | $5 - 2 = +3$ | `0` | `6` | Loop ends. `tank >= 0`. |

### Final Check:

* After the loop finishes, `total` is `0`.
* Since `total >= 0` (meaning total gas equals total cost), a complete circuit is guaranteed to exist.
* The algorithm returns `index = 3`.

---

## Complexity Analysis

### Time Complexity: $\mathcal{O}(n)$

* The algorithm uses a single `while` loop that traverses the arrays exactly once.
* At each step, it performs basic constant-time $\mathcal{O}(1)$ arithmetic operations and conditional checks.

### Space Complexity: $\mathcal{O}(1)$

* No extra data structures are used.
* Only a few primitive integer variables (`tank`, `index`, `total`, `i`, `n`) are allocated, consuming constant auxiliary memory.
