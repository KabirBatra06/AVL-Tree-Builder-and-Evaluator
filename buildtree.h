#include "hbt.h"
#include <stdio.h>
#include <stdlib.h>

Tnode* new_node(int key);

void delete_tree(Tnode* root);

int height_calc(Tnode* root);

Tnode* clockwise_rotate(Tnode* node);

Tnode* counter_clockwise_rotate(Tnode* node);

Tnode* inorder_predecessor_prev(Tnode* node);

int insert(Tnode** root, int key);

Tnode* balancer(Tnode* root);

Tnode* delete(Tnode* root, int delete_key);

int create_tree_from_file(FILE* file, Tnode** root);

void print(FILE* file, Tnode* root);