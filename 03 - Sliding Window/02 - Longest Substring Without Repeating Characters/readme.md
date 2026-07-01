# Longest Substring Without Repeating Characters

## Problem Statement

Given a string `s`, find the length of the **longest substring** without repeating characters.

A **substring** is a contiguous non-empty sequence of characters within a string.

### Examples

**Example 1:**

* **Input:** `s = "abcabcbb"`
* **Output:** `3`
* **Explanation:** The answer is `"abc"`, with the length of 3.

**Example 2:**

* **Input:** `s = "bbbbb"`
* **Output:** `1`
* **Explanation:** The answer is `"b"`, with the length of 1.

**Example 3:**

* **Input:** `s = "pwwkew"`
* **Output:** `3`
* **Explanation:** The answer is `"wke"`, with the length of 3. Note that the answer must be a substring, `"pwke"` is a subsequence and not a substring.

#### Problem URL [LeetCode - Longest Substring Without Repeating Characters](https://leetcode.com/problems/longest-substring-without-repeating-characters/description/?envType=study-plan-v2&envId=top-interview-150)

## How to Build Intuition & Approach

When faced with a problem that requires finding a contiguous segment (substring) satisfying a certain condition (no repeating characters), a few core concepts should come to mind:

1. **Brute Force (Checking all substrings):** You could generate every possible substring, check if it contains duplicates, and track the maximum length. This takes $O(n^3)$ or $O(n^2)$ time, which is too slow for large inputs.
2. **Dynamic Substring Maintenance (The Substring Reconstruction Approach):** As you scan through the string character by character, you can maintain the current valid substring. If you encounter a duplicate character that is already inside your current tracking substring, you must discard the prefix of your tracking substring up to (and including) that duplicate character to make the remaining part unique again.
3. **Sliding Window Optimization:** Instead of explicitly slicing and modifying string objects, you can track the boundaries of your substring using two pointers: a left pointer `j` and a right pointer `i`. As the right pointer expands the window, if a duplicate is found, the left pointer `j` shifts forward to shrink the window, instantly excluding the repeating element. Using a hash map to remember the **last seen index** of each character allows the left pointer to jump directly to the correct position without a linear scan.

## Approach 1: Unoptimized Substring Manipulation

### Code Implementation

```cpp
// O(n)^2 - Unoptimized Solution
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        if(s.length() == 0) return 0;
        if(s.length() == 1) return 1;

        string subStr = "";
        int len = 0;
        for(int i = 0; i < s.length(); i++){
            int j = 0;

            while(j < subStr.length()){
                if(subStr[j] == s[i]) {
                    subStr = subStr.substr(j + 1);
                    break;
                }

                j++;
            }

            subStr += s[i];

            len = max<int>(len, subStr.length());
        }

        return len;
    }
};

```

### Line-by-Line Explanation

* **`if(s.length() == 0) return 0; if(s.length() == 1) return 1;`**: Base case optimizations. If the string is empty or has a single character, its longest unique substring length is trivially `0` or `1`.
* **`string subStr = ""; int len = 0;`**: Initializes an empty string `subStr` to accumulate the current unique characters and an integer `len` to hold the maximum length found so far.
* **`for(int i = 0; i < s.length(); i++)`**: Iterates through each character of the input string `s`.
* **`int j = 0; while(j < subStr.length())`**: A nested loop that scans through our currently tracked `subStr` to check if the incoming character `s[i]` already exists within it.
* **`if(subStr[j] == s[i]) { subStr = subStr.substr(j + 1); break; }`**: If a duplicate is found at index `j` of `subStr`, we drop everything from the beginning up to index `j` by taking a substring from `j + 1` to the end. We break early since uniqueness is restored.
* **`subStr += s[i];`**: Appends the current character `s[i]` to the now-cleared `subStr`.
* **`len = max<int>(len, subStr.length());`**: Updates the maximum length tracking variable if the current window length is larger.
* **`return len;`**: Returns the maximum length computed after scanning the entire string.

### Dry Run

Let's dry run with `s = "pwwkew"`:

1. `i = 0`, `s[0] = 'p'`: `subStr` is empty. No loop match. `subStr` becomes `"p"`. `len = max(0, 1) = 1`.
2. `i = 1`, `s[1] = 'w'`: `subStr = "p"`. No match. `subStr` becomes `"pw"`. `len = max(1, 2) = 2`.
3. `i = 2`, `s[2] = 'w'`: `subStr = "pw"`. Loop finds match at `j = 1` (`subStr[1] == 'w'`). `subStr` gets sliced from index $1+1$, becoming `""`. Loop breaks. `s[2]` appended $\rightarrow$ `subStr = "w"`. `len = max(2, 1) = 2`.
4. `i = 3`, `s[3] = 'k'`: `subStr = "w"`. No match. `subStr` becomes `"wk"`. `len = max(2, 2) = 2`.
5. `i = 4`, `s[4] = 'e'`: `subStr = "wk"`. No match. `subStr` becomes `"wke"`. `len = max(2, 3) = 3`.
6. `i = 5`, `s[5] = 'w'`: `subStr = "wke"`. Match found at `j = 0`. `subStr` sliced from index $0+1$, becoming `"ke"`. `s[5]` appended $\rightarrow$ `subStr = "kew"`. `len = max(3, 3) = 3`.

**Final Output:** `3`

### Complexity Analysis

* **Time Complexity:** $O(n^2)$ — For each character in the string, we potentially iterate through the length of `subStr` (up to size $n$). Additionally, string slicing via `.substr()` takes linear time proportional to the length of the substring.
* **Space Complexity:** $O(n)$ — Additional memory used to store the dynamic `subStr` string object.

---

## Approach 2: Optimized Sliding Window (Two Pointers + Hash Map)

### Code Implementation

```cpp
// O(N) Optimized Solution
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        if(s.length() == 0) return 0;
        if(s.length() == 1) return 1;

        int j = 0;
        unordered_map<char, int> last;
        int len = 0;

        for(int i = 0; i < s.length(); i++){
            if(last.find(s[i]) != last.end()){
                j = max(j, last[s[i]] + 1);
            }

            last[s[i]] = i;
            len = max<int>(len, i - j + 1);
        }

        return len;
    }
};

```

### Line-by-Line Explanation

* **`int j = 0;`**: Declares the left boundary pointer `j` of our sliding window.
* **`unordered_map<char, int> last;`**: A hash map used to map each character to its most recent index location in the string.
* **`for(int i = 0; i < s.length(); i++)`**: The right boundary pointer `i` expands the sliding window linearly across the string.
* **`if(last.find(s[i]) != last.end())`**: Checks if the current character `s[i]` has been encountered before.
* **`j = max(j, last[s[i]] + 1);`**: If the character is a duplicate, we must move the left boundary `j` right past the old occurrence of this character. We use `max` to ensure `j` never moves backward (in case the last seen instance of the character is outside/before our current window).
* **`last[s[i]] = i;`**: Updates (or inserts) the latest index location of character `s[i]` to be `i`.
* **`len = max<int>(len, i - j + 1);`**: Computes the size of the current window (`i - j + 1`) and stores the maximum window size observed.

### Dry Run

Let's dry run with `s = "abcabcbb"`:

1. `i = 0`, `s[0] = 'a'`: Not in map. `last['a'] = 0`. Window size = $0 - 0 + 1 = 1$. `len = 1`.
2. `i = 1`, `s[1] = 'b'`: Not in map. `last['b'] = 1`. Window size = $1 - 0 + 1 = 2$. `len = 2`.
3. `i = 2`, `s[2] = 'c'`: Not in map. `last['c'] = 2`. Window size = $2 - 0 + 1 = 3$. `len = 3`.
4. `i = 3`, `s[3] = 'a'`: Found 'a' at index `0`. `j = max(0, 0 + 1) = 1`. Update `last['a'] = 3`. Window size = $3 - 1 + 1 = 3$. `len = 3`.
5. `i = 4`, `s[4] = 'b'`: Found 'b' at index `1`. `j = max(1, 1 + 1) = 2`. Update `last['b'] = 4`. Window size = $4 - 2 + 1 = 3$. `len = 3`.
6. `i = 5`, `s[5] = 'c'`: Found 'c' at index `2`. `j = max(2, 2 + 1) = 3`. Update `last['c'] = 5`. Window size = $5 - 3 + 1 = 3$. `len = 3`.
7. `i = 6`, `s[6] = 'b'`: Found 'b' at index `4`. `j = max(3, 4 + 1) = 5`. Update `last['b'] = 6`. Window size = $6 - 5 + 1 = 2$. `len = 3`.
8. `i = 7`, `s[7] = 'b'`: Found 'b' at index `6`. `j = max(5, 6 + 1) = 7`. Update `last['b'] = 7`. Window size = $7 - 7 + 1 = 1$. `len = 3`.

**Final Output:** `3`

### Complexity Analysis

* **Time Complexity:** $O(n)$ — We process each character exactly once with the right pointer `i`. Map lookups and insertions take $O(1)$ average time complexity.
* **Space Complexity:** $O(\min(m, n))$ — The space required for the hash map depends on the size of the string $n$ and the size of the alphabet/character set $m$.

---

## Comparison Table

| Strategy | Time Complexity | Space Complexity | Performance & Scalability |
| --- | --- | --- | --- |
| **Approach 1: Unoptimized** | $O(n^2)$ | $O(n)$ | Slow. String instantiation and sub-scanning inside the loop cause high overhead for large datasets. |
| **Approach 2: Sliding Window** | $O(n)$ | $O(\min(m, n))$ | Highly optimized. Processes strings in a single pass using continuous memory tracking pointers. |
