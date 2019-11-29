#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "bst.h"


Stack *stack_create(size_t stack_size)
{
	Stack *s = (Stack *)malloc(sizeof(Stack));
	s->data = malloc(sizeof(Item) * stack_size);
	s->ptr = 0;
	s->size = stack_size;
	return s;
}

int stack_push(Stack *s, Item value)
{
	if (stack_is_full(s)) {
		s->data = (Item*)realloc(s->data, sizeof(Item) * (s->size + 5));
		s->size += 5;
	}
	s->data[s->ptr++] = value;
	return 0;
}

Item stack_pop(Stack *s)
{
	if (stack_is_empty(s)) {
		return 0;
	}
	return s->data[--s->ptr];
}

Item stack_top(Stack *s)
{
	if (stack_is_empty(s)) {
		return 0;
	}
	return s->data[s->ptr - 1];
}


bool stack_is_empty(Stack *s)
{
	return (s->ptr <= 0);
}

bool stack_is_full(Stack *s)
{
	return (s->ptr >= s->size);
}

void stack_destroy(Stack **s)
{
	free((*s)->data);
	free(*s);
	*s = NULL;
}

void stack_print(Stack *s) {
	Stack *tmp = stack_create(s->size);
	while (!stack_is_empty(s)) {
		printf("%d ", stack_top(s));
		stack_push(tmp, stack_pop(s));
	}

	printf("\n");

	while (!stack_is_empty(tmp)) {
		stack_push(s, stack_pop(tmp));
	}
	
	stack_destroy(&tmp);
}


Stack* stack_copy(Stack *s)
{
    Stack *s_copy1 = stack_create(s->size);
    Stack *s_copy2 = stack_create(s->size);

    while (!stack_is_empty(s)) {
        stack_push(s_copy1, stack_top(s));
        stack_push(s_copy2, stack_pop(s));
    }
    while (!stack_is_empty(s_copy2)) {
        stack_push(s, stack_pop(s_copy2));
    }
    return s_copy1;
}