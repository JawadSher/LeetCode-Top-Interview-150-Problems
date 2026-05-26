<div align="center">

# LEETCODE TOP INTERVIEW 150 PROBLEMS

### 🔥 A focused journey through the most important interview problems — one topic at a time.

[![License](https://img.shields.io/github/license/JawadSher/LeetCode-Top-Interview-150-Problems)](LICENSE)
[![Problems](https://img.shields.io/badge/problems-150-orange?logo=leetcode)](https://leetcode.com/studyplan/top-interview-150/)
[![Status](https://img.shields.io/badge/status-in--progress-yellow)](https://github.com/JawadSher/LeetCode-Top-Interview-150-Problems)
[![Language](https://img.shields.io/badge/language-C++-blue?logo=cplusplus)](https://isocpp.org/)
[![Study Plan](https://img.shields.io/badge/LeetCode-Top%20Interview%20150-brightgreen?logo=leetcode)](https://leetcode.com/studyplan/top-interview-150/)
[![Last Commit](https://img.shields.io/github/last-commit/JawadSher/LeetCode-Top-Interview-150-Problems)](https://github.com/JawadSher/LeetCode-Top-Interview-150-Problems/commits/main)
[![Difficulty](https://img.shields.io/badge/difficulty-Easy%20%7C%20Medium%20%7C%20Hard-red)](https://leetcode.com/studyplan/top-interview-150/)

</div>

---

## 📖 Introduction

Welcome to my **LeetCode Top 150 Questions** repository!

Two years ago, I spent 7–8 months grinding through the complete DSA series by **Love Babbar** and built an entire [DSA repository](https://github.com/JawadSher/DSA-LeetCode-GFG-Problems-Repository) from scratch — covering everything from arrays to graphs. It was a big effort, and I'm proud of it.

After stepping away from DSA for a while, I still remember the *names* — linked lists, graphs, trees, DP — but the *muscle memory* to implement them has gotten rusty. That's completely normal. The knowledge never disappears; it just needs to be re-activated.

So I decided to go through the **LeetCode Top Interview 150** study plan — a curated set of 150 problems that covers every critical data structure and algorithm pattern asked at top tech companies (Google, Amazon, Meta, Microsoft, etc.).

**Goal:** Complete all 150 problems in **15–20 days**, organized by topic, and documented here.

---

## 🧠 How to Recall DSA Fast (After a Long Break)

> If you're coming back to DSA after months or years, don't try to "re-learn" everything. Just **re-expose** yourself.

Here's what works best:

**1. Don't Start from Scratch — Start from Patterns**
Every DSA problem fits a pattern (two pointers, sliding window, BFS/DFS, etc.). Focus on recognizing the pattern, not memorizing the code.

**2. Read Your Old Code First**
Before solving a new problem on a topic, look at 1–2 problems you solved before in your old repo. Even 5 minutes of reading old solutions wakes up your memory faster than 30 minutes of re-reading theory.

**3. The 3-Step Method Per Problem**
- **5 min** — Try to brute-force it mentally (don't code yet)
- **10 min** — Look at the approach/hint if stuck (not the full solution)
- **Code it** — Then optimize

**4. Draw It, Don't Just Read It**
For trees, graphs, and linked lists — draw the structure on paper/whiteboard first. Visual memory reconnects faster than abstract reading.

**5. Keep a "Pattern Notebook"**
After each topic, write 2–3 lines: *"Two Pointers = shrink window from both ends when condition fails."* These micro-notes act as fast recall triggers.

**6. Spaced Repetition**
After finishing a topic, revisit its first problem 2 days later. This locks it in. Tools like Anki or even a simple checklist work great.

**7. Time-Box Each Session**
90-minute focused sessions beat 4-hour drifting. Set a timer. One topic per session.

---

## 📂 Repository Content

> Each folder follows the structure: `Problem Name / solution.cpp + README.md`

| # | Topic | Problems | Key Concepts to Recall |
|---|-------|----------|------------------------|
| 01 | [Array & String](#) | 13 | Two pointers, prefix sum, in-place ops |
| 02 | [Two Pointers](#) | 4 | Converging / fast-slow pointer tricks |
| 03 | [Sliding Window](#) | 4 | Variable/fixed window, frequency maps |
| 04 | [Matrix](#) | 4 | Row-col traversal, spiral, rotation |
| 05 | [HashMap](#) | 7 | Collision, grouping, frequency counting |
| 06 | [Intervals](#) | 5 | Sort by start, merge overlaps, greedy |
| 07 | [Stack](#) | 5 | Monotonic stack, bracket matching |
| 08 | [Linked List](#) | 11 | Dummy node, fast/slow ptr, reversal |
| 09 | [Binary Tree General](#) | 9 | Recursion, inorder/preorder/postorder |
| 10 | [Binary Tree BFS](#) | 3 | Queue-based level order traversal |
| 11 | [Binary Search Tree](#) | 3 | BST property: left < root < right |
| 12 | [Graph General](#) | 4 | Adjacency list, DFS/BFS templates |
| 13 | [Graph BFS](#) | 3 | Shortest path, multi-source BFS |
| 14 | [Trie](#) | 2 | Insert/search with children array |
| 15 | [Backtracking](#) | 7 | Choose-Explore-Unchoose pattern |
| 16 | [Divide & Conquer](#) | 3 | Merge sort style, recursive halving |
| 17 | [Kadane's Algorithm](#) | 2 | Max subarray, local vs global max |
| 18 | [Binary Search](#) | 7 | lo/hi/mid, search on answer space |
| 19 | [Heap](#) | 6 | Min-heap, max-heap, top-K problems |
| 20 | [Bit Manipulation](#) | 5 | XOR tricks, bit masking, count bits |
| 21 | [Math](#) | 3 | Modular arithmetic, digit ops |
| 22 | [1D Dynamic Programming](#) | 8 | Memoization → tabulation |
| 23 | [Multidimensional DP](#) | 7 | 2D grid DP, string DP |

---

## 📁 Project Structure

```
Leetcode-Top-150-Questions/
│
├── 01 - Array and String/
│   ├── 01 - Merge Sorted Array/
│   │   ├── solution.cpp
│   │   └── README.md
│   ├── 02 - Remove Element/
│   │   ├── solution.cpp
│   │   └── README.md
│   └── ...
│
├── 02 - Two Pointers/
│   ├── 01 - Valid Palindrome/
│   │   ├── solution.cpp
│   │   └── README.md
│   └── ...
│
├── 03 - Sliding Window/
│   └── ...
│
├── ... (and so on for all 23 topics)
│
├── LICENSE
└── README.md
```

---

## 🚀 Getting Started

```bash
# Clone the repository
git clone https://github.com/JawadSher/Leetcode-Top-150-Questions.git
cd Leetcode-Top-150-Questions
```

Browse by topic folder. Each problem folder contains:
- `solution.cpp` — my clean, commented C++ solution
- `README.md` — problem statement, approach explanation, time/space complexity

---

## 📅 Progress Tracker

| Day | Topics Covered | Problems Solved |
|-----|---------------|-----------------|
| 1   | Array & String (Part 1) | — |
| 2   | Array & String (Part 2) | — |
| 3   | Two Pointers + Sliding Window | — |
| 4   | Matrix + HashMap | — |
| 5   | Intervals + Stack | — |
| 6   | Linked List (Part 1) | — |
| 7   | Linked List (Part 2) | — |
| 8   | Binary Tree General | — |
| 9   | Binary Tree BFS + BST | — |
| 10  | Graph General + BFS | — |
| 11  | Trie + Backtracking | — |
| 12  | Divide & Conquer + Kadane's | — |
| 13  | Binary Search | — |
| 14  | Heap | — |
| 15  | Bit Manipulation + Math | — |
| 16  | 1D Dynamic Programming | — |
| 17  | Multidimensional DP | — |
| 18–20 | Revision + Remaining | — |

---

## 🔗 Resources

- 📌 [LeetCode Top Interview 150 Study Plan](https://leetcode.com/studyplan/top-interview-150/)
- 📌 [My Original DSA Repository (Love Babbar Series)](https://github.com/JawadSher/DSA-LeetCode-GFG-Problems-Repository)
- 📌 [Love Babbar DSA Series (YouTube)](https://www.youtube.com/c/LoveBabbar)
- 📌 [NeetCode YouTube (for pattern explanations)](https://www.youtube.com/@NeetCode)
- 📌 [CP-Algorithms Reference](https://cp-algorithms.com/)

---

## 📜 License

This project is licensed under the MIT License — see the [LICENSE](LICENSE) file for details.

---

## 🤝 Contributing

Contributions are welcome! If you have a better or alternate solution:

1. Fork the repository
2. Create a new branch: `git checkout -b better-solution`
3. Add your solution with comments
4. Commit: `git commit -m 'Add alternate solution for XYZ'`
5. Push and open a Pull Request

---

<div align="center">

*Built with persistence, caffeine, and the spirit of that 7-month DSA grind.* ☕

**Jawad Sher**

</div>
