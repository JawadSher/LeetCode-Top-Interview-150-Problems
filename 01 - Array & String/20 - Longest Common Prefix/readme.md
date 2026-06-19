# Longest Common Prefix

## Problem Statement

Write a function to find the longest common prefix string amongst an array of strings.

If there is no common prefix, return an empty string `""`.

### Examples

> **Example 1:**
> * **Input:** `strs = ["flower","flow","flight"]`
> * **Output:** `"fl"`
> 
> 

> **Example 2:**
> * **Input:** `strs = ["dog","racecar","car"]`
> * **Output:** `""`
> * **Explanation:** There is no common prefix among the input strings.
> 
> 

#### Problem URL [LeetCode - Longest Common Prefix](https://leetcode.com/problems/longest-common-prefix/description/?envType=study-plan-v2&envId=top-interview-150)


## Source Code Solution

```cpp
class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        // Edge case: If the input array is empty, return an empty string
        if (strs.empty()) return "";
        
        int n = strs[0].length();

        // Vertical scanning: Iterate character by character through the first string
        for(int i = 0; i < n; i++){
            char c = strs[0][i]; // The character to match across all other strings
            
            // Compare character 'c' with the same position 'i' in all other strings
            for (int j = 1; j < strs.size(); j++) {
                // If index 'i' reaches the end of any string OR characters don't match
                if (i == strs[j].length() || strs[j][i] != c) {
                    return strs[0].substr(0, i); // Return the prefix up to index i
                }
            }
        }

        return strs[0]; // If the entire first string matches, it is the common prefix
    }
};

```

---

## Line-by-Line Code Explanation

* `if (strs.empty()) return "";`
Guards against an empty input array to avoid out-of-bounds errors when referencing `strs[0]`.
* `int n = strs[0].length();`
Stores the length of the first string, defining the maximum possible length of a common prefix.
* `for(int i = 0; i < n; i++)`
An outer loop that moves index-by-index (columns) through the characters of the first string. This strategy is known as **Vertical Scanning**.
* `char c = strs[0][i];`
Picks the character at index `i` from the first string to act as our baseline match target.
* `for (int j = 1; j < strs.size(); j++)`
An inner loop that iterates through all the remaining strings (rows) in the array.
* `if (i == strs[j].length() || strs[j][i] != c)`
Checks two termination criteria:
1. `i == strs[j].length()`: The current string `strs[j]` is shorter than `i`, meaning we've run out of characters to match.
2. `strs[j][i] != c`: The character at index `i` in the current string does not match our target character `c`.


* `return strs[0].substr(0, i);`
If a mismatch or out-of-bounds occurs, the common prefix breaks. We return a substring extracted from the first string from index $0$ up to (but excluding) index `i`.
* `return strs[0];`
If the loops finish without hitting a mismatch, it means the entire first string is a prefix for every other string in the array.

---

## Dry Run / Step-by-Step Walkthrough

Let's trace the logic with the input `strs = ["flower", "flow", "flight"]`:

1. **Initial Setup:** `strs[0] = "flower"`, `n = 6`.
2. **Column `i = 0`:**
* Target character `c = 'f'`.
* Check `strs[1]` ("flow"): `strs[1][0]` is `'f'` (Match).
* Check `strs[2]` ("flight"): `strs[2][0]` is `'f'` (Match).


3. **Column `i = 1`:**
* Target character `c = 'l'`.
* Check `strs[1]` ("flow"): `strs[1][1]` is `'l'` (Match).
* Check `strs[2]` ("flight"): `strs[2][1]` is `'l'` (Match).


4. **Column `i = 2`:**
* Target character `c = 'o'`.
* Check `strs[1]` ("flow"): `strs[1][2]` is `'o'` (Match).
* Check `strs[2]` ("flight"): `strs[2][2]` is `'i'`.
* **Mismatch Detected:** `strs[2][2] != 'o'`.


5. **Termination:** The condition triggers and executes `strs[0].substr(0, 2)`.
6. **Result:** Returns `"fl"`.

---

## Complexity Analysis

### Time Complexity: $O(S)$

Where $S$ is the total sum of all characters across all strings in the input array. In the worst-case scenario (e.g., all strings are exactly identical), the algorithm compares every character of every string, leading to a linear running time relative to the total character count.

### Space Complexity: $O(1)$

The vertical scanning method executes entirely in-place. No extra arrays or data structures are created; it only stores primitive variable allocations (`i`, `j`, `n`, `c`), keeping space utilization constant.
