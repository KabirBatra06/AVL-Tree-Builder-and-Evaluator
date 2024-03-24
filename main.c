#include "hbt.h"
#include <stdio.h>
#include <stdlib.h>
#include "buildtree.h"
#include "evaluate.h"

int main(int argc, char *argv[])
{

    if ((argc != 4 || argv[1][0] != '-' || argv[1][1] != 'b' || argv[1][2] != '\0') && (argc != 3 || argv[1][0] != '-' || argv[1][1] != 'e' || argv[1][2] != '\0'))
    {
        return EXIT_FAILURE;
    }

    Tnode* root = NULL;

    if(argv[1][0] == '-' && argv[1][1] == 'b')
    {
        FILE* file = fopen(argv[2], "rb");
        if(file == NULL)
        {
            printf("%d\n", -1);
            return EXIT_FAILURE;
        }

        if(create_tree_from_file(file, &root))
        {
            printf("%d\n", 0);
            FILE* file2 = fopen(argv[3], "wb");
            if(file2 == NULL)
            {
                delete_tree(root);
                return EXIT_FAILURE;
            }
            print(file2, root);
            fclose(file2);
            delete_tree(root);
            return EXIT_FAILURE;
        }

        fclose(file);

        FILE* file2 = fopen(argv[3], "wb");
        if(file2 == NULL)
        {
            delete_tree(root);
            return EXIT_FAILURE;
        }
        print(file2, root);
        fclose(file2);
        printf("%d\n", 1);
        delete_tree(root);
        return EXIT_SUCCESS;
    }
    else if(argv[1][0] == '-' && argv[1][1] == 'e')
    {
        if(valid_tree_check(argv[2]))
        {
            delete_tree(root);
            return EXIT_SUCCESS;
        }
        delete_tree(root);
        return EXIT_FAILURE;
    }
    
    return EXIT_FAILURE;
}