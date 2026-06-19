# Length of Last Word

## Problem Statement

Given a string `s` consisting of words and spaces, return the length of the **last** word in the string.

A **word** is a maximal substring consisting of non-space characters only.

### Examples

> **Example 1:**
> * **Input:** `s = "Hello World"`
> * **Output:** `5`
> * **Explanation:** The last word is `"World"` with length 5.
> 
> 

> **Example 2:**
> * **Input:** `s = "   fly me   to   the moon  "`
> * **Output:** `4`
> * **Explanation:** The last word is `"moon"` with length 4.
> 
> 

> **Example 3:**
> * **Input:** `s = "luffy is still joyboy"`
> * **Output:** `6`
> * **Explanation:** The last word is `"joyboy"` with length 6.
> 
> 

#### Problem URL [LeetCode - Length of Last Word](https://leetcode.com/problems/length-of-last-word/description/?envType=study-plan-v2&envId=top-interview-150)

## Source Code Solutions

### Approach 1: Optimized Reverse Traversal (Single Pass)

This approach scans the string from right to left, counting characters of the last word directly while ignoring trailing spaces.

```cpp
// Optimized: O(N) Time, O(1) Space
class Solution {
public:
    int lengthOfLastWord(string s) {
        int count = 0;
        
        // Loop backwards from the end of the string
        for(int i = s.length() - 1; i >= 0; i--){
            // If we hit a space and we have already counted letters, the last word is complete
            if(s[i] == ' ' && count > 0) return count;
            // If it's a character, increment our count
            if(s[i] != ' ') count++;
        }
        return count;
    }
};

```

### Approach 2: Un-Optimized Using String Stream (Two Passes)

This approach cleans up the sentence first by extracting all words via an input string stream, re-building a trimmed string, and then traversing backwards.

```cpp
// Un-Optimized: O(N) Time, O(N) Space
class Solution {
public:
    string trimAllExtraSpaces(const string &str) {
        istringstream stream(str);
        string word;
        string result;

        // Extract words and reconstruct the string with single space padding
        while (stream >> word) {
            if (!result.empty()) {
                result += " ";
            }
            result += word;
        }
        return result;
    }

    int lengthOfLastWord(string s) {
        int count = 0;
        string sentence = trimAllExtraSpaces(s);
        
        // Loop backwards through the normalized string
        for(int i = sentence.length() - 1; i >= 0; i--){
            if(sentence[i] == ' ') return count;
            count++;
        }
        return count;
    }
};

```

---

## Line-by-Line Code Explanation (Approach 1)

* `int count = 0;`
Initializes an integer counter tracking the length of the final word found.
* `for(int i = s.length() - 1; i >= 0; i--)`
Starts a loop at the very last index of the string and moves backwards to look for the last word first.
* `if(s[i] == ' ' && count > 0) return count;`
Checks if the current character is a space. If `count > 0`, it means we have already been counting letters of the last word and just hit the boundary space separating it from the next word. We can safely return our answer immediately.
* `if(s[i] != ' ') count++;`
If the character is not a space, it belongs to our target word, so we increment `count`.
* `return count;`
Handles the boundary fallback case if the entire string contains only one word with no leading spaces.

---

## Dry Run / Step-by-Step Walkthrough

Let's trace **Approach 1** using the input `s = "  moon  "`:

1. **Initial State:** `count = 0`, string length is 8. Loop starts at index `i = 7`.
2. `i = 7`: `s[7]` is `' '`. `count > 0` is false. Loop continues.
3. `i = 6`: `s[6]` is `' '`. `count > 0` is false. Loop continues.
4. `i = 5`: `s[5]` is `'n'`. `s[i] != ' '` triggers $\rightarrow$ `count` becomes `1`.
5. `i = 4`: `s[4]` is `'o'`. `s[i] != ' '` triggers $\rightarrow$ `count` becomes `2`.
6. `i = 3`: `s[3]` is `'o'`. `s[i] != ' '` triggers $\rightarrow$ `count` becomes `3`.
7. `i = 2`: `s[2]` is `'m'`. `s[i] != ' '` triggers $\rightarrow$ `count` becomes `4`.
8. `i = 1`: `s[1]` is `' '`. Condition `s[1] == ' ' && count > 0` evaluates to true (`' ' == ' '` and `4 > 0`).
9. **Result:** The function instantly returns `4`.

---

## Comparison: Which One is Better and Why?

**Approach 1 is significantly better.** Here is why:

### 1. Space Efficiency (The Main Decider)

* **Approach 1** operates entirely in-place. It only reads the existing string and stores a single primitive integer variable (`count`). Its auxiliary space complexity is **$O(1)$**.
* **Approach 2** creates an internal string stream buffer and builds an entirely new string copy (`result` and `sentence`) to normalize spaces. If the input string is large, this unnecessarily wastes memory. Its auxiliary space complexity is **$O(N)$**.

### 2. Time Efficiency & Performance

* **Approach 1** only looks at what it absolutely needs to. In a sentence of 1,000 words, it skips trailing spaces, counts the very last word, and immediately hits a return statement. It rarely has to look at the beginning of the string.
* **Approach 2** processes the **entire string** from start to finish via `istringstream` just to remove spaces, copying every single word into memory before it can even begin counting the last word.

---

## Complexity Analysis

| Metric | Approach 1 (Optimized) | Approach 2 (Un-Optimized) |
| --- | --- | --- |
| **Time Complexity** | **$O(N)$** (Worst-case if no trailing spaces; often much faster $O(\text{length of last word})$) | **$O(N)$** (Always parses the entire string twice) |
| **Space Complexity** | **$O(1)$** (Constant space) | **$O(N)$** (Linear space for buffer allocation) |
