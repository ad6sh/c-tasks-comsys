#include "tree.h"

void init_tree(struct tree *tree)
{
    if (tree != NULL)
    {
        tree->root = NULL;
        tree->n_students = 0;
    }
}