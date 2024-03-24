#include "hbt.h"
#include <stdio.h>
#include <stdlib.h>

int is_height_balanced(Tnode* root);

int is_bst(Tnode* root);

int create_tree_to_eval(Tnode** root, FILE* fptr);

int valid_tree_check(char* filename);