# Zigzag Conversion

## 📝 Problem Statement
The string `"PAYPALISHIRING"` is written in a zigzag pattern on a given number of rows like this (you may want to display this pattern in a fixed font for better legibility):


```

P   A   H   N
A P L S I I G
Y   I   R

```

And then read line by line: `"PAHNAPLSIIGYIR"`

Write the code that will take a string and make this conversion given a number of rows:
```cpp
string convert(string s, int numRows);

```

#### 🔗 Problem URL [LeetCode - Zigzag Conversion](https://leetcode.com/problems/zigzag-conversion/description/)

## 💻 Source Code

```cpp
class Solution {
public:
    string convert(string s, int numRows) {
        // Edge case: No conversion needed if there's only 1 row
        if (numRows == 1) return s;

        vector<string> rows(numRows);
        bool goingDown = false;
        int currRow = 0;

        for(char c : s){
            rows[currRow] += c;

            // Flip direction when hitting the top or bottom boundaries
            if(currRow == 0 || currRow == numRows - 1) goingDown = !goingDown;

            // Step up or down depending on the direction flag
            currRow += goingDown ? 1 : -1;
        }

        // Combine all rows into a single string
        string result = "";
        for(string &row: rows) result += row;

        return result;
    }
};

```

## 🔍 Source Code Explanation

* **`if (numRows == 1) return s;`**: If there is only one row, the zigzag movement is impossible (you would just bounce in place). The output string remains identical to the input.
* **`vector<string> rows(numRows);`**: Instead of managing a complex 2D character matrix full of spaces, we create an array of strings. Each string represents a horizontal row where characters will be appended.
* **`bool goingDown = false;`**: A state tracker flag that determines whether we are moving down towards the bottom row (`true`) or up towards the top row (`false`).
* **`if(currRow == 0 || currRow == numRows - 1) goingDown = !goingDown;`**: This acts as a wall-bounce detector. Every time our row pointer touches row `0` (the ceiling) or row `numRows - 1` (the floor), it flips the boolean flag to reverse directions.
* **`result += row;`**: A final aggregation loop that appends each processed row sequentially from top to bottom to form the final transformed string.

---

## 💡 Intuition & Solution Approach

### The Core Intuition

The problem naturally looks like a physical object bouncing back and forth between two walls (the top row and the bottom row).

Instead of trying to calculate the mathematical mathematical jump indices for a 1D string array, it is far more intuitive to **simulate the process dynamically**. We process the characters of the string one by one, drop them into their respective row "buckets", and change our movement direction every time we hit a boundary.

---

## 🔄 Dry Run Example

Let's trace the algorithm with **`s = "PAYPALISHIRING"`** and **`numRows = 3`**.

Initial Setup:

* `rows = ["", "", ""]`
* `currRow = 0`, `goingDown = false`

### Step-by-Step Execution:

| Character | Current Row Index | `currRow` Boundary Match? | Action on `goingDown` | Next Row Calculation | Row Buckets State |
| --- | --- | --- | --- | --- | --- |
| **P** | `0` | Yes (`currRow == 0`) | Flips to `true` | `0 + 1 = 1` | `rows[0] = "P"` |
| **A** | `1` | No | Stays `true` | `1 + 1 = 2` | `rows[1] = "A"` |
| **Y** | `2` | Yes (`currRow == 2`) | Flips to `false` | `2 - 1 = 1` | `rows[2] = "Y"` |
| **P** | `1` | No | Stays `false` | `1 - 1 = 0` | `rows[1] = "AP"` |
| **A** | `0` | Yes (`currRow == 0`) | Flips to `true` | `0 + 1 = 1` | `rows[0] = "PA"` |
| **L** | `1` | No | Stays `true` | `1 + 1 = 2` | `rows[1] = "APL"` |
| **I** | `2` | Yes (`currRow == 2`) | Flips to `false` | `2 - 1 = 1` | `rows[2] = "YI"` |
| ... | ... | ... | ... | ... | ... |
| **G** | `1` | No | Stays `true` | Loop Ends | `rows[0]="PAHN"`, `rows[1]="APLSIIG"`, `rows[2]="YIR"` |

### Final Assembly:

Combine `rows[0] + rows[1] + rows[2]`:
`"PAHN"` + `"APLSIIG"` + `"YIR"` = **`"PAHNAPLSIIGYIR"`**

---

## 📊 Complexity Analysis

### Time Complexity: $O(n)$

* **Distribution Phase:** We iterate through the string `s` exactly once, performing constant time $O(1)$ operations to append characters to our rows. This takes $O(n)$ time where $n$ is the length of string `s`.
* **Concatenation Phase:** We iterate through the rows to build the final output string. Every character is visited exactly once here too, taking $O(n)$ time.
* **Total Time Complexity:** $O(n)$

### Space Complexity: $O(n)$

* We allocate a `vector<string>` containing `numRows` strings. Together, these strings store exactly $n$ characters. No additional empty spaces or filler characters are allocated.
* **Total Space Complexity:** $O(n)$
