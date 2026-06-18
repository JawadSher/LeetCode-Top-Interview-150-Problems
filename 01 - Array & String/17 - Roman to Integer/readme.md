# Roman to Integer

## Problem Statement

Roman numerals are represented by seven different symbols: `I`, `V`, `X`, `L`, `C`, `D`, and `M`.

| Symbol | Value |
| --- | --- |
| **I** | 1 |
| **V** | 5 |
| **X** | 10 |
| **L** | 50 |
| **C** | 100 |
| **D** | 500 |
| **M** | 1000 |

Roman numerals are usually written largest to smallest from left to right. However, there are six instances where subtraction is used:

* **I** can be placed before **V** (5) and **X** (10) to make 4 and 9.
* **X** can be placed before **L** (50) and **C** (100) to make 40 and 90.
* **C** can be placed before **D** (500) and **M** (1000) to make 400 and 900.

Given a roman numeral string `s`, convert it to an integer.

#### Problem URL [LeetCode - Roman to Integer](https://leetcode.com/problems/roman-to-integer/?envType=study-plan-v2&envId=top-interview-150)


## Solution (C++)

```cpp
class Solution {
public:
    int romanToInt(string s) {
       unordered_map<char, int> roman = {
            {'I', 1},
            {'V', 5},
            {'X', 10},
            {'L', 50},
            {'C', 100},
            {'D', 500},
            {'M', 1000}
        };

        int num = 0;
        int n = s.length();
        for(int i = 0; i < n; i++){
            if(i+1 < n && roman[s[i]] < roman[s[i+1]]){
                num += roman[s[i+1]] - roman[s[i]];
                i++;
            }else num += roman[s[i]];
        }

        return num;
    }
};

```

---

## Line-by-Line Explanation

* `unordered_map<char, int> roman = { ... };`
Initializes a hash map to map each Roman numeral character to its corresponding integer value for $O(1)$ lookup time.
* `int num = 0;`
Initializes an integer tracking variable `num` to accumulate the total converted value.
* `int n = s.length();`
Stores the length of the input string `s` to avoid calling `length()` repeatedly inside the loop condition.
* `for(int i = 0; i < n; i++) { ... }`
Loops through the string character by character from left to right.
* `if(i+1 < n && roman[s[i]] < roman[s[i+1]])`
Checks two conditions: first, whether a next character exists (`i+1 < n`) to prevent out-of-bounds errors, and second, if the current Roman numeral value is smaller than the next Roman numeral value. This smaller-before-larger pattern flags instances of subtraction (like `IV` or `XL`).
* `num += roman[s[i+1]] - roman[s[i]];`
If the subtraction condition is met, calculates the combined value of the pair (e.g., $5 - 1 = 4$ for `IV`) and adds it directly to `num`.
* `i++;`
Skips the next character in the loop because it was already processed as part of the subtracted pair.
* `else num += roman[s[i]];`
If the current character is greater than or equal to the next one, it follows standard additive rules. The single character value is added to `num`.
* `return num;`
Returns the final calculated integer value after completing the loop traversal.

---

## Dry Run with Examples

### Example 1: `s = "LVIII"`

* **Initial State**: `num = 0`, `n = 5`
* **i = 0**: `s[0] = 'L'` (50). Next is `'V'` (5). $50 \not< 5$, so enter `else`: `num += 50` $\rightarrow$ **50**.
* **i = 1**: `s[1] = 'V'` (5). Next is `'I'` (1). $5 \not< 1$, so enter `else`: `num += 5` $\rightarrow$ **55**.
* **i = 2**: `s[2] = 'I'` (1). Next is `'I'` (1). $1 \not< 1$, so enter `else`: `num += 1` $\rightarrow$ **56**.
* **i = 3**: `s[3] = 'I'` (1). Next is `'I'` (1). $1 \not< 1$, so enter `else`: `num += 1` $\rightarrow$ **57**.
* **i = 4**: `s[4] = 'I'` (1). Next out of bounds. Enter `else`: `num += 1` $\rightarrow$ **58**.
* **Result**: **58**

### Example 2: `s = "MCMXCIV"`

* **Initial State**: `num = 0`, `n = 7`
* **i = 0**: `s[0] = 'M'` (1000). Next `'C'` (100). $1000 \not< 100$. `else`: `num += 1000` $\rightarrow$ **1000**.
* **i = 1**: `s[1] = 'C'` (100). Next `'M'` (1000). $100 < 1000$. `if` matches: `num += (1000 - 100)` $\rightarrow$ `num += 900` $\rightarrow$ **1900**. Increment `i++` (skip next).
* **i = 3**: `s[3] = 'X'` (10). Next `'C'` (100). $10 < 100$. `if` matches: `num += (100 - 10)` $\rightarrow$ `num += 90` $\rightarrow$ **1990**. Increment `i++` (skip next).
* **i = 5**: `s[5] = 'I'` (1). Next `'V'` (5). $1 < 5$. `if` matches: `num += (5 - 1)` $\rightarrow$ `num += 4` $\rightarrow$ **1994**. Increment `i++` (skip next).
* Loop ends.
* **Result**: **1994**

---

## Complexity Analysis

* **Time Complexity:** $O(n)$
The solution iterates through the string of length $n$ exactly once. Hash map lookups take $O(1)$ constant time, which keeps the total time complexity linear relative to the input length.
* **Space Complexity:** $O(1)$
The `unordered_map` holds a fixed set of 7 key-value pairs representing the Roman symbols. Because the memory usage remains constant regardless of the input string length, the auxiliary space complexity is $O(1)$.
