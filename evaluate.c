#include "hbt.h"
#include <stdio.h>
#include <stdlib.h>
#include "buildtree.h"

int is_height_balanced(Tnode* root)
{
    int left_height;
    int right_height;
    int diff;

    if(root == NULL)
    {
        return 1;
    }

    left_height = height_calc(root->left);
    right_height = height_calc(root->right);

    diff = left_height - right_height;

    if((diff > -2 && diff < 2) && is_height_balanced(root->left) && is_height_balanced(root->right))
    {
        return 1;
    }

    return 0;
}

int is_bst(Tnode* root)
{
    if (root == NULL)
    {
        return 1;
    }

    if (root->left != NULL && root->left->key > root->key)
    {
        return 0;
    }

    if (root->right != NULL && root->right->key < root->key)
        return 0;
 
    if (is_bst(root->right) == 0 || is_bst(root->left) == 0)
    {
        return 0;
    }

    return 1;
}

int create_tree_to_eval(Tnode** root, FILE* fptr)
{
    int key;
    char branches;
    int retval = 0;

    fread(&key, sizeof(int),1, fptr);
    fread(&branches, sizeof(char), 1, fptr);

    if((int)branches > 3 || (int)branches < 0 || key > HBT_MAX || key < HBT_MIN)
    {
        return 1;
    }

    *root = new_node(key);

    if((int)branches == 3 || (int)branches == 2)
    {
        retval += create_tree_to_eval(&((*root)->left), fptr);
    }

    if((int)branches == 3 || (int)branches == 1)
    {
        retval += create_tree_to_eval(&((*root)->right), fptr);
    }

    return retval; 
}

int valid_tree_check(char* filename)
{
    Tnode* root = NULL;
    int valid_file;
    int valid_bst = -1;
    int valid_balance = -1;
    int size;
    int valid_size;

    FILE* file = fopen(filename, "rb");

    // RETURN 0 IF NO FILE EXISTS
    if(file == NULL)
    {
        valid_file = -1;
        printf("%d,%d,%d\n", valid_file, valid_bst, valid_balance);
        return 0;
    }

    fseek(file, 0, SEEK_END);
    size = ftell(file);
    rewind(file);

    valid_size = size % (sizeof(char) + sizeof(int));

    // RETURN 0 IF FILE DOES NOT HAVE CORRECT NUMBER OF KEY INSTRUCTION PAIRS
    if(valid_size != 0)
    {
        return 0;
    }
    
    // RETURN 0 IF INVALID KEY OR INSTRUCTION IS ENCOUNTERED
    if(create_tree_to_eval(&root, file) != 0)
    {
        valid_file = 0;
        printf("%d,%d,%d\n", valid_file, valid_bst, valid_balance);
        return 0;
    }

    valid_file = 1;
    valid_bst = is_bst(root);
    valid_balance = is_height_balanced(root);

    printf("%d,%d,%d\n", valid_file, valid_bst, valid_balance);
    delete_tree(root);
    return 1;
}