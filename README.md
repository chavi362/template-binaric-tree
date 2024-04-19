# Binary Search Tree (BST) Implementation

This project includes a C++ implementation of a Binary Search Tree (BST) along with utility classes for tree traversal and operations.
Overview

A Binary Search Tree (BST) is a type of binary tree where each node has at most two children, referred to as the left child and the right child. The key property of a BST is that for any node, the values in the left subtree are less than the node's value, and the values in the right subtree are greater than or equal to the node's value.

This project consists of the following components:

### Queue (Abstract Class):
Defines the interface for a queue data structure.
Provides abstract methods for basic queue operations such as enqueue, dequeue, front, isEmpty, and clear.

### Tree (Abstract Class):
Represents a binary tree with methods for tree traversal (pre-order, in-order, post-order) and utility operations (clear, height calculation, tree reflection, breadth-first scan).

### SearchTree (Derived Class):
Inherits from the Tree class to implement a Binary Search Tree (BST).
Provides methods to add, search for, remove, and find successors of values within the BST.
Includes a method to delete duplicate values from the BST.

### Node (Nested Class within Tree):
Represents a single node in the binary tree, containing a value and pointers to left and right children.
