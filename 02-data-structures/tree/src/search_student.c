#include "tree.h"

struct student * search_student(struct tree *tree, uint32_t number)
{
    struct student *result;
    if(tree == NULL || tree->n_students == 0)
    {
        errno = EINVAL;
        return NULL;
    }
    else
    {
        result = tree->root;

        while(result != NULL)
        {
            if(result->student_number == number)
            {
                return result;
            }
            else if(number < result->student_number)
            {
                result = result->left;
            }
            else if(number > result->student_number)
            {
                result = result->right;
            }
        }
        errno = ENOKEY;
        return NULL;
    }
    
}