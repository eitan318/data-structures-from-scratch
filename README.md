# ds — Data Structures from Scratch

A header-only C++17 library of classical data structures, written from the
ground up for clarity and learning. Every container lives in a single header
under `include/ds/`, has Doxygen documentation, and ships with a runnable
example.

## Layout

```
.
├── include/ds/        # the library — one header per data structure
├── examples/          # one runnable example per header
├── CMakeLists.txt     # builds the examples and the docs target
├── Doxyfile           # doxygen configuration
└── README.md
```

## Data structures

| Header                              | Class                          | Notes                                    |
| ----------------------------------- | ------------------------------ | ---------------------------------------- |
| `array.hpp`                         | `Array<T>`                     | Fixed-size, bounds-checked               |
| `dynamic_array.hpp`                 | `DynamicArray<T>`              | Growable; doubles / halves capacity      |
| `bit_array.hpp`                     | `BitArray`                     | 1 bit per element, packed into 64-bit words |
| `singly_linked_list.hpp`            | `SinglyLinkedList<T>`          | Head + tail pointers                     |
| `doubly_linked_list.hpp`            | `DoublyLinkedList<T>`          | O(n/2) random access                     |
| `circular_linked_list.hpp`          | `CircularLinkedList<T>`        | Singly linked ring                       |
| `doubly_circular_linked_list.hpp`   | `DoublyCircularLinkedList<T>`  | Doubly linked ring                       |
| `stack.hpp`                         | `Stack<T>`                     | Array-backed LIFO                        |
| `queue.hpp`                         | `Queue<T>`                     | Ring-buffer FIFO                         |
| `binary_heap.hpp`                   | `BinaryHeap<T, Compare>`       | Min-heap by default                      |
| `priority_queue.hpp`                | `PriorityQueue<T, Compare>`    | Max-priority queue over `BinaryHeap`     |
| `binary_tree.hpp`                   | `BinaryTree<T>`                | Level-order insert + 4 traversals        |
| `binary_search_tree.hpp`            | `BinarySearchTree<T, Compare>` | Unbalanced BST                           |

## Complexity reference

| Operation                  | Array | DynamicArray | LinkedList\* | Stack | Queue | Heap / PQ | BST (avg / worst) |
| -------------------------- | :---: | :----------: | :----------: | :---: | :---: | :-------: | :---------------: |
| Access by index            | O(1)  | O(1)         | O(n)         | top: O(1) | front/back: O(1) | top: O(1) | —                 |
| Insert at end              | —     | O(1) amortised | O(1)       | O(1) amortised | O(1) amortised | O(log n) | O(log n) / O(n) |
| Insert at arbitrary pos.   | —     | O(n)         | O(n)         | —     | —     | —         | O(log n) / O(n)   |
| Remove                     | —     | O(n)         | O(n)         | O(1)  | O(1)  | O(log n)  | O(log n) / O(n)   |
| Search                     | O(n)  | O(n)         | O(n)         | —     | —     | —         | O(log n) / O(n)   |

\* doubly linked variants are O(n/2) for indexed access.

## Build & run

The library itself needs no building — just add `include/` to your include
path. To compile the examples and generate documentation:

```sh
cmake -B build
cmake --build build
./build/examples/example_binary_search_tree
```

To regenerate the API docs (requires `doxygen`):

```sh
cmake --build build --target docs
# open docs/html/index.html
```

## Using the library in your own project

```cpp
#include "ds/binary_search_tree.hpp"

int main() {
    ds::BinarySearchTree<int> bst;
    for (int x : {5, 2, 8, 1, 3}) bst.insert(x);
    bst.in_order([](int x) { std::cout << x << ' '; });
}
```

All containers live in the `ds::` namespace and follow the same conventions:

- snake_case method names (`push_back`, `pop_front`, `for_each`),
- `size()` / `empty()` / `at()` mirror the standard library where it makes sense,
- bounds-violating operations throw `std::out_of_range`,
- copy is deleted (the structures own raw resources); move is supported.

## Design notes

- **Header-only.** Every type is templated, so the implementation lives in
  the header. No separate `.cpp` files to compile.
- **No virtual interfaces.** The earlier draft used `IList` / `IQueue` /
  `IBinaryTree` base classes. They constrained signatures (e.g. forced
  function-pointer printing) without giving any genuine polymorphism, so
  they were removed.
- **Minimal surface area.** Each structure exposes only what is essential to
  understand it; helpers from `<algorithm>` or `<vector>` are used only
  where re-implementing them would add noise without insight (e.g. the heap
  storage uses `std::vector`).

## License

MIT — see `LICENSE`.
