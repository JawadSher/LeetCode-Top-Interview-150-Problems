# Reverse Words in a String

## 📝 Problem Description

Given an input string `s`, reverse the order of the **words**.

A **word** is defined as a sequence of non-space characters. The words in `s` will be separated by at least one space.

Return *a string of the words in reverse order concatenated by a single space.*

**Note** that `s` may contain leading or trailing spaces or multiple spaces between two words. The returned string should only have a single space separating the words. Do not include any extra spaces.

🔗 **Problem Link:** [LeetCode - Reverse Words in a String](https://leetcode.com/problems/reverse-words-in-a-string/description/?envType=study-plan-v2&envId=top-interview-150)

### Examples

**Example 1:**

> **Input:** `s = "the sky is blue"`
> **Output:** `"blue is sky the"`

**Example 2:**

> **Input:** `s = "  hello world  "`
> **Output:** `"world hello"`
> **Explanation:** Your reversed string should not contain leading or trailing spaces.

**Example 3:**

> **Input:** `s = "a good   example"`
> **Output:** `"example good a"`
> **Explanation:** You need to reduce multiple spaces between two words to a single space in the reversed string.

---

## 💡 Intuition & Approach

The problem requires reversing the sequence of words while handling arbitrary spacing gracefully.

Using C++'s `std::stringstream` is an elegant way to solve this:

1. **Tokenization:** `stringstream` automatically handles multiple spaces and skips leading/trailing whitespaces, extracting one clean word at a time via the stream extraction operator (`>>`).
2. **Reversal on the Fly:** Instead of pushing words into a vector and reversing it later, we can prepend each new word to the front of our result string (`sentence = word + ' ' + sentence`).
3. **Boundary Condition:** To avoid a trailing or leading space on the final string, we only add the space character if the result string is not empty.

---

## 💻 Code Implementation

```cpp
class Solution {
public:
    string reverseWords(string s) {
        string sentence = "";
        stringstream ss(s);
        string word;

        // Extract words while automatically ignoring extra spaces
        while (ss >> word) {
            if (sentence.empty()) {
                sentence = word;
            } else {
                // Prepend the new word to reverse the sequence order
                sentence = word + ' ' + sentence;
            }
        }

        return sentence;
    }
};

```

### 🔍 Source Explanation

The provided solution addresses the **Reverse Words in a String** problem by leveraging C++'s standard input/output stream library, specifically `std::stringstream`.

In C++, `std::stringstream` associates a string object with a stream, allowing you to read from or write to the string as if it were a standard stream (like `cin` or `cout`).

### Why `stringstream` works perfectly here:

* **Automatic Whitespace Skipping:** The stream extraction operator (`>>`) inherently skips leading, trailing, and consecutive whitespace characters. It extracts sequences of non-space characters one at a time.
* **Tokenization:** It breaks the long string down into isolated "word" tokens seamlessly, saving us from writing manual loops to track index positions or handle multiple spaces.

---

## 💻 Code Breakdown

Let's look at the logic step-by-step:

1. **Initialization:**
```cpp
string sentence = "";
stringstream ss(s);
string word;

```


We initialize an empty result string (`sentence`), load our input string `s` into the stream object `ss`, and create a temporary buffer string (`word`) to hold each token during iteration.
2. **The Stream Loop & Reversal:**
```cpp
while (ss >> word) {
    if (sentence.empty()) {
        sentence = word;
    } else {
        sentence = word + ' ' + sentence;
    }
}

```


* `ss >> word` evaluates to `true` as long as there are words left in the stream to extract.
* If `sentence` is empty, it means we just found the *first* word from the left. We assign it directly to avoid adding an accidental leading/trailing space.
* For every subsequent word, instead of appending it to the end, we **prepend** it (`word + ' ' + sentence`). This built-in ordering reverses the sequence of the words dynamically without needing a stack or an intermediate vector.



---

## 🏃‍♂️ Dry Run Example

Let's trace the execution with an example string that contains tricky spacing:
`s = "  hello   world  "`

### **Setup:**

* `sentence = ""`
* `ss` is loaded with `"  hello   world  "`

---

### **Iteration 1:**

* `ss >> word` runs. It skips the leading spaces and extracts `"hello"`.
* `word = "hello"`
* **Check:** Is `sentence` empty? **Yes**.
* **Action:** `sentence = word;`
* **Current State:** `sentence = "hello"`

---

### **Iteration 2:**

* `ss >> word` runs again. It skips the three spaces between the words and extracts `"world"`.
* `word = "world"`
* **Check:** Is `sentence` empty? **No** (it contains `"hello"`).
* **Action:** `sentence = word + ' ' + sentence;`

$$\text{sentence} = \text{"world"} + \text{" "} + \text{"hello"} = \text{"world hello"}$$


* **Current State:** `sentence = "world hello"`

---

### **Iteration 3:**

* `ss >> word` attempts to run. It encounters the trailing spaces, finds no more valid non-space characters, and hits the End-Of-File (`EOF`).
* The loop terminates.

### **Output:**

The function returns `sentence`, which evaluates to `"world hello"`. All extra spaces were automatically ignored, and the words are successfully reversed.

## 📊 Complexity Analysis

| Complexity | Analysis |
| --- | --- |
| **Time Complexity** | $O(N)$ where $N$ is the length of the string `s`. We traverse the string to read words and build the result. |
| **Space Complexity** | $O(N)$ to store the words inside the `stringstream` buffer and construct the final output string. |
