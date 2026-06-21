
# Find the Index of the First Occurrence in a String

## 📝 Problem Statement
Given two strings `needle` and `haystack`, return the index of the first occurrence of `needle` in `haystack`, or `-1` if `needle` is not part of `haystack`.

### Example 1
* **Input:** `haystack = "sadbutsad"`, `needle = "sad"`
* **Output:** `0`
* **Explanation:** `"sad"` occurs at index 0 and 6. The first occurrence is at index 0, so we return 0.

### Example 2
* **Input:** `haystack = "leetcode"`, `needle = "leeto"`
* **Output:** `-1`
* **Explanation:** `"leeto"` did not occur in `"leetcode"`, so we return -1.

#### 🔗 Problem URL [LeetCode - Find the Index of the First Occurrence in a String](https://leetcode.com/problems/find-the-index-of-the-first-occurrence-in-a-string/description/)


## 💻 Source Code

```cpp
class Solution {
public:
    int strStr(string haystack, string needle) {
        int n = haystack.length();
        int j = needle.length();
        int i = 0;

        // Loop only as long as the remaining characters can fit the needle
        while (i <= n - j) {
            // Check if the substring starting at index i matches needle
            if (needle == haystack.substr(i, j)) return i;

            i++;
        }

        return -1;
    }
};

```

### 🔍 Source Code Explanation

* **`int n = haystack.length(); int j = needle.length();`**: Stores the lengths of both strings to avoid making repeated function calls inside the loop.
* **`while (i <= n - j)`**: This is an optimized boundary condition. If `haystack` has 5 characters left and `needle` requires 6 characters, it is mathematically impossible to find a match. Stopping at `n - j` prevents redundant iterations at the end of the string.
* **`haystack.substr(i, j)`**: Extracts a substring from `haystack` starting at index `i` with a fixed length of `j` (the length of the `needle`).
* **`if (needle == ...)`**: Directly compares the extracted chunk with our target `needle`. If they match perfectly, we immediately return the starting index `i`.
* **`return -1;`**: If the loop finishes without finding a match, the function returns `-1`.

### The Core Intuition

This approach utilizes a **Sliding Window / Substring Matching** simulation. Think of `needle` as a fixed-size stencil. We place this stencil over the start of `haystack`, check if the letters match underneath, and if they don't, we slide the stencil forward by exactly 1 character position (`i++`) and check again.

Instead of writing complex inner tracking loops, we leverage C++'s built-in `substr()` string slicer to handle the window character extractions natively.

---

## 🔄 Dry Run Example

Let's trace the algorithm with **`haystack = "hello"`** and **`needle = "ll"`**.

Initial Setup:

* `n = 5` (length of `"hello"`)
* `j = 2` (length of `"ll"`)
* Boundary limit: `n - j = 5 - 2 = 3` (Loop runs while `i <= 3`)

### Step-by-Step Execution:

| Step (`i`) | Substring Extracted via `haystack.substr(i, 2)` | Comparison (`substr == needle`) | Action |
| --- | --- | --- | --- |
| **`i = 0`** | `haystack.substr(0, 2)` $\rightarrow$ `"he"` | `"he" == "ll"` $\rightarrow$ **False** | Move to next index (`i++`) |
| **`i = 1`** | `haystack.substr(1, 2)` $\rightarrow$ `"el"` | `"el" == "ll"` $\rightarrow$ **False** | Move to next index (`i++`) |
| **`i = 2`** | `haystack.substr(2, 2)` $\rightarrow$ `"ll"` | `"ll" == "ll"` $\rightarrow$ **True** | **Match found! Return `2**` |

The function returns `2` and terminates early.

---

## 📊 Complexity Analysis

### Time Complexity: $O((n - j) \cdot j)$

* **Outer Loop:** Runs at most $n - j + 1$ times.
* **Substring & Comparison:** Generating a substring of length $j$ and comparing it character-by-character against `needle` takes $O(j)$ time in the worst case.
* **Total Time Complexity:** $O((n - j) \cdot j)$. In worst-case scenarios (like `haystack = "aaaaa"`, `needle = "aab"`), it behaves like $O(n \cdot j)$.

### Space Complexity: $O(j)$

* **Memory Allocation:** Inside the loop, `haystack.substr(i, j)` dynamically allocates a temporary string copy of size $j$ for comparison during each iteration.
* **Total Space Complexity:** $O(j)$ auxiliary space.
