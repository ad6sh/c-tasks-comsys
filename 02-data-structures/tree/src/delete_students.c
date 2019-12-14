#include "tree.h"

void delete_students(struct tree *tree)
{
    if(tree != NULL)
    {
        struct student * root = tree->root;
        void postorder_delete(struct student *, struct tree *);
        postorder_delete(root, tree);
        init_tree(tree);
    }
    
}

void postorder_delete(struct student * node, struct tree * tree)
{
    if(node->left != NULL) postorder_delete(node->left, tree);
    if(node->right != NULL) postorder_delete(node->right, tree);
    free(node);
    tree->n_students --;

}

