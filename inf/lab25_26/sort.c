#include "sort.h"
#include "stack_array.h"
#include <stdio.h>

void stack_sort2(Stack *s) {
    printf("4");
    int x = stack_pop(s);
    Stack *s1 = stack_create(s->size);
    Stack *s2 = stack_create(s->size);
    Stack *tmp = stack_create(s->size);
    int y;
    while (stack_is_empty(s)) {
        y = stack_pop(s);
        if (y > x) {
            stack_push(s2, y);
        } else {
            stack_push(s1, y);
        }
    }
    if (s1->size > 1) {
        stack_sort2(s1);
        printf("0");
    }
    if (s2->size > 1) {
        stack_sort2(s2);
        printf("1");
    }
    while (!stack_is_empty(s2)) {
        stack_push(tmp, stack_pop(s2));
    }
    while (!stack_is_empty(tmp)) {
        stack_push(s, stack_pop(tmp));
    }
    stack_push(s, x);
    stack_destroy(&s1);
    stack_destroy(&s2);
    stack_destroy(&tmp);
    printf("2");
}







void quickSort(int *numbers, int left, int right)
{
    int pivot; // разрешающий элемент
    int l_hold = left; //левая граница
    int r_hold = right; // правая граница
    pivot = numbers[left];
    while (left < right) // пока границы не сомкнутся
    {
    while ((numbers[right] >= pivot) && (left < right))
      right--; // сдвигаем правую границу пока элемент [right] больше [pivot]
    if (left != right) // если границы не сомкнулись
    {
      numbers[left] = numbers[right]; // перемещаем элемент [right] на место разрешающего
      left++; // сдвигаем левую границу вправо 
    }
    while ((numbers[left] <= pivot) && (left < right))
      left++; // сдвигаем левую границу пока элемент [left] меньше [pivot]
    if (left != right) // если границы не сомкнулись
    {
      numbers[right] = numbers[left]; // перемещаем элемент [left] на место [right]
      right--; // сдвигаем правую границу вправо 
    }
  }
  numbers[left] = pivot; // ставим разрешающий элемент на место
  pivot = left;
  left = l_hold;
  right = r_hold;
  if (left < pivot) // Рекурсивно вызываем сортировку для левой и правой части массива
    quickSort(numbers, left, pivot - 1);
  if (right > pivot)
    quickSort(numbers, pivot + 1, right);
}

void stack_form_massiv(int *massiv, Stack *s, int a) 
{
    Stack *s_copy = stack_create(s->size);
    for (int i = a - 1; i >= 0; i--) {
        stack_push(s_copy, massiv[i]);
    }
    stack_print(s_copy);
    stack_destroy(&s_copy);
} 

int* create_massiv(Stack *s, int *massiv, int *i_old) 
{
    Stack *tmp = stack_create(s->size);
    int i = 0;
    while (!stack_is_empty(s)) {
        massiv[i] = stack_top(s);
        stack_push(tmp, stack_pop(s));
        i++;
    }
    
    *i_old = i;
    
    while (!stack_is_empty(tmp)) {
        stack_push(s, stack_pop(tmp));
    }
    stack_destroy(&tmp);
    return massiv;
}


void unctionm(Stack *s1, Stack *s2) 
{
    Stack *tmp = stack_create((s1->size) + (s2->size));
    Stack *s1_copy = stack_copy(s1);
    Stack *s2_copy = stack_copy(s2);
    
    while (!stack_is_empty(s1_copy)) {
        stack_push(tmp, stack_pop(s1_copy)); 
    }
    while (!stack_is_empty(s2_copy)) {
        stack_push(tmp, stack_pop(s2_copy));
    }

    stack_print(tmp);
    stack_destroy(&tmp);
}
