#include "tree.h"

int insert_student(struct tree *tree, struct student *student)
{
    if(tree == NULL || student == NULL || student->name == NULL)
    {
        errno = EINVAL;
        return -1;
    }
    else
    {
        if(tree->n_students == 0)
        {
            tree->root = student;
            tree->n_students++;            
            return 0;
        }
        else 
        {
            struct student *place_to_insert = tree->root;            
            struct student *place_to_insert_parent = tree->root;
            while (place_to_insert != NULL)
            {
                if(place_to_insert->student_number == student->student_number)
                {
                    strcpy(place_to_insert->name, student->name);
                    return 0;
                }
                place_to_insert_parent = place_to_insert;
                if(student->student_number < place_to_insert->student_number)
                {
                    place_to_insert = place_to_insert->left;
                }
                else 
                {
                    place_to_insert = place_to_insert->right;
                }

            }
            if(student->student_number < place_to_insert_parent->student_number)
            {
                place_to_insert_parent->left = student;
                tree->n_students++;
                return 0;
            }
            else
            {
                place_to_insert_parent->right = student;
                tree->n_students++;
                return 0;
            }
            

        }
    }
}



    