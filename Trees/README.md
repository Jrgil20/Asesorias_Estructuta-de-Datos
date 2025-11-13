# Trees

This directory contains implementations of various tree data structures.

- **BST (Binary Search Tree)**: A simple tree structure where each node has at most two children, and the left child is less than the parent, and the right child is greater.
- **AVL Tree**: A self-balancing binary search tree. The heights of the two child subtrees of any node differ by at most one.
- **Red-Black Tree**: Another self-balancing binary search tree with slightly less strict balancing rules than AVL trees, resulting in faster insertions and deletions but slower lookups.
- **B-Tree**: A self-balancing tree that generalizes the binary search tree, allowing for nodes with more than two children. They are optimized for systems that read and write large blocks of data.

## Key Differences

| Tree Type       | Balance                               | Use Case                               | Complexity (Avg/Worst) |
|-----------------|---------------------------------------|----------------------------------------|------------------------|
| **BST**         | Not guaranteed (can become a list)    | Simple applications, educational       | O(log n) / O(n)        |
| **AVL**         | Strictly balanced                     | Search-intensive applications          | O(log n) / O(log n)    |
| **Red-Black**   | Loosely balanced                      | Insert/delete-intensive applications   | O(log n) / O(log n)    |
| **B-Tree**      | Balanced, optimized for block storage | Databases, file systems                | O(log n) / O(log n)    |

## Traversals

Common ways to visit all nodes in a tree:
- **In-order**: Left, Root, Right (results in sorted order for BSTs)
- **Pre-order**: Root, Left, Right
- **Post-order**: Left, Right, Root
