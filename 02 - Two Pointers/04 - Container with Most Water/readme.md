# Container With Most Water

## Problem Statement

You are given an integer array `height` of length `n`. There are `n` vertical lines drawn such that the two endpoints of the `i`-th line are `(i, 0)` and `(i, height[i])`.

Find two lines that, together with the x-axis, form a container such that the container contains the most water. Return the maximum amount of water a container can store.

**Note:** You may not slant the container. The amount of water is determined by the shorter of the two lines multiplied by the distance between them (width).

### Example

**Input:** `height = [1, 8, 6, 2, 5, 4, 8, 3, 7]`
**Output:** `49`
**Explanation:** The vertical lines at index 1 (`height[1] = 8`) and index 8 (`height[8] = 7`) form the largest container.

* Width = `8 - 1 = 7`
* Height = `min(8, 7) = 7`
* Area = `7 * 7 = 49`

#### Problem URL [https://leetcode.com/problems/container-with-most-water/](https://leetcode.com/problems/container-with-most-water/description/?envType=study-plan-v2&envId=top-interview-150)

## Solution

```cpp
class Solution {
public:
    int maxArea(vector<int>& height) {
        int n = height.size();
        int j = n - 1; // Right pointer
        int i = 0;     // Left pointer
        int area = 0;
        
        while (i < j) {
            // Calculate width and height of the current container
            int width = j - i;
            int h = min(height[i], height[j]);
            
            // Update the maximum area found so far
            area = max(area, width * h);

            // Move the pointer pointing to the shorter line inward
            if (height[i] < height[j]) {
                i++;
            } else {
                j--;
            }
        }

        return area;
    }
};

```

### Explanation of the Source Code

* **Initialization:** We use two pointers, `i` at the beginning (index 0) and `j` at the end (`n-1`) of the array. We maintain an `area` variable to track the maximum area found.
* **Loop:** The `while (i < j)` loop continues as long as the two pointers have not met.
* **Calculation:** Inside the loop, we calculate the `width` as the distance between the two pointers (`j - i`). The `height` of the container is limited by the shorter line (`min(height[i], height[j])`).
* **Update:** We calculate the current area (`width * height`) and update the `area` if the current one is larger.
* **Pointer Strategy:** To potentially find a larger area, we must move the pointer associated with the shorter line. Moving the taller line's pointer inward would only decrease the width without any guarantee of finding a taller line, whereas moving the shorter line's pointer gives us a chance to find a taller line that might compensate for the reduced width.

### Dry Run Example

Input: `height = [1, 8, 6, 2]`

1. `i=0 (val 1)`, `j=3 (val 2)`: `width = 3`, `h = min(1, 2) = 1`. `Area = 3 * 1 = 3`. Since `1 < 2`, `i` moves to 1.
2. `i=1 (val 8)`, `j=3 (val 2)`: `width = 2`, `h = min(8, 2) = 2`. `Area = max(3, 2 * 2) = 4`. Since `8 > 2`, `j` moves to 2.
3. `i=1 (val 8)`, `j=2 (val 6)`: `width = 1`, `h = min(8, 6) = 6`. `Area = max(4, 1 * 6) = 6`. Since `8 > 6`, `j` moves to 1.
4. `i` is no longer `< j`. Loop terminates. Result: **6**.

### Complexity Analysis

* **Time Complexity:** **O(n)**, where `n` is the number of elements in the `height` array. Each pointer moves across the array at most once.
* **Space Complexity:** **O(1)**. We only use a constant amount of extra space for variables `i`, `j`, `area`, `width`, and `h`.
