#include <stdio.h>
#include <stdbool.h>

#include "bst.h"


void print_help() {
    printf("Menu: \n");
    printf("1: Add elem \n");
    printf("2: Delete elem \n");
    printf("3: Print \n");
    printf("4: Exit \n");
    printf("Your choice: ");
}


int main()
{

    Stack *s = stack_create(1);
    int cmd;
    int input;
    print_help();
    
    while (scanf("%d", &cmd) == 1) {
        printf("\n");
        switch(cmd) {
            case 1:
                printf("Enter item: ");
                scanf("%d", &input);
                stack_push(s, input);
                printf("Item added!\n\n");
                break;
            case 2:
                if (!stack_is_empty(s)) {
                    stack_pop(s);
                    printf("Item deleted!\n\n");
                }
                else 
                    printf("Stack is empty!\n\n");
                break;
            case 3:
                if (!stack_is_empty(s)) {
                    printf("Stack: ");
                    stack_print(s);
                    printf("\n");
                }
                else 
                    printf("Stack is empty!\n\n");        
                break;   
            case 4:
                stack_destroy(&s);
                printf("Stack destroyed\n");
                free(s);
                return 0;
            default:
                printf("Incorrect command\n\n");
                break;
        }
        print_help();
    }
}