# Insert Delete GetRandom O(1)

## Problem Statement

Implement the `RandomizedSet` class:

* `RandomizedSet()` Initializes the `RandomizedSet` object.
* `bool insert(int val)` Inserts an item `val` into the set if not present. Returns `true` if the item was not present, `false` otherwise.
* `bool remove(int val)` Removes an item `val` from the set if present. Returns `true` if the item was present, `false` otherwise.
* `int getRandom()` Returns a random element from the current set of elements (it's guaranteed that at least one element exists when this method is called). Each element must have the **same probability** of being returned.

You must implement the functions of the class such that each function works in **average** `O(1)` time complexity.

### Examples

**Input:**

```text
["RandomizedSet", "insert", "remove", "insert", "getRandom", "remove", "insert", "getRandom"]
[[], [1], [2], [2], [], [1], [2], []]

```

**Output:**

```text
[null, true, false, true, 2, true, false, 2]

```

**Explanation:**

1. `RandomizedSet randomizedSet = new RandomizedSet();`
2. `randomizedSet.insert(1); // Inserts 1 to the set. Returns true as 1 was inserted successfully.`
3. `randomizedSet.remove(2); // Returns false as 2 does not exist in the set.`
4. `randomizedSet.insert(2); // Inserts 2 to the set, returns true. Set now contains [1,2].`
5. `randomizedSet.getRandom(); // getRandom() should return either 1 or 2 randomly.`
6. `randomizedSet.remove(1); // Removes 1 from the set, returns true. Set now contains [2].`
7. `randomizedSet.insert(2); // Returns false as 2 is already in the set.`
8. `randomizedSet.getRandom(); // Since 2 is the only number in the set, getRandom() will always return 2.`

---

#### Problem Link: [Insert Delete GetRandom O(1)](https://leetcode.com/problems/insert-delete-getrandom-o1/)

---

## Solution (C++)

```cpp
class RandomizedSet {
    vector<int> vec;
    unordered_map<int, int> mp;
public:
    RandomizedSet() {}
    
    bool insert(int val) {
        if(!mp.count(val)){
            vec.push_back(val);
            int index = vec.size() - 1;
            mp[val] = index;
            return true;
        }
        return false;
    }
    
    bool remove(int val) {
        if(mp.count(val)){
            int index = mp.find(val)->second; 
            mp[vec[vec.size()-1]] = index;
            swap(vec[index], vec[vec.size()-1]); 
            mp.erase(val);
            vec.pop_back();
            return true;
        }
        return false;
    }
    
    int getRandom() {
        return vec[rand() % vec.size()];
    }
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */

```

---

## Step-by-Step Source Code Explanation

To achieve an average time complexity of $O(1)$ for all operations, we combine two data structures:

1. **`vector<int> vec`**: Allows us to get a random element in $O(1)$ time using indexing.
2. **`unordered_map<int, int> mp`**: Maps a value to its corresponding index in the vector, allowing $O(1)$ lookups.

### 1. Class Initialization

```cpp
vector<int> vec;
unordered_map<int, int> mp;

```

* `vec` stores the actual values.
* `mp` stores key-value pairs where the key is `val` and the value is its index inside `vec`.

### 2. `insert(int val)`

```cpp
if(!mp.count(val)){
    vec.push_back(val);
    int index = vec.size() - 1;
    mp[val] = index;
    return true;
}

```

* **Step 1:** Check if `val` already exists using `mp.count(val)`. If it exists, return `false`.
* **Step 2:** If it's a new value, push it to the back of `vec`.
* **Step 3:** Record its position (the last index of `vec`) into `mp`.

### 3. `remove(int val)`

Removing from an arbitrary index in an array normally takes $O(N)$ time because elements have to shift. To do it in $O(1)$ time:

```cpp
if(mp.count(val)){
    int index = mp.find(val)->second; 
    mp[vec[vec.size()-1]] = index;
    swap(vec[index], vec[vec.size()-1]); 
    mp.erase(val);
    vec.pop_back();
    return true;
}

```

* **Step 1:** Check if `val` exists in `mp`. If not, return `false`.
* **Step 2:** Get the index of `val` from `mp`.
* **Step 3:** Update the map entry of the **last element** in `vec` to point to the index of the element being removed.
* **Step 4:** Swap the target element with the last element of `vec`.
* **Step 5:** Erase `val` from `mp` and remove the last element from `vec` using `pop_back()` (which is an $O(1)$ operation).

### 4. `getRandom()`

```cpp
return vec[rand() % vec.size()];

```

* Uses standard `rand()` to produce a random index within the bounds of `vec.size()`. Since all elements are stored contiguously in the vector, this returns any element with equal probability in $O(1)$ time.

---

## Dry Run Example

Let's trace how the data structures change with a sequence of operations:

| Operation | Internal Logic | State of `vec` | State of `mp` | Return Value |
| --- | --- | --- | --- | --- |
| **Initial** | Instantiate structures | `[]` | `{}` | `null` |
| `insert(10)` | `10` not in map. Push to `vec`. Update `mp[10] = 0`. | `[10]` | `{10: 0}` | `true` |
| `insert(20)` | `20` not in map. Push to `vec`. Update `mp[20] = 1`. | `[10, 20]` | `{10: 0, 20: 1}` | `true` |
| `insert(30)` | `30` not in map. Push to `vec`. Update `mp[30] = 2`. | `[10, 20, 30]` | `{10: 0, 20: 1, 30: 2}` | `true` |
| `remove(20)` | Find index of `20` (index 1). Swap `20` with last element (`30`). Update `mp[30] = 1`. Pop `20`. | `[10, 30]` | `{10: 0, 30: 1}` | `true` |
| `getRandom()` | Generates random index `0` or `1`. Returns element at that index. | `[10, 30]` | `{10: 0, 30: 1}` | `10` or `30` |

---

## Complexity Analysis

### Time Complexity

| Function | Average Time Complexity | Reason |
| --- | --- | --- |
| `insert` | $O(1)$ | Hash map lookup and vector `push_back()` both take $O(1)$ average time. |
| `remove` | $O(1)$ | Swapping with the last element and using `pop_back()` avoids array shifting, taking $O(1)$ time. |
| `getRandom` | $O(1)$ | Choosing a random index and looking it up in an array takes constant time. |

### Space Complexity

* **$O(N)$**: Where $N$ is the number of unique elements currently stored in the set. Both the `vector` and the `unordered_map` store at most $N$ elements.
