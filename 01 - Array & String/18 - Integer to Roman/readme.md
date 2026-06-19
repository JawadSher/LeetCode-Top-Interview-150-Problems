# Integer to Roman

## Problem Statement

Seven different symbols represent Roman numerals with the following values:

| Symbol | Value |
| --- | --- |
| **I** | 1 |
| **V** | 5 |
| **X** | 10 |
| **L** | 50 |
| **C** | 100 |
| **D** | 500 |
| **M** | 1000 |

Roman numerals are usually written largest to smallest from left to right. However, the numeral for four is not `IIII`. Instead, the number four is written as `IV`. Because the one is before the five we subtract it making four. The same principle applies to number nine, which is written as `IX`.

There are six instances where subtraction is used:

* `I` can be placed before `V` (5) and `X` (10) to make **4** and **9**.
* `X` can be placed before `L` (50) and `C` (100) to make **40** and **90**.
* `C` can be placed before `D` (500) and `M` (1000) to make **400** and **900**.

Given an integer `num`, convert it to a Roman numeral string.

### Examples

> **Example 1:**
> * **Input:** `num = 37`
> * **Output:** `"XXXVII"`
> * **Explanation:** `30 = XXX`, `7 = VII`.
> 
> 

> **Example 2:**
> * **Input:** `num = 3949`
> * **Output:** `"MMMCMXLIX"`
> * **Explanation:** `3000 = MMM`, `900 = CM`, `40 = XL`, `9 = IX`.
> 
> 

#### Problem URL [LeetCode - Integer to Roman](https://leetcode.com/problems/integer-to-roman/description/?envType=study-plan-v2&envId=top-interview-150)


## Source Code Solution

```cpp
class Solution {
public:
    string intToRoman(int num) {
        string ROMAN = "";
        // Mapping of Roman numeral values in descending order including subtractive cases
        vector<pair<int, string>> table = {
            {1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"},
            {100, "C"},  {90, "XC"},  {50, "L"},  {40, "XL"},
            {10, "X"},   {9, "IX"},   {5, "V"},   {4, "IV"},
            {1, "I"}
        };

        // Greedy approach: Match the largest possible values first
        for(auto& [value, symbol] : table){
            while (num >= value){
                ROMAN += symbol;  // Append symbol to the resulting string
                num -= value;     // Reduce the number
            }
        }

        return ROMAN;
    }
};

```

---

## Line-by-Line Code Explanation

* `string ROMAN = "";`
Initializes an empty string container that will hold and accumulate our final Roman numeral sequence.
* `vector<pair<int, string>> table = { ... };`
Creates a static look-up array of pairs. It matches integer values with their respective Roman strings. Crucially, it lists them in **descending order** and hardcodes the complex subtractive pairs (like `{900, "CM"}`), removing the need for deep mathematical conditional tracking.
* `for(auto& [value, symbol] : table)`
Uses C++ structured binding to systematically iterate through each value-symbol pair in our table from largest ($1000$) to smallest ($1$).
* `while (num >= value)`
A greedy check loop. As long as our current remaining number is larger than or equal to the active table entry value, we keep processing it.
* `ROMAN += symbol;`
Appends the matching Roman character phrase directly to the right side of our result string sequence.
* `num -= value;`
Subtracts the processed value directly from `num`, shrinking it down before the next check iteration.
* `return ROMAN;`
Once `num` drops down to $0$, the loop ends completely, and the function returns the finalized string representation.

---

## Dry Run / Step-by-Step Walkthrough

Let's trace how the code evaluates `num = 58`:

1. **Initial state:** `num = 58`, `ROMAN = ""`
2. Iterating through `table`:
* Skips values from $1000$ down to $90$ since `58 < value`.
* Reaches `{50, "L"}`:
* Loop condition `58 >= 50` matches.
* `ROMAN` becomes `"L"`.
* `num` becomes $58 - 50 = 8$.


* Reaches values $40$ down to $10$: Skips since `8 < value`.
* Reaches `{5, "V"}`:
* Loop condition `8 >= 5` matches.
* `ROMAN` becomes `"LV"`.
* `num` becomes $8 - 5 = 3$.


* Reaches `{1, "I"}`:
* Loop condition `3 >= 1` matches $\rightarrow$ `ROMAN = "LVI"`, `num = 2`.
* Loop condition `2 >= 1` matches $\rightarrow$ `ROMAN = "LVII"`, `num = 1`.
* Loop condition `1 >= 1` matches $\rightarrow$ `ROMAN = "LVIII"`, `num = 0`.




3. **End state:** Loop finishes because `num == 0`. Returns `"LVIII"`.

---

## Complexity Analysis

### Time Complexity: $O(1)$

Because the input range is strictly bound by LeetCode rules ($1 \le \text{num} \le 3999$), the lookup table size remains fixed ($13$ elements). The `while` loop runs at most a finite, constant number of times overall regardless of input size. Thus, the time complexity simplifies to absolute constant time.

### Space Complexity: $O(1)$

The storage consumed by our `table` mapping sequence vector stays entirely uniform, and the auxiliary resulting string storage length tops out at a maximum constraint ceiling, keeping the storage efficiency metrics bound to a fixed execution footprint.
