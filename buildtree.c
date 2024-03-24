#include "hbt.h"
#include <stdio.h>
#include <stdlib.h>

Tnode* new_node(int key)
{
    Tnode* newele = malloc(sizeof(Tnode));

    if(!newele)
    {
        return NULL;
    }

    newele->key = key;
    newele->left = NULL;
    newele->right = NULL;
    newele->balance = 0;

    return newele;
}

void delete_tree(Tnode* root) 
{
    if (root == NULL) 
        return;
        
    delete_tree(root->left);
    delete_tree(root->right);

    free(root);
} 

int height_calc(Tnode* root)
{
    if(root == NULL)
    {
        return 0;
    }

    int left = height_calc(root->left);
    int right = height_calc(root->right);

    if(left >= right)
    {
        return (1 + left);
    }
    else
    {
        return (1 + right);
    }
}

Tnode* clockwise_rotate(Tnode* node)
{
    Tnode* ret_val = node->left;
    node->left = ret_val->right;
    ret_val->right = node;
    return ret_val;
}

Tnode* counter_clockwise_rotate(Tnode* node)
{
    Tnode* ret_val = node->right;
    node->right = ret_val->left;
    ret_val->left = node;
    return ret_val;
}

Tnode* inorder_predecessor_prev(Tnode* node)
{
    Tnode* retval;
    if(node->left != NULL)
    {
        retval = node->left;
        if(retval->right == NULL)
        {
            return node;
        }
        while(retval->right->right != NULL)
        {
            retval = retval->right;
        }
        return retval;
    }

    return NULL;
}

int insert(Tnode** root, int key)
{
    Tnode* yng_ancestor = *root; 
    Tnode* parent_yng_ancestor = NULL;
    Tnode* curr_node = *root;
    Tnode* parent_curr = NULL;
    Tnode* temp = NULL;
    Tnode* child = NULL;

    if(*root == NULL)
    {
        *root = new_node(key);
        return 0;
    }

    while(curr_node != NULL)
    {
        if(key <= curr_node->key)
        {
            temp = curr_node->left;
        }
        else
        {
            temp = curr_node->right;
        }

        if( (temp != NULL) && (temp->balance != 0) )
        {
            parent_yng_ancestor = curr_node;
            yng_ancestor = temp;
        }

        parent_curr = curr_node; // stores the node to which the new value should be added
        curr_node = temp;
    }

    temp = new_node(key);

    if(temp == NULL)
    {
        return 1;
    }

    if(parent_curr == NULL) // inserting first node
    {
        *root = temp;
    }
    else // inserting all other nodes
    {
        if(key <= parent_curr->key)
        {
            parent_curr->left = temp;
        }
        else
        {
            parent_curr->right = temp;
        }

    }

    curr_node = yng_ancestor;
    while(curr_node != temp)
    {
        if(key <= curr_node->key)
        {
            curr_node->balance += 1;
            curr_node = curr_node->left;
        }
        else
        {
            curr_node->balance -=1;
            curr_node = curr_node->right;
        }
    }

    if( (yng_ancestor->balance < 2) && (yng_ancestor->balance > -2))
    {
        return 0; 
    }

    if(key <= yng_ancestor->key)
    {
        child = yng_ancestor->left;
    }
    else
    {
        child = yng_ancestor->right;
    }

    if((yng_ancestor->balance == 2) && (child->balance == 1))
    {
        curr_node = clockwise_rotate(yng_ancestor);
        yng_ancestor->balance = 0;
        child->balance = 0;
    }

    if((yng_ancestor->balance == -2) && (child->balance == -1))
    {
        curr_node = counter_clockwise_rotate(yng_ancestor);
        yng_ancestor->balance = 0;
        child->balance = 0;
    }

    if((yng_ancestor->balance == 2) && (child->balance == -1))
    {
        yng_ancestor->left = counter_clockwise_rotate(child);
        curr_node = clockwise_rotate(yng_ancestor);

        if(curr_node->balance == 0)
        {
            yng_ancestor->balance = 0;
            child->balance = 0;
        }
        else
        {
            if(curr_node->balance == 1)
            {
                yng_ancestor->balance = -1;
                child->balance = 0;
            }
            else
            {
                yng_ancestor->balance = 0;
                child->balance = 1;
            }
            curr_node->balance = 0;
        }
    }
    if((yng_ancestor->balance == -2) && (child->balance == 1))
    {
        yng_ancestor->right = clockwise_rotate(child);
        curr_node = counter_clockwise_rotate(yng_ancestor);

        if(curr_node->balance == 0)
        {
            yng_ancestor->balance = 0;
            child->balance = 0;
        }
        else
        {
            if(curr_node->balance == -1)
            {
                yng_ancestor->balance = 1;
                child->balance = 0;
            }
            else
            {
                yng_ancestor->balance = 0;
                child->balance = -1;
            }
            curr_node->balance = 0;
        }
    }

    if(parent_yng_ancestor == NULL)
    {
        *root = curr_node;
    }
    else
    {
        if(key <= parent_yng_ancestor->key)
        {
            parent_yng_ancestor->left = curr_node;
        }
        else
        {
            parent_yng_ancestor->right = curr_node;
        }
    }

    return 0;
}



Tnode* balancer(Tnode* root)
{
    if(root == NULL)
    {
        return root;
    }
    
    root->right = balancer(root->right);

    if(!root)
    {
        return root;
    }

    root->balance = height_calc(root->left) - height_calc(root->right);
    int balance_used_left = 0;
    int balance_used_right = 0;

    //UPDATING BALANCE OF LEFT CHILD OF DELETED NODE
    if(root->left == NULL)
    {
        balance_used_left = 0;
    }
    else
    {
        root->left->balance = height_calc(root->left->left) - height_calc(root->left->right);
        balance_used_left = root->left->balance;
    }

    //UPDATING BALANCE OF RIGHT CHILD OF DELETED NODE
    if(root->right == NULL)
    {
            balance_used_right = 0;
    }
    else
    {
        root->right->balance = height_calc(root->right->left) - height_calc(root->right->right);
        balance_used_right = root->right->balance;
    }

    //ROTATIONS FOR BALANCING
    if(root->balance == 2 && balance_used_left >= 0)
    {
        return(clockwise_rotate(root));
    }
    if(root->balance == 2 && balance_used_left < 0)
    {
        root->left = counter_clockwise_rotate(root->left);
        return(clockwise_rotate(root));
    }
    if(root->balance == -2 && balance_used_right <= 0)
    {
        return(counter_clockwise_rotate(root));
    }
    if(root->balance == -2 && balance_used_right > 0)
    {
        root->right = clockwise_rotate(root->right);
        return(counter_clockwise_rotate(root));
    }

    return root;
    
}

Tnode* delete(Tnode* root, int delete_key)
{
    if(root == NULL)
    {
        return root;
    }
    if(root->key > delete_key)
    {
        root->left = delete(root->left, delete_key); 
    }
    else if(root->key < delete_key)
    {
        root->right = delete(root->right, delete_key);
    }
    else
    {
        //IF ROOT HAS NO LEFT CHILD
        if(root->left == NULL && root->right == NULL)
        {
            Tnode* temp = root;
            root = NULL;
            free(temp);
        }
        else if(root->left == NULL)
        {
            Tnode* temp = root->right;

            root->key = temp->key;
            root->left = temp->left;
            root->right = temp->right;

            free(temp);
        }
        // ELSE IF ROOT HAS NO RIGHT CHILD
        else if(root->right == NULL)
        {
            Tnode* temp = root->left;

            root->key = temp->key;
            root->left = temp->left;
            root->right = temp->right;
            
            free(temp);
        }
        // ELSE IF ROOT HAS 2 CHILDREN
        else
        {
            Tnode* prev = inorder_predecessor_prev(root);

            if(prev == root)
            {
                Tnode* temp = prev->left;
                temp->right = root->right;
                
                root->key = temp->key;
                root->left = temp->left;
                root->right = temp->right;

                free(temp);
            }
            else
            {
                Tnode* predecessor = prev->right;
                prev->right = predecessor->left;
                
                root->key = predecessor->key;

                root->left = balancer(root->left);
                free(predecessor); 
            }
        }

    }

    if(!root)
    {
        return root;
    }

    root->balance = height_calc(root->left) - height_calc(root->right);
    int balance_used_left = 0;
    int balance_used_right = 0;

    //UPDATING BALANCE OF LEFT CHILD OF DELETED NODE
    if(root->left == NULL)
    {
        balance_used_left = 0;
    }
    else
    {
        root->left->balance = height_calc(root->left->left) - height_calc(root->left->right);
        balance_used_left = root->left->balance;
    }

    //UPDATING BALANCE OF RIGHT CHILD OF DELETED NODE
    if(root->right == NULL)
    {
        balance_used_right = 0;
    }
    else
    {
        root->right->balance = height_calc(root->right->left) - height_calc(root->right->right);
        balance_used_right = root->right->balance;
    }

    //ROTATIONS FOR BALANCING
    if(root->balance == 2 && balance_used_left >= 0)
    {
        return(clockwise_rotate(root));
    }
    if(root->balance == 2 && balance_used_left < 0)
    {
        root->left = counter_clockwise_rotate(root->left);
        return(clockwise_rotate(root));
    }
    if(root->balance == -2 && balance_used_right <= 0)
    {
        return(counter_clockwise_rotate(root));
    }
    if(root->balance == -2 && balance_used_right > 0)
    {
        root->right = clockwise_rotate(root->right);
        return(counter_clockwise_rotate(root));
    }

    return root;
}

int create_tree_from_file(FILE* file, Tnode** root)
{

    int key;
    char instruction; 

    while(fread(&key, sizeof(int), 1, file))
    {
        // EXIT AT INVALIID KEY
        if(key > HBT_MAX || key < HBT_MIN)
        {
            return 1;
        }

        fread(&instruction, sizeof(char), 1, file);

        if(instruction == 'i')
        {
            if(insert(root, key))
            {
                return 1;
            }
        }
        else if(instruction == 'd')
        {
            *root = delete(*root, key);
        }
        else
        {
            //EXIT AT INVALID OPERATION
            return 1;
        }
    }

    return 0;
}

void print(FILE* file, Tnode* root)
{
    if (root == NULL)
    {
        return;
    }

    char lft = 2;
    char rht = 1;
    char empt = 0;
    char both = 3;

    int key = root->key;

    fwrite(&(key), sizeof(int), 1, file);

    if(root->left != NULL && root->right != NULL)
    {
        fwrite(&both, sizeof(char), 1, file);
    }
    else if(root->right == NULL && root->left != NULL)
    {
        fwrite(&lft, sizeof(char), 1, file);
    }
    else if(root->right != NULL && root->left == NULL)
    {
        fwrite(&rht, sizeof(char), 1, file);
    }
    else if(root->right == NULL && root->left == NULL)
    {
        fwrite(&empt, sizeof(char), 1, file);
    }
    
    print(file, root->left);

    print(file, root->right);
}