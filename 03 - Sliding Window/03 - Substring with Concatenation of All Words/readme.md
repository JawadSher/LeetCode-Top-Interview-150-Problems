# Substring with Concatenation of All Words

## Problem Statement

You are given a string `s` and an array of strings `words`. All strings in `words` are of the **same length**.

A **concatenated substring** is a substring that contains all the strings from `words` exactly once, in any order, and without any intervening characters.

You need to find and return the starting indices of all such concatenated substrings in `s`.

### Examples

**Example 1:**

* **Input:** `s = "barfoothefoobarman"`, `words = ["foo","bar"]`
* **Output:** `[0,9]`
* **Explanation:**
* Substrings starting at index 0 is `"barfoo"`. It is the concatenation of `["bar", "foo"]`.
* Substrings starting at index 9 is `"foobar"`. It is the concatenation of `["foo", "bar"]`.



**Example 2:**

* **Input:** `s = "wordgoodgoodgoodwordthingword"`, `words = ["word","good","best","word"]`
* **Output:** `[]`
* **Explanation:** There is no substring of length 16 (4 words * 4 chars) that matches the combination perfectly.


#### Problem URL [LeetCode - Substring with Concatenation of All Words](https://leetcode.com/problems/substring-with-concatenation-of-all-words/description/?envType=study-plan-v2&envId=top-interview-150)

## Intuition & Approach

The length of each word is fixed (`w_len`), and the total number of words is `w_size`. This means any valid valid substring must have an exact total length of `window = w_len * w_size`.

### Steps to Solve:

1. **Count Word Frequencies:** Store the count of each word from the `words` array into a frequency map (`freq`).
2. **Scan the String:** Iterate through the string `s` using a loop from index `0` up to `s.length() - window`.
3. **Check Each Window:** For each starting index `i`, create a copy of our frequency map. Check consecutive chunks of length `w_len`.
4. **Validate Words:**
* If a chunk is not in our map, or its available count drops below zero, this starting index `i` is invalid. Break early.
* If all chunks match the frequency map perfectly, add `i` to the result list.



---

## C++ Solution

```cpp
class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        unordered_map<string, int> freq, curr;
        vector<int> indices;
            
        int w_len = words[0].length();
        int w_size = words.size();
        int window = w_len * w_size;

        if ((int)s.length() < window)
            return indices;

        for(auto &word : words) freq[word]++;

        for (int i = 0; i <= (int)s.length() - window; i++){
            curr = freq;
            bool isOk = true;
            for(int j = i; j < i + window; j += w_len){
                string word = s.substr(j, w_len); 
                if(curr.find(word) == curr.end()) {
                    isOk = false;
                    break;
                }

                curr[word]--;

                if (curr[word] < 0) {
                    isOk = false;
                    break;
                }
            }
            
            if(isOk) indices.push_back(i);
        }   

        return indices;
    }
};

```

---

## Line-by-Line Code Explanation

* `unordered_map<string, int> freq, curr;`
Declares `freq` to store target word counts and `curr` to track counts in the current window.
* `int w_len = words[0].length();`
Gets the fixed length of a single word.
* `int w_size = words.size();`
Gets the total number of words.
* `int window = w_len * w_size;`
Calculates the required total length of the concatenated substring.
* `if ((int)s.length() < window) return indices;`
Edge case: If `s` is shorter than the required window size, return an empty vector immediately.
* `for(auto &word : words) freq[word]++;`
Populates the `freq` map with the required counts for each word.
* `for (int i = 0; i <= (int)s.length() - window; i++){`
Loops through every possible starting position `i` where a full window can fit.
* `curr = freq;`
Resets our tracking map `curr` by copying the target counts for the new window check.
* `for(int j = i; j < i + window; j += w_len){`
Iterates through the window in steps of `w_len` to extract each individual word chunk.
* `string word = s.substr(j, w_len);`
Extracts a chunk of size `w_len` starting at index `j`.
* `if(curr.find(word) == curr.end()) { isOk = false; break; }`
If the extracted chunk isn't part of our target words, this window is invalid. Stop checking.
* `curr[word]--;`
Decrements the available count of the found word.
* `if (curr[word] < 0) { isOk = false; break; }`
If we use a word more times than it appears in `words`, the window is invalid. Stop checking.
* `if(isOk) indices.push_back(i);`
If the entire window successfully matches all words, save the starting index `i`.

---

## Dry Run

**Inputs:** `s = "barfooman"`, `words = ["foo","bar"]`

* `w_len = 3`, `w_size = 2`, `window = 6`.
* `freq = {"foo": 1, "bar": 1}`
* **i = 0:** (Sub-window: `"barfoo"`)
* `j = 0`: extracts `"bar"`. `curr["bar"]` becomes 0. Valid.
* `j = 3`: extracts `"foo"`. `curr["foo"]` becomes 0. Valid.
* Loop finishes successfully -> `indices = [0]`.


* **i = 1:** (Sub-window: `"arfoom"`)
* `j = 1`: extracts `"arf"`. Not found in `curr` -> Breaks.


* **i = 3:** (Sub-window: `"fooman"`)
* `j = 3`: extracts `"foo"`. `curr["foo"]` becomes 0. Valid.
* `j = 6`: extracts `"man"`. Not found in `curr` -> Breaks.



**Final Result:** `[0]`

---

## Complexity Analysis

### Time Complexity: $O(N \cdot M \cdot K)$

* $N$ is the length of string `s`.
* $M$ is the number of words (`w_size`).
* $K$ is the length of each word (`w_len`).
* We loop $N - (M \cdot K)$ times. Inside, we do up to $M$ lookups, each extracting a substring of length $K$. Deep copying the map each iteration also takes $O(M)$ time.

### Space Complexity: $O(M \cdot K)$

* The space required for the `freq` and `curr` maps to store $M$ words, where each word has a length of $K$.
