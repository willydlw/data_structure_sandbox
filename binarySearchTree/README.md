# Binary Search Tree 

A Binary Search Tree is a special form of a binary tree. The value in each node must be greater than (or equal to) any values in its left subtree but less than (or equal to) any values in its right subtree.


## Definition

A binary search tree (BST), a special form of a binary tree, satisfies the binary search property:

1. The value in each node must be greater than (or equal to) any values stored in its left subtree.
2. The value in each node must be less than (or equal to) any values stored in its right subtree.


## Basic Operations 

- Search
- Insertion
- Deletion

### Search

Search for a target value in the tree. 

1. return the node if the target value is equal to the value of the node.
2. continue searching in the left subtree if the target value is less than the value of the node.
3. continue searching in the right subtree if the target value is greater than the value of the node.


### Insertion 

Insert a new node by minimizing the number of changes to the tree. The tree is traversed to find the proper leaf position for the target node and insert it as a leaf.

1. Search the left or right subtrees according to the relation of the value of the node and the target node value.
2. Repeat step 1 until reaching an external leaf node.
3. Add the new node as its left or right child depending on the relation of the value of the node and the value of the target node.

Note: do not add the node if it already exists in the tree.


## Deletion

The implementation will minimize changes to the BST. The solution is to replace the target node with a proper child. According to the number of its children, we should consider three different cases:

1. Target has no children. Remove the child.
2. Target has one child 
3. Target has two children


Given a root node reference of a BST and a key, delete the node with the given key in the BST. Return the root node reference (possibly updated) of the BST.

1. Search for the node.
2. If the node is found.


## Inorder Successor 

Given the root of a binary search tree and a node p in it, return the in-order successor of that node in the BST. If the given node has no in-order successor in the tree, return null.

The successor of a node p is the node with the smallest key greater than p.val.



### References:

https://www.enjoyalgorithms.com/blog/insertion-in-binary-search-tree


