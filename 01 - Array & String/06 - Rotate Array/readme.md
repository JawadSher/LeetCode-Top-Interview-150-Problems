# Rotate Array

LeetCode Problem: [https://leetcode.com/problems/rotate-array/](https://leetcode.com/problems/rotate-array/)

---

## Problem Statement

Given an integer array `nums`, rotate the array to the right by `k` steps, where `k` is non-negative.

**Example 1:**
```
Input:  nums = [1, 2, 3, 4, 5, 6, 7], k = 3
Output: [5, 6, 7, 1, 2, 3, 4]
```

**Example 2:**
```
Input:  nums = [1, 2, 3, 4, 5], k = 2
Output: [4, 5, 1, 2, 3]
```

**Constraints:**
- `1 <= nums.length <= 10^5`
- `-2^31 <= nums[i] <= 2^31 - 1`
- `0 <= k <= 10^5`

---

## Key Observation Before Solving

Before writing any code, trace what actually happens physically:

```
Original: [1, 2, 3, 4, 5],  k = 2

Step 1:   [5, 1, 2, 3, 4]   ← last element jumps to front
Step 2:   [4, 5, 1, 2, 3]   ← last element jumps to front again
```

One rotation step = save last element → shift everything right by 1 → place saved element at front.

### Why k %= n matters

If `k = 5` on an array of size 5, you rotate back to the original — wasted work.
If `k = 7` on an array of size 5, it's the same as `k = 2` because `7 % 5 = 2`.

So always reduce: `k = k % n` before doing anything.

---

## Solution 1 — Brute Force (TLE on large inputs)

### Intuition

The simplest idea: simulate one rotation step k times.

One step:
1. Save `nums[0]` (leftmost element)
2. Put `nums[n-1]` at `nums[0]`
3. Shift inner elements right by 1
4. Place saved element at `nums[1]`

Repeat this k times.

### Code

```cpp
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
            k %= n;
            for(int i = 1; i <= k; i++){
                int l = nums[0];
                nums[0] = nums[n-1];
                
                for(int j = n-1; j > 1; j--){
                     nums[j] = nums[j-1];
                }
                nums[n-n+1] = l;
                
            }
    }
};
```

### Why it fails on large inputs

- Outer loop runs `k` times
- Inner loop runs `n` times
- Total: `n * k` operations

Worst case: `n = 100000`, `k = 99999` → **~10 billion operations** → LeetCode times out.

**Time:** O(n * k) | **Space:** O(1)

---

## Solution 2 — Extra Array with Math

### Intuition

Instead of physically shifting elements k times, ask: **where does each element end up?**

Trace `[1, 2, 3, 4, 5]` with `k = 2`:

```
i=0: nums[0]=1 → rotated[(0+2)%5] = rotated[2] = 1
i=1: nums[1]=2 → rotated[(1+2)%5] = rotated[3] = 2
i=2: nums[2]=3 → rotated[(2+2)%5] = rotated[4] = 3
i=3: nums[3]=4 → rotated[(3+2)%5] = rotated[0] = 4
i=4: nums[4]=5 → rotated[(4+2)%5] = rotated[1] = 5

Result: [4, 5, 1, 2, 3] ✅
```

The beauty: element at index `i` always belongs at index `(i + k) % n` after rotation.
The `% n` handles the wraparound when the index exceeds the array size.

Every element jumps directly to its final position in **one single pass**. No shifting at all.

### Code

```cpp
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        k %= n;
        vector<int> rotated(n);
        for (int i = 0; i < n; i++) {
            rotated[(i + k) % n] = nums[i];
        }
        nums = rotated;
    }
};
```

**Time:** O(n) | **Space:** O(n)

---

## Solution 3 — Reverse Trick (Optimal)

### Intuition

This is the O(1) space solution. It uses a beautiful mathematical pattern with reversals.

**Observation:** Take `[1, 2, 3, 4, 5]` with `k = 2`. Expected output: `[4, 5, 1, 2, 3]`.

**Step 1 — Reverse the entire array:**
```
[1, 2, 3, 4, 5]  →  [5, 4, 3, 2, 1]
```

**Step 2 — Reverse the first k elements:**
```
[5, 4, 3, 2, 1]  →  [4, 5, 3, 2, 1]
 ↑  ↑
 reverse these (k=2)
```

**Step 3 — Reverse the remaining elements from index k to end:**
```
[4, 5, 3, 2, 1]  →  [4, 5, 1, 2, 3]
       ↑  ↑  ↑
       reverse these
```

Result: `[4, 5, 1, 2, 3]` ✅

### Why this works

After reversing the entire array, the elements that should be at the front are at the front — but in reverse order. Reversing the first k elements fixes their order. The remaining elements are also in reverse order, so reversing them fixes their order too.

### How to think the loop condition for partial reversal

For any reversal of a section from index `start` to index `end`:
- The midpoint is `start + (end - start) / 2`
- The loop runs while `i < midpoint`

For the third loop reversing from `k` to `n-1`:
- `start = k`, `end = n-1`
- Midpoint = `k + (n-k) / 2`
- Swap partner of index `i` is `nums[n - (i - k) - 1]`

### Code

```cpp
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        k %= n;

        // Step 1: Reverse entire array
        for (int i = 0; i < n / 2; i++) {
            swap(nums[i], nums[n - i - 1]);
        }

        // Step 2: Reverse first k elements
        for (int i = 0; i < k / 2; i++) {
            swap(nums[i], nums[k - i - 1]);
        }

        // Step 3: Reverse remaining elements from k to end
        for (int i = k; i < k + (n - k) / 2; i++) {
            swap(nums[i], nums[n - (i - k) - 1]);
        }
    }
};
```

**Time:** O(n) | **Space:** O(1)

---

## Summary

| Solution | Time | Space | Result |
|---|---|---|---|
| Brute Force (simulate k steps) | O(n * k) | O(1) | TLE on large input |
| Extra Array with math formula | O(n) | O(n) | Accepted |
| Reverse Trick | O(n) | O(1) | Accepted (Optimal) |

---

## Thinking Pattern to Remember

1. **Don't jump to code.** Trace a small example first (`[1,2,3,4,5]`, `k=2`) and watch what physically happens.
2. **Find the atomic unit.** What does ONE step look like? Build from there.
3. **Ask where each element ends up.** That question leads directly to the `(i+k)%n` formula.
4. **When stuck on space, think in reversals.** Many array rearrangement problems have elegant reversal-based O(1) solutions.
5. **Always verify loop bounds by tracing.** Before running code, ask: "Can this index ever go out of bounds?"
