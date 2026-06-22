# Text Justification

> **[Problem Link → LeetCode 68: Text Justification](https://leetcode.com/problems/text-justification/description/?envType=study-plan-v2&envId=top-interview-150)**

---

## Problem Statement

Format a list of words onto lines where **every line must be exactly `maxWidth` characters long**.

### Justification Rules

| Rule | Description |
|---|---|
| **Greedy Packing** | Fit as many words as possible on each line. Never split a word. |
| **Even Spacing** | Fill remaining empty slots with spaces distributed *between* words. |
| **Left-Heavy Spacing** | If spaces can't divide evenly, left gaps get more spaces than right gaps. |
| **Single-Word Lines** | One word sits at the far left; all remaining spaces pad the right. |
| **Last Line Exception** | Last line is strictly left-justified (one space between words), trailing spaces fill the end. |

---

## Intuition & Analogy

Think of this like **packing books into identical cardboard boxes**:

- **Step 1 — Pack:** Keep placing books into the current box until the next one is too big to fit.
- **Step 2 — Fill:** The books don't fill the box perfectly, so you stuff bubble wrap (spaces) between them.
- **Step 3 — Left bias:** If you have an odd amount of bubble wrap, prioritize the leftmost gaps first.
- **Step 4 — Last box:** Just shove all books to the left and dump all remaining bubble wrap on the right.

**Key insight:** This is a pure **simulation** problem — no tricks, no sorting, no complex data structures. You just:
1. Track your position with pointer `i`
2. Look ahead with pointer `j` to see how many words fit
3. Calculate leftover space mathematically
4. Meticulously construct the string

---

## Solution Code

```cpp
class Solution {
public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        int n = words.size();
        vector<string> ans;
        int i = 0;

        while (i < n) {
            int charsCount = words[i].length();
            int j = i + 1;
            int spacesBtwWords = 0;

            // Greedy: find how many words fit on this line
            while (j < n && charsCount + spacesBtwWords + words[j].length() + 1 <= maxWidth) {
                charsCount += words[j].length();
                spacesBtwWords++;
                j++;
            }

            int allSpacesInLine = maxWidth - charsCount;
            int baseSpaces    = spacesBtwWords <= 0 ? 0 : allSpacesInLine / spacesBtwWords;
            int extraLeftSpace = spacesBtwWords <= 0 ? 0 : allSpacesInLine % spacesBtwWords;

            string line = "";
            bool isLastLine = (j == n);

            // Build the line word by word
            for (int k = i; k < j; k++) {
                line += words[k];

                if (k == j - 1) break; // no spaces after the last word

                if (isLastLine || spacesBtwWords == 0) {
                    line += " "; // left-justify: single space
                } else {
                    // Standard justification: base spaces + possibly 1 extra
                    int spacesToAdd = baseSpaces + (extraLeftSpace > 0 ? 1 : 0);
                    if (extraLeftSpace > 0) extraLeftSpace--;
                    for (int s = 0; s < spacesToAdd; s++) line += " ";
                }
            }

            // Pad right side for last line or single-word lines
            if (isLastLine || spacesBtwWords == 0)
                while (line.size() < maxWidth) line += " ";

            ans.push_back(line);
            i = j;
        }

        return ans;
    }
};
```

> ⚠️ **Bug fix note:** In a common incorrect version, `extraLeftSpace` is decremented *inside* the inner `s` loop. This dumps all extra spaces into the very first gap (e.g., gaps of `4, 2, 2` instead of `3, 3, 2`). The fix is to compute `spacesToAdd` **before** the loop and decrement `extraLeftSpace` exactly once per gap.

---

## Code Walkthrough

### Initialization
- `i = 0` — pointer to the first word of the current line
- `ans` — accumulates the final formatted lines

### Outer Loop: `while (i < n)`
Runs until every word has been placed on a line.

### Phase 1 — Greedy Word Fitting
```
charsCount = words[i].length()   // start with the first word
j = i + 1                        // look-ahead pointer
spacesBtwWords = 0
```
- The inner `while` checks: can the next word fit if separated by at least 1 space?
- Condition: `charsCount + spacesBtwWords + words[j].length() + 1 <= maxWidth`
- If yes → add its length, increment `spacesBtwWords`, advance `j`

### Phase 2 — Space Math
```
allSpacesInLine = maxWidth - charsCount     // total spaces to distribute
baseSpaces      = allSpacesInLine / spacesBtwWords   // every gap gets this many
extraLeftSpace  = allSpacesInLine % spacesBtwWords   // this many left gaps get +1
```

### Phase 3 — String Construction
- `isLastLine = (j == n)` flags whether we're on the final line
- Loop over words `k = i` to `j`:
  - Append the word
  - If last word in loop → stop (no trailing space)
  - If **last line or single word** → append `" "` (left-justify)
  - Otherwise → append `baseSpaces + (1 if extraLeftSpace > 0)`

### Phase 4 — Right Padding
- For last line or single-word lines, pad with spaces until `line.size() == maxWidth`

---

## Dry Run

**Input:** `words = ["This", "is", "an", "example"]`, `maxWidth = 16`

| Step | Action | Math | State |
|---|---|---|---|
| 1 | Start Line 1 with "This" | `charsCount = 4` | — |
| 2 | Fit "is" | `4+0+2+1=7 ≤ 16` ✅ | `charsCount=6, gaps=1` |
| 3 | Fit "an" | `6+1+2+1=10 ≤ 16` ✅ | `charsCount=8, gaps=2` |
| 4 | Try "example" | `8+2+7+1=18 > 16` ❌ | Stop at `j=3` |
| 5 | Space math | `16-8=8 total`, `8/2=4 base`, `8%2=0 extra` | — |
| 6 | Build line | `"This"` + 4 spaces + `"is"` + 4 spaces + `"an"` | `"This    is    an"` |
| 7 | Save, advance | `i = 3` | `ans = ["This    is    an"]` |
| 8 | Start Line 2 with "example" | `charsCount=7, j=4` | `isLastLine = true` |
| 9 | Build & pad | Left-justify, pad right | `"example         "` |
| 10 | Done | Push to `ans` | Return `ans` |

**Output:** `["This    is    an", "example         "]`

---

## Complexity Analysis

### Time Complexity — O(N)
- `N` = total characters across all words
- Each word is visited **at most twice**: once during fitting, once during string building
- String construction is bounded by total output size
- The nested loops don't compound — work per word stays constant

### Space Complexity — O(N)
- The `ans` vector stores all formatted lines
- Total output size is proportional to input size plus added spaces
- No auxiliary data structures used beyond the output itself

---

## Edge Cases to Keep in Mind

- **Single word on a line** — must be left-padded to `maxWidth` (not justified)
- **Last line** — always left-justified regardless of word count
- **Perfect fit** — when words exactly fill `maxWidth` with no extra spaces needed
- **Single word input** — both a single-word line *and* the last line simultaneously
