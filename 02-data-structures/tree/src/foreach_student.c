#include "tree.h"



ssize_t foreach_student(struct tree *tree, uint32_t from, uint32_t till,
                        void callback(struct student *, void *userdata), 
                        void *userdata)
{
    if(tree == NULL || (from > till) || callback == NULL)
    {
        errno = EINVAL;
        return -1;
    }

    ssize_t count = 0;
    void inorder_recursion(struct student *, uint32_t , uint32_t ,void (*)(struct student *, void *), void *, ssize_t * );  
    inorder_recursion(tree->root, from, till, callback, userdata, &count);
    return count;
}

void inorder_recursion(struct student *student, uint32_t from, uint32_t till,void (*callback)(struct student *, void *userdata), void *userdata, ssize_t *count)
{
    if(student->left != NULL) inorder_recursion(student->left, from, till, callback, userdata, count);
    
    if(student->student_number >= from && student->student_number <= till)
    {
        (*callback)(student, userdata);
        (*count)++;
    }
    if(student->right != NULL) inorder_recursion(student->right, from, till, callback, userdata, count);
}
