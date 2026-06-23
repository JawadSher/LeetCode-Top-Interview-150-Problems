# Valid Palindrome

**Link:** [LeetCode - Valid Palindrome](https://leetcode.com/problems/valid-palindrome/description/?envType=study-plan-v2&envId=top-interview-150)

## Problem Statement

A phrase is considered a **palindrome** if, after converting all uppercase letters into lowercase letters and removing all non-alphanumeric characters, it reads the same forward and backward. Alphanumeric characters include letters and numbers.

Given a string `s`, return `true` if it is a palindrome, or `false` otherwise.

### Examples

**Example 1:**
* **Input:** `s = "A man, a plan, a canal: Panama"`
* **Output:** `true`
* **Explanation:** After removing non-alphanumeric characters and converting to lowercase, `s` becomes `"amanaplanacanalpanama"`, which reads the same forward and backward.

**Example 2:**
* **Input:** `s = "race a car"`
* **Output:** `false`
* **Explanation:** The filtered string is `"raceacar"`. Reading backward, it is `"racaecar"`, which is not a match.

**Example 3:**
* **Input:** `s = " "`
* **Output:** `true`
* **Explanation:** The filtered string is `""` (empty string). An empty string reads the same forward and backward, so it is a valid palindrome.

---

## Solution (C++)

```cpp
class Solution {
public:
    bool isPalindrome(string s) {
        string word = "";

        for(int i = 0; i < s.length(); i++){
            if(isalnum(s[i])) word += tolower(s[i]);
        }

        int start = 0;
        int end = word.length() -1;
        while(start < end){
            if(word[start] != word[end]) return false;

            start++;
            end--;
        }

        return true;
    }
};
```
## Detailed Code Explanation

The solution relies on string manipulation and the **Two Pointers** technique to verify the palindrome. Here is how the code is structured:

1. **Filtering the String:**
* We initialize an empty string called `word`.
* We iterate through the original string `s` using a `for` loop.
* For every character `s[i]`, we use the built-in C++ function `isalnum()` to check if it is an alphanumeric character (a letter or a number).
* If it is, we convert it to lowercase using `tolower()` and append it to our new string `word`. This cleanly strips out all spaces, punctuation, and uppercase letters.


2. **Checking for Palindrome:**
* We initialize two pointers:
* `start` points to the beginning of our filtered string (`0`).
* `end` points to the last character of our filtered string (`word.length() - 1`).


* We use a `while` loop that runs as long as `start` is less than `end`.
* Inside the loop, we compare the characters at the `start` and `end` indices.
* If `word[start]` does not equal `word[end]`, the string is not a palindrome, and we immediately return `false`.
* If they match, we move the pointers inward (`start++` moves right, `end--` moves left) to check the next pair of characters.
* If the loop finishes without finding any mismatches, we return `true`.



---

## Dry Run Example

Let's do a dry run of the code using the input: **`s = "A b, a"`**

### Step 1: Filtering Phase

* `i = 0`: Character is `'A'`. It is alphanumeric. Convert to lowercase -> `'a'`. Add to `word`. (`word = "a"`)
* `i = 1`: Character is `' '` (space). Not alphanumeric. Ignore.
* `i = 2`: Character is `'b'`. It is alphanumeric. Add to `word`. (`word = "ab"`)
* `i = 3`: Character is `','` (comma). Not alphanumeric. Ignore.
* `i = 4`: Character is `' '` (space). Not alphanumeric. Ignore.
* `i = 5`: Character is `'a'`. It is alphanumeric. Add to `word`. (`word = "aba"`)

After the first loop, our filtered string is **`word = "aba"`**.

### Step 2: Two Pointers Phase

* Initial state: `start = 0`, `end = 2`. Length of `word` is 3.

**Iteration 1:**

* Check condition: `start < end` (0 < 2) is **True**.
* Compare characters: `word[0]` is `'a'`, `word[2]` is `'a'`. They match.
* Update pointers: `start` becomes 1, `end` becomes 1.

**Iteration 2:**

* Check condition: `start < end` (1 < 1) is **False**. The `while` loop terminates.

**Final Return:** The loop exits naturally, meaning no mismatches were found. The function returns **`true`**.

---

## Complexity Analysis

### Time Complexity: O(n)

* **Filtering loop:** We iterate through the original string `s` of length `n` exactly once to create the `word` string. This takes O(n) time.
* **Two-pointer loop:** In the worst-case scenario (a valid palindrome), the two pointers will check each character in the filtered string exactly once (or half the length, approaching from both sides). This takes at most O(n) time.
* **Overall Time Complexity:** O(n) + O(n) = **O(n)**, where `n` is the length of the string `s`.

### Space Complexity: O(n)

* We are creating a new auxiliary string `word` to store the filtered alphanumeric characters.
* In the worst-case scenario (e.g., the string already contains only lowercase alphanumeric characters, with no spaces or punctuation), the new string `word` will be exactly the same size as the input string `s`.
* **Overall Space Complexity:** **O(n)**, where `n` is the length of the string `s`.
