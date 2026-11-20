# C data structures and algorithms

Implementations of classic abstract data types and algorithms in C, each with its own `test.c`. Coursework for Algorithms and Data Structures at TU Košice.

| Folder | Topic |
|---|---|
| `01-02_RAM` | Programs for a RAM machine (sum, max, exp) |
| `03_llist` | Linked list |
| `04_lstack`, `04_lqueue` | Stack and queue on linked lists (+ a formal queue specification in mCRL2) |
| `05_tree_arr`, `05_graph` | Array-based tree, graph |
| `06_traverse` | Graph/tree traversal |
| `08_dnc_dp` | Divide and conquer, dynamic programming (Fibonacci, binomial coefficients, min/max, matrices) |
| `09_sort1`, `10_sort2` | Quicksort, heapsort, radix sort |
| `10_hashtable` | Hash table |
| `11_BVS` | Binary search tree |

## Build and test

Most folders are self-contained:

```bash
cd 03_llist
gcc -Wall -Wextra -o test test.c llist.c && ./test
```

## Notes

- `05_graph` needs the queue implementation from `04_lqueue`: `gcc test.c graph.c ../04_lqueue/lqueue.c`.
- `10_sort2` links with its own `lqueue.c`: `gcc test.c radix.c lqueue.c`.
- `10_hashtable`: `gcc test.c hashtable.c`.

## License

MIT, see [LICENSE](LICENSE).
