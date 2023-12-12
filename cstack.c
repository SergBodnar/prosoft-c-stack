/*
Школа ПРОСОФТ 2023.
Задание.
В файле cstack.h определен интерфейс (API) в виде набора прототипов функций.
Необходимо реализовать эти функции.
Библиотека предназначен для реализации стека в учебных целях.

Функция void stack_free(const hstack_t hstack) выполнена в двух вариантах:
1. рекурсия
2. цикл while

https://github.com/SergBodnar/prosoft-c-stack

Сергей Боднар.
*/

#include "cstack.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define STACKCOUNT 20

int stack_descriptor_id = -1;

typedef struct node
{
    struct node *prev;
    unsigned int size;
    char data[0];
} node_t;

typedef struct stack_descriptor
{
    struct node *top;
    int node_count;
    int id;

} stack_descriptor_t;

stack_descriptor_t *descriptor_table[STACKCOUNT];