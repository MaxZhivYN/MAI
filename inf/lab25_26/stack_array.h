#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include <stdbool.h>

typedef int Item;

typedef struct {
	int ptr;
	int size;
	Item *data;
} Stack;

Stack *stack_create(size_t stack_size);
int stack_push(Stack *s, Item value);
Item stack_pop(Stack *s);
Item stack_top(Stack *s);
bool stack_is_empty(Stack *s);
bool stack_is_full(Stack *s);
void stack_destroy(Stack **s);
void stack_print(Stack *s);
void print_help();
Stack* stack_copy(Stack *s);

#endif