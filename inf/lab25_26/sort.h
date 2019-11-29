#ifndef SORT_H
#define SORT_H

#include <stdlib.h>
#include <stdbool.h>
#include "stack_array.h"

void quickSort(int *numbers, int left, int right);
void stack_sort2(Stack *s);
void stack_form_massiv(int *massiv, Stack *s, int a);
int* create_massiv(Stack *s, int *massiv, int *i_old);
void unctionm(Stack *s1, Stack *s2);

#endif