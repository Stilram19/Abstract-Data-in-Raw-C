# Abstract Data (In Raw C)

**Abstract Data** is a self-contained C library that implements common data structures inspired by the C++ STL (Standard Template Library), but using only raw C — no macros, no generic tricks, and no dependencies beyond the C standard library.

This project is built with a systems programming mindset and focuses on:
- **Memory safety**
- **API clarity**
- **Encapsulation and modularity**
- **Production-grade error handling**

> Goal: Build a reusable, testable, and efficient container library that mimics the behavior of STL containers like `vector`, `list`, `deque`, `stack`, `priority_queue`, `map`, and `set` — all in portable C.

---

## 🧱 Containers Overview

| Container             | Status     | Backing / Strategy                | Priority | Notes |
|-----------------------|------------|----------------------------------|----------|-------|
| `dynamic_array`       | ✅ Done    | Raw buffer                        | ✅ High  | STL equivalent: `std::vector` |
| `singly_list`         | ✅ Done    | Node with `next` pointer          | ✅ High  | Learn ownership and pointer manipulation |
| `doubly_list`         | ⏳ Planned | Node with `prev` and `next`       | ✅ High  | Needed for `deque`, `stack`, `queue` |
| `stack`               | ⏳ Planned | Based on `dynamic_array` or list  | ✅ High  | LIFO container |
| `queue`               | ⏳ Planned | Based on list or circular buffer  | ✅ High  | FIFO container |
| `deque`               | ⏳ Planned | DLL or circular array             | ✅ Medium| Double-ended queue |
| `ring_buffer`         | ⏳ Planned | Fixed-size circular buffer        | 🔶 Medium| Useful in real-time systems |
| `priority_queue`      | ⏳ Planned | Binary heap (min/max)             | ✅ High  | Heap-based, used in scheduling algorithms |
| `hash_map`            | ⏳ Planned | Open addressing / chaining        | ✅ High  | Collision resolution + resizing |
| `hash_set`            | ⏳ Planned | Open addressing / chaining        | ✅ High  | Set semantics, no duplicates |
| `tree_map`            | ⏳ Planned | AVL / Red-Black Tree              | 🔶 Medium| Keeps keys sorted |
| `tree_set`            | ⏳ Planned | AVL / Red-Black Tree              | 🔶 Medium| Sorted unique values |
| `trie`                | ⏳ Planned | Prefix tree                       | 🔽 Low   | For strings / autocomplete |
| `bitset`              | ⏳ Planned | Compact bool vector (bitmask)     | 🔽 Low   | Useful for memory efficiency |
| `allocator`           | ⏳ Planned | Custom malloc/free wrappers       | 🔶 Medium| For custom memory management |
| `pool_allocator`      | ⏳ Planned | Fixed-size memory pool            | 🔶 Medium| Fast object reuse |
| `graph`               | ⏳ Planned | Adjacency list / matrix           | 🔽 Low   | For algorithms practice |
| `matrix`              | ⏳ Planned | 2D index helpers on flat array    | 🔽 Low   | Cache-aware numerical layout |
| `set`                 | ⏳ Planned | Backed by hash map or tree        | ✅ High  | Enforces unique elements |
| `multiset`            | ⏳ Planned | Backed by map with counters       | 🔶 Medium| Allows duplicates |
| `disjoint_set`        | ⏳ Planned | Array with parent + rank          | ✅ High  | Used in graph algorithms |
| `segment_tree`        | ⏳ Planned | Binary tree in flat array         | 🔶 Medium| Range queries: sum, min, max |
| `fenwick_tree` (BIT)  | ⏳ Planned | Flat array with prefix sums       | 🔽 Low   | Efficient range-sum with less space |
| `ordered_set`         | ⏳ Planned | Tree-based + rank functionality   | 🔽 Low   | Used in competitive programming |

---

## 🔧 Features

- **Generic**: Every container accepts element size at construction time.
- **OOP-inspired design**: Each module exposes a clean C interface (`.h`) and hides internal implementation details.
- **Robust error handling**: All public functions return status codes (`OK`, `ERR`) or NULL, no `assert()`s in release code.
- **Memory safe**: No leaks, no double frees, no uninitialized access.
- **Test-driven**: Each container has its own unit and stress tests.
