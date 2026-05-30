# 🗑️ Remove Element

## 📌 Problem Statement

Given an integer array `nums` and an integer `val`, remove all occurrences of `val` in `nums` **in-place**. The order of the elements may be changed. Then, return the number of elements in `nums` which are not equal to `val`.

### ⚠️ Constraints & Rules:

1. **In-Place Modification:** You must modify the input array directly with $O(1)$ extra memory. Do not allocate extra space for another array.
2. **Return Value ($k$):** Your function must return the number of elements that are not equal to `val`.
3. **Array Validation:** The first $k$ elements of `nums` must contain the elements which are not equal to `val`. What you leave beyond the first $k$ elements does not matter.

---

## 🧪 Examples

### **Example 1**

* **Input:** `nums = [3, 2, 2, 3]`, `val = 3`
* **Output:** `2`, `nums = [2, 2, _, _]`
* **Explanation:** Your function should return `k = 2`, with the first two elements of `nums` being `2`. It does not matter what you leave beyond the returned $k$ (hence underscores).

### **Example 2**

* **Input:** `nums = [0, 1, 2, 2, 3, 0, 4, 2]`, `val = 2`
* **Output:** `5`, `nums = [0, 1, 3, 0, 4, _, _, _]`
* **Explanation:** Your function should return `k = 5`, with the first five elements of `nums` containing `0`, `1`, `3`, `0`, and `4`. Note that the order of those five elements can be arbitrary.

---

## ⚠️ Edge Cases Kept in Mind

* **All elements match `val`:** `nums = [2, 2, 2]`, `val = 2` $\rightarrow$ Output: `0`.
* **No elements match `val`:** `nums = [1, 2, 3]`, `val = 4` $\rightarrow$ Output: `3`.
* **Empty Array:** `nums = []`, `val = 1` $\rightarrow$ Output: `0`.
* **Single element matches/doesn't match:** `nums = [1]`, `val = 1` $\rightarrow$ Output: `0`.

---

## 🧠 Approach 1: Vector Erase Method (Initial Approach)

### **Idea:**

Iterate through the array. Whenever an element equals `val`, use the built-in `nums.erase()` method to physically drop the element. Because `erase()` shifts all subsequent elements to the left, we must decrement our loop counter (`i--`) to ensure we don't skip evaluating the newly shifted element at the current index.

### **C++ Implementation:**

```cpp
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int n = nums.size();
        
        for(int i = 0; i < nums.size(); i++){
            if(nums[i] == val) {
                nums.erase(nums.begin() + i); // Removes element and shifts everything left
                n--;                          // Reduce overall count tracker
                i--;                          // Step back index to re-verify the new element at 'i'
            }
        }
        return n;
    }
};

```

### **Dry Run Example:** `nums = [1, 2, 2, 3]`, `val = 2`

| Loop Index (`i`) | Array State (`nums`) | Condition (`nums[i] == val`) | Action Taken | Current Count (`n`) |
| --- | --- | --- | --- | --- |
| **0** | `[1, 2, 2, 3]` | `1 == 2` (False) | Move forward | 4 |
| **1** | `[1, 2, 2, 3]` | `2 == 2` (True) | Erase index 1, `i--` | 3 |
| **1** | `[1, 2, 3]` | `2 == 2` (True) | Erase index 1, `i--` | 2 |
| **1** | `[1, 3]` | `3 == 2` (False) | Move forward | 2 |
| **End** | `[1, 3]` | Loop exits | **Returns 2** | 2 |

### **Complexity Analysis:**

* ⏱️ **Time Complexity:** $O(N^2)$ — While we only have a single `for` loop, the `std::vector::erase` operation itself takes $O(N)$ time because it shifts all the elements after the erased position to the left. In the worst-case scenario (e.g., all elements need to be removed), this causes quadratic time consumption.
* 📦 **Space Complexity:** $O(1)$ — Done purely in-place.

---

## 🚀 Approach 2: Two-Pointer Technique (Optimized Interview Solution)

> 💡 **Why this is better:** Instead of physically deleting elements and causing costly array reshuffling ($O(N)$ per deletion), we can overwrite elements using a **reader** and **writer** pointer configuration.

### **Idea:**

We maintain a pointer `k` which tracks where the next valid element should be placed. We iterate through the array using another index `i`:

* If `nums[i]` is **not** equal to `val`, we copy its value over to `nums[k]` and increment `k`.
* If `nums[i]` **is** equal to `val`, we simply ignore it and move on.

### **Optimal C++ Implementation:**

```cpp
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int k = 0; // Tracks the insertion point for valid elements
        
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] != val) {
                nums[k] = nums[i]; // Write the valid element over the unwanted data
                k++;               // Advance valid element boundary
            }
        }
        return k; // k matches the total number of non-val items
    }
};

```

### **Complexity Analysis:**

* ⏱️ **Time Complexity:** $O(N)$ — We iterate through the array exactly once. No underlying element shifting occurs.
* 📦 **Space Complexity:** $O(1)$ — Modifies the array entirely in-place.

---

## 🧠 Key Takeaways

1. **Be Mindful of Modifying Collections During Iteration:** When removing elements from a linear data structure dynamically, indices shift. Failing to decrement the iterator or index variable (`i--`) will introduce subtle bugs where consecutive targets are skipped.
2. **Avoid Shifting Overhead:** Native methods like `.erase()` hide nested linear loops under the hood. Using **Two-Pointers** to overwrite garbage values instead of collapsing the array shrinks execution time from $O(N^2)$ to an optimal $O(N)$.
