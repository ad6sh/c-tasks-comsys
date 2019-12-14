#include "tree.h"


struct student * create_student(uint32_t number, const char *name)
{
    if(name != NULL)
    {
        struct student *student_node = malloc(sizeof(struct student));
        if(student_node == NULL)
        {
            errno = ENOMEM;
            return NULL;
        }
        else if(strlen(name) > (sizeof(student_node->name)-1))
        {
            //printf("test\n");
            errno = EINVAL;
            return NULL;
        }
        else
        {
            strcpy(student_node->name,name);
            student_node->student_number = number;
            student_node->left = NULL;
            student_node->right = NULL;
            return student_node;
        }
        
       
    }
    else 
    {
        errno = EINVAL;
        return NULL;
    }    
}