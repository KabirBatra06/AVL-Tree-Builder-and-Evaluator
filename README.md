## GOAL
This code is an implementation of a self-balancing binary search tree (BST) using the AVL (Adelson-Velsky and Landis) tree rotation techniques.

## Components

- Structures and Global Definitions:

  Tnode: Represents a node in the AVL tree, storing an integer key, pointers to left and right children, and a balance factor.
  HBT_MAX and HBT_MIN: Define maximum and minimum key values for the tree.

- Utility Functions:

  new_node: Allocates memory for a new node and initializes it with the given key.\
  delete_tree: Recursively deletes all nodes in the tree.\
  height_calc: Calculates the height of a given node.\
  clockwise_rotate and counter_clockwise_rotate: Perform single rotation operations for balancing the tree.\
  inorder_predecessor_prev: Finds the inorder predecessor of a given node.\
  balancer: Balances the AVL tree after deletion operations.

- Insertion Function (insert):

  Inserts a new node into the AVL tree while maintaining balance.
  Adjusts balance factors and performs rotations if necessary.

- Deletion Function (delete):

  Deletes a node from the AVL tree while maintaining balance.
  Handles cases where the node has zero, one, or two children, adjusting the tree structure and performing rotations if needed.

- File I/O Functions:
  
  create_tree_from_file: Reads instructions from a file (containing keys and operations) and builds/alters the AVL tree accordingly.\
  print: Writes the keys and child relations of each node in the tree to a file.
