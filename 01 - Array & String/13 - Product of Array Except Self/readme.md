# Product of Array Except Self


## 📝 Problem Statement
Given an integer array `nums`, return *an array* `ans` *such that* `ans[i]` *is equal to the product of all the elements of* `nums` *except* `nums[i]`.

The product of any prefix or suffix of `nums` is **guaranteed** to fit in a **32-bit** integer.

### ⚠️ Constraints & Follow-up
* **Constraint:** You must write an algorithm that runs in $O(n)$ time and **without using the division operation**.
* **Follow-up:** Can you solve the problem in $O(1)$ extra space complexity? (The output array **does not** count as extra space for space complexity analysis.)

### 📥 Example 1
* **Input:** `nums = [1, 2, 3, 4]`
* **Output:** `[24, 12, 8, 6]`
* *Explanation:* * `ans[0]` = 2 * 3 * 4 = 24
    * `ans[1]` = 1 * 3 * 4 = 12
    * `ans[2]` = 1 * 2 * 4 = 8
    * `ans[3]` = 1 * 2 * 3 = 6

### 📥 Example 2
* **Input:** `nums = [-1, 1, 0, -3, 3]`
* **Output:** `[0, 0, 9, 0, 0]`

#### Problem Link [LeetCode - Product of Array Except Self](https://leetcode.com/problems/product-of-array-except-self/?envType=study-plan-v2&envId=top-interview-150)


## 💡 Solution Strategy
Any element's product-except-self value can be broken down into two distinct parts:
$$\text{ans}[i] = (\text{Product of all elements to the left of } i) \times (\text{Product of all elements to the right of } i)$$

Instead of creating separate auxiliary prefix and suffix arrays (which would cost $O(n)$ extra space), we use a **two-pass approach** directly inside our final output array:
1.  **Forward Pass (Prefix):** Accumulate the product of all elements to the left of index $i$ and store it directly in `ans[i]`.
2.  **Backward Pass (Suffix):** Traverse backward, keeping track of a running suffix product. Multiply it into the existing prefix value already sitting inside `ans[i]`.

---

## 💻 Code Implementation

```cpp
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        
        vector<int> ans(n);
        ans[0] = 1; // Base case: nothing exists to the left of index 0
        
        int prefix = 1;
        int suffix = 1;
        
        // Step 1: Compute Prefix Products
        for(int i = 1; i < n; i++){
            ans[i] = prefix * nums[i-1];
            prefix = prefix * nums[i-1];
        }
        
        // Step 2: Compute Suffix Products & Combine
        for(int i = n-2; i >= 0; i--){
            ans[i] = (suffix * nums[i+1]) * ans[i];
            suffix = suffix * nums[i+1];
        }
        
        return ans;
    }
};

```

---

## 🔍 Line-by-Line Code Explanation

* **`int n = nums.size();`**
Extracts the size of the input array so we can initialize container bounds and structure our loops.
* **`vector<int> ans(n);`**
Creates the output integer array `ans` of size `n` which will store the final calculated products.
* **`ans[0] = 1;`**
Sets up the base element. Since index `0` has no elements to its left, its initial prefix product value defaults to `1`.
* **`int prefix = 1; int suffix = 1;`**
Initializes tracking accumulators. `prefix` keeps a rolling track of leftward products, and `suffix` keeps a rolling track of rightward products.
* **`for(int i = 1; i < n; i++) { ... }`**
Iterates from index `1` to `n-1`. For every element, it calculates the cumulative product of all items before it and assigns it to `ans[i]`. It then updates the rolling `prefix` state variable.
* **`for(int i = n-2; i >= 0; i--) { ... }`**
Iterates backward from the second-to-last element (`n-2`) down to `0`. It calculates the suffix product of all items to the right of `i`, multiplies it by the pre-calculated prefix value already saved in `ans[i]`, and saves it back.

---

## ⚙️ Execution Walkthrough (Dry Run)

Let’s trace the execution using **`nums = [1, 2, 3, 4]`** where `n = 4`.

### Phase 1: Initialization

* `ans` is initialized with size 4.
* `ans[0] = 1` -> `ans = [1, 0, 0, 0]`
* `prefix = 1`

### Phase 2: Prefix Loop (Forward Pass)

We loop from `i = 1` to `i = 3`:

| Index (`i`) | `nums[i-1]` | Calculation (`prefix * nums[i-1]`) | Resulting `ans[i]` | Updated `prefix` |
| --- | --- | --- | --- | --- |
| **`i = 1`** | `nums[0] = 1` | `1 * 1` | `ans[1] = 1` | `prefix = 1` |
| **`i = 2`** | `nums[1] = 2` | `1 * 2` | `ans[2] = 2` | `prefix = 2` |
| **`i = 3`** | `nums[2] = 3` | `2 * 3` | `ans[3] = 6` | `prefix = 6` |

* **State after Forward Pass:** `ans = [1, 1, 2, 6]`

---

### Phase 3: Suffix Loop (Backward Pass)

We initialize `suffix = 1` and loop backward from `i = 2` down to `i = 0`:

| Index (`i`) | `nums[i+1]` | Calculation (`(suffix * nums[i+1]) * ans[i]`) | Resulting `ans[i]` | Updated `suffix` |
| --- | --- | --- | --- | --- |
| *Initial* | — | — | `ans[3] = 6` (unchanged) | `suffix = 1` |
| **`i = 2`** | `nums[3] = 4` | `(1 * 4) * ans[2]` $\rightarrow$ `4 * 2` | `ans[2] = 8` | `suffix = 4` |
| **`i = 1`** | `nums[2] = 3` | `(4 * 3) * ans[1]` $\rightarrow$ `12 * 1` | `ans[1] = 12` | `suffix = 12` |
| **`i = 0`** | `nums[1] = 2` | `(12 * 2) * ans[0]` $\rightarrow$ `24 * 1` | `ans[0] = 24` | `suffix = 24` |

* **Final Output State:** `ans = [24, 12, 8, 6]`

---

## 📊 Complexity Analysis

### ⏱️ Time Complexity: $O(n)$

* **Prefix Pass:** Iterates through the array exactly $n-1$ times $\rightarrow O(n)$.
* **Suffix Pass:** Iterates backwards through the array exactly $n-1$ times $\rightarrow O(n)$.
* Total running time is $O(n) + O(n) = O(2n)$, which simplifies strictly to **$O(n)$**.

### 🗄️ Space Complexity: $O(1)$

* No additional internal linear data configurations (like variable prefix or suffix array structures) are defined.
* We only utilize a few primitive integer scale variables (`prefix`, `suffix`, `n`, `i`).
* According to problem guidelines, the memory allocation consumed by returning the final output array `ans` does not factor into overall extra space complexity. Thus, the solution utilizes **$O(1)$ auxiliary space**.
