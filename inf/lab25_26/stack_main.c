#include <stdio.h>
#include <stdbool.h>

#include "stack_array.h"
#include "sort.h"


int main()
{
    int size1, size2;
    printf("Insert size of memory 1: ");
    scanf("%d", &size1);
    printf("Insert size of memory 2: ");
    scanf("%d", &size2);
    Stack *s1 = stack_create(size1);
    Stack *s2 = stack_create(size2);
    int massiv[size1];
    int cmd;
    int a = 0;
    int *i;
    i = &a;
    print_help();

    int input;
    int work = 1;

    while (work && scanf("%d", &cmd) == 1) {
        switch(cmd) {
            case 1:
                scanf("%d", &input);
                stack_push(s1, input);
                break;
            case 2:
                stack_pop(s1);
                break;
            case 3:
                printf("op ");
                stack_sort2(s1);
                printf("ol ");
                break;
            case 4:
                unctionm(s1, s2);
                break;
            case 5:
                create_massiv(s1, massiv, i);
                quickSort(massiv, 0, a - 1);
                stack_form_massiv(massiv, s1, a);
                break;
            case 6:
                stack_print(s1);
                stack_print(s2);
                break;   
            case 7:
                work = false;
                break;
            case 8:
                print_help();
                break;
            case 9:
                scanf("%d", &input);
                stack_push(s2, input);
                break;
            case 10:
                stack_pop(s2);
                break;
            case 11:
                printf("op ");
                stack_sort2(s1);
                printf("ol ");
                stack_print(s1);
                break;
        }
    }
    stack_destroy(&s1);
    stack_destroy(&s2);
}