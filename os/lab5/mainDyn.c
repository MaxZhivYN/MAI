#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <dlfcn.h>

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
    Stack* (*stack_create)(size_t stack_size);
    int (*stack_push)(Stack *s, Item value);
    Item (*stack_pop)(Stack *s);
    bool (*stack_is_empty)(Stack *s);
    void (*stack_destroy)(Stack **s);
    void (*stack_print)(Stack *s);

    char *err;

    void *libHandle;
    libHandle = dlopen("./libbst.so", RTLD_LAZY);
    if (!libHandle) {
        fprintf(stderr, "%s\n", dlerror());
        exit(1);
    }

    stack_create = dlsym(libHandle, "stack_create");
    stack_push = dlsym(libHandle, "stack_push");
    stack_pop = dlsym(libHandle, "stack_pop");
    stack_is_empty = dlsym(libHandle, "stack_is_empty");
    stack_destroy = dlsym(libHandle, "stack_destroy");
    stack_print = dlsym(libHandle, "stack_print");

    if (err = dlerror()) {
        fprintf(stderr, "%s\n", err);
        exit(1);
    }

    Stack *s = (*stack_create)(1);
    int cmd;
    int input;
    print_help();
    
    while (scanf("%d", &cmd) == 1) {
        printf("\n");
        switch(cmd) {
            case 1:
                printf("Enter item: ");
                scanf("%d", &input);
                (*stack_push)(s, input);
                printf("Item added!\n\n");
                break;
            case 2:
                if (!( (*stack_is_empty)(s) )) {
                    (*stack_pop)(s);
                    printf("Item deleted!\n\n");
                }
                else 
                    printf("Stack is empty!\n\n");
                break;
            case 3:
                if (!( (*stack_is_empty)(s) )) {
                    printf("Stack: ");
                    (*stack_print)(s);
                    printf("\n");
                }
                else 
                    printf("Stack is empty!\n\n");        
                break;   
            case 4:
                (*stack_destroy)(&s);
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