# Abstract Data (In Raw C)

**Abstract Data** is a self-contained C library that implements common data structures inspired by the C++ STL (Standard Template Library), but using only raw C — no macros, no generic tricks, and no dependencies beyond the C standard library.

This project is built with a systems programming mindset and focuses on:
- memory safety
- API clarity
- encapsulation and modularity
- production-grade error handling

> goal: build a reusable, testable, and efficient container library that mimics the behavior of STL containers like `vector`, `list`, `deque`, `stack`, `priority_queue`, `map`, and `set` — all in portable C.

---

## 🧱 Containers Overview (ordered by priority)

| Container             | Status     | Backing / Strategy               | Priority | Notes |
|-----------------------|------------|----------------------------------|----------|-------|
| `dynamic_array`       | ✅ Done    | raw buffer                       | ✅ High  | STL equivalent: `std::vector` |
| `stack`               | ✅ Done    | based on `dynamic_array`         | ✅ High  | LIFO container |
| `queue`               | ✅ Done    | based on singly list             | ✅ High  | FIFO container |
| `heap`                | ✅  Done   | based on `dynamic_array`         | ✅ High  | sorting, greedy algorithms |
| `priority_queue`      | ✅  Done   | binary heap (min/max)            | ✅ High  | scheduling, greedy algorithms |
| `hash_map`            | ⏳ Planned | open addressing / chaining       | ✅ High  | key-value store |
| `hash_set`            | ⏳ Planned | open addressing / chaining       | ✅ High  | fast unique set |
| `set`                 | ⏳ Planned | backed by hash map or tree       | ✅ High  | interview classic |
| `disjoint_set`        | ⏳ Planned | array with parent + rank         | ✅ High  | union-find, graph problems |
| `lru_cache`           | ⏳ Planned | hash map + doubly list           | ✅ High  | systems, caching mechanism |
| `singly_list`         | ✅ Done    | node with `next` pointer         | ✅ High  | ownership & pointer practice |
| `doubly_list`         | ✅ Done    | node with `prev` and `next`      | ✅ High  | base for `deque`, `lru_cache` |
| `deque`               | ⏳ Planned | DLL or circular buffer           | 🔶 Medium| double-ended queue |
| `tree_map`            | ⏳ Planned | AVL / red-black tree             | 🔶 Medium| ordered map |
| `tree_set`            | ⏳ Planned | AVL / red-black tree             | 🔶 Medium| sorted unique values |
| `multiset`            | ⏳ Planned | backed by map with counters      | 🔶 Medium| allows duplicates |
| `ring_buffer`         | ⏳ Planned | fixed-size circular buffer       | 🔶 Medium| used in embedded/real-time |
| `allocator`           | ⏳ Planned | custom malloc/free wrappers      | 🔶 Medium| memory control & reuse |
| `pool_allocator`      | ⏳ Planned | fixed-size memory pool           | 🔶 Medium| performance boost, reuse |
| `segment_tree`        | ⏳ Planned | binary tree in flat array        | 🔶 Medium| range queries |
| `trie`                | ⏳ Planned | prefix tree                      | 🔽 Low   | strings, autocomplete |
| `bitset`              | ⏳ Planned | compact bool vector (bitmask)    | 🔽 Low   | memory efficient flags |
| `fenwick_tree (BIT)`  | ⏳ Planned | flat array with prefix sums      | 🔽 Low   | range-sum, log(n) |
| `graph`               | ⏳ Planned | adjacency list / matrix          | 🔽 Low   | BFS, DFS, algorithms |
| `matrix`              | ⏳ Planned | 2D index helpers on flat array   | 🔽 Low   | numerical, spatial cache |
| `ordered_set`         | ⏳ Planned | tree-based + rank ops            | 🔽 Low   | competitive programming |

---

## 📈 Sorting Algorithms (NEW)

| Algorithm           | Status     | Strategy / Type                  | Priority | Notes |
|---------------------|------------|----------------------------------|----------|-------|
| `bubble_sort`       | ✅ Done    | comparison, exchange             | ✅ High  | simple, educational |
| `insertion_sort`    | ⏳ Planned | comparison, insertion            | ✅ High  | efficient on nearly sorted data |
| `selection_sort`    | ⏳ Planned | comparison, selection            | ✅ High  | simple, inefficient |
| `merge_sort`        | ⏳ Planned | comparison, divide-and-conquer   | ✅ High  | stable, efficient, requires memory |
| `quick_sort`        | ⏳ Planned | comparison, divide-and-conquer   | ✅ High  | fast, in-place (usually) |
| `heap_sort`         | ⏳ Planned | comparison, selection            | ✅ High  | in-place, uses `heap` container |
| `shell_sort`        | ⏳ Planned | comparison, insertion variant    | 🔶 Medium| improvement on insertion sort |
| `counting_sort`     | ⏳ Planned | non-comparison, integer          | 🔶 Medium| linear time, for specific ranges |
| `radix_sort`        | ⏳ Planned | non-comparison, integer          | 🔶 Medium| sorts digit by digit |
| `bucket_sort`       | ⏳ Planned | non-comparison, distribution     | 🔶 Medium| for uniformly distributed data |
| `tim_sort`          | ⏳ Planned | hybrid (merge + insertion)       | 🔶 Medium| Python's standard sort |
| `introspective_sort`| ⏳ Planned | hybrid (quick + heap)            | 🔶 Medium| C++ `std::sort` |
| `tree_sort`         | ⏳ Planned | comparison, tree-based           | 🔽 Low   | uses a binary search tree |
| `cube_sort`         | ⏳ Planned | comparison, parallel-friendly    | 🔽 Low   | complex, academic |
| `external_sort`     | ⏳ Planned | for data larger than RAM         | 🔽 Low   | uses external storage (disk) |

---

## 🔧 Features

- generic: every container accepts element size at construction time
- oop-inspired design: each module exposes a clean C interface (`.h`) and hides internal implementation details
- robust error handling: all public functions return status codes (`OK`, `ERR`) or NULL, no `assert()`s in release code
- memory safe: no leaks, no double frees, no uninitialized access
- test-driven: each container has its own unit and stress tests
