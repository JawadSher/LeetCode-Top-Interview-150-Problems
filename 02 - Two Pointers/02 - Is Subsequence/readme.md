# Is Subsequence

**Link:** [LeetCode - Is Subsequence](https://leetcode.com/problems/is-subsequence/description/?envType=study-plan-v2&envId=top-interview-150)

## Problem Statement

Given two strings `s` and `t`, return `true` if `s` is a **subsequence** of `t`, or `false` otherwise.

A **subsequence** of a string is a new string that is formed from the original string by deleting some (can be none) of the characters without disturbing the relative positions of the remaining characters. For example, `"ace"` is a subsequence of `"abcde"`, while `"aec"` is not.

### Examples

**Example 1:**
* **Input:** `s = "abc"`, `t = "ahbgdc"`
* **Output:** `true`
* **Explanation:** All characters of `s` (`'a'`, `'b'`, `'c'`) appear in `t` in the exact same relative order.

**Example 2:**
* **Input:** `s = "axc"`, `t = "ahbgdc"`
* **Output:** `false`
* **Explanation:** While `'a'` and `'c'` are present in `t`, the character `'x'` is missing. Therefore, `s` cannot be formed from `t`.

**Example 3:**
* **Input:** `s = ""`, `t = "ahbgdc"`
* **Output:** `true`
* **Explanation:** An empty string is mathematically considered a subsequence of any string.

## Solution (C++)

```cpp
class Solution {
public:
    bool isSubsequence(string s, string t) {
        if(s.length() == 0) return true;

        int j = 0;
        for(int i = 0; i < t.length(); i++){
            if(t[i] == s[j]) j++;

            if(j == s.length()) return true;
        }

        return false;
    }
};
```

## Detailed Code Explanation

This solution utilizes the **Two Pointers** technique to track our progress through both strings simultaneously.

1. **Handling Edge Cases:**
* The code first checks if the string `s` is empty (`s.length() == 0`). If it is, it immediately returns `true`, as an empty string is always a valid subsequence.


2. **Pointer Initialization:**
* A pointer `j` is initialized to `0`. This pointer tracks our current position in the target subsequence `s`.
* The `for` loop uses a counter `i` to iterate through the main string `t`.


3. **Character Matching:**
* As we iterate through `t`, we compare the current character `t[i]` with the current character we need from `s` (`s[j]`).
* If there is a match (`t[i] == s[j]`), we increment `j`. This means we have successfully found the current character of `s` inside `t`, and we can now move on to look for the *next* character of `s`.


4. **Early Exit Condition:**
* Inside the loop, after potentially incrementing `j`, we check if `j` equals the total length of `s` (`j == s.length()`).
* If this is true, it means we have successfully found all characters of `s` within `t` in the correct order. We can immediately return `true` without checking the rest of `t`.


5. **Final Fallback:**
* If the `for` loop finishes iterating through all of `t` and we haven't returned `true` yet, it means we couldn't find all characters of `s` in order. The function then returns `false`.


## Dry Run Example

Let's do a dry run of the code using the inputs: **`s = "abc"`** and **`t = "ahbgdc"`**

* Initial state: `j = 0` (pointing to `'a'` in `s`). `s.length()` is 3.

**Iteration 1 (`i = 0`):**

* `t[0]` is `'a'`. `s[0]` is `'a'`.
* They match! Increment `j`. (`j` becomes 1).
* Check condition: `j` (1) != `s.length()` (3). Continue.

**Iteration 2 (`i = 1`):**

* `t[1]` is `'h'`. `s[1]` is `'b'`.
* No match. Continue.

**Iteration 3 (`i = 2`):**

* `t[2]` is `'b'`. `s[1]` is `'b'`.
* They match! Increment `j`. (`j` becomes 2).
* Check condition: `j` (2) != `s.length()` (3). Continue.

**Iteration 4 (`i = 3`):**

* `t[3]` is `'g'`. `s[2]` is `'c'`.
* No match. Continue.

**Iteration 5 (`i = 4`):**

* `t[4]` is `'d'`. `s[2]` is `'c'`.
* No match. Continue.

**Iteration 6 (`i = 5`):**

* `t[5]` is `'c'`. `s[2]` is `'c'`.
* They match! Increment `j`. (`j` becomes 3).
* Check condition: `j` (3) == `s.length()` (3).
* **Target reached! Return `true`.**

---

## Complexity Analysis

### Time Complexity: O(n)

* The algorithm iterates through the string `t` exactly once using the `for` loop. The number of operations scales linearly with the length of `t`. Let `n` be the length of `t`.
* **Overall Time Complexity:** **O(n)**.

### Space Complexity: O(1)

* The algorithm only uses a couple of integer variables (`i` and `j`) to act as pointers. No new arrays or strings are created, regardless of the input sizes.
* **Overall Space Complexity:** **O(1)** (Constant space).
