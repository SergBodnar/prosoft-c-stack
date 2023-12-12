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

hstack_t stack_new()
{
    descriptor_table[stack_descriptor_id + 1]->id = stack_descriptor_id;
    descriptor_table[stack_descriptor_id]->top = NULL;
    return (stack_descriptor_id);
}

// рекурсия
/*
void stack_free(const hstack_t hstack)
{

    if ((stack_valid_handler(hstack) == 1)          //
        || (descriptor_table[hstack]->top == NULL)) //
    {
        return;
    }
    descriptor_table[hstack]->node_count--;
    node_t *ptr_prev = descriptor_table[hstack]->top->prev;

    free(descriptor_table[hstack]->top);
    descriptor_table[hstack]->top = ptr_prev;
    stack_free(hstack);
}
*/

// while
void stack_free(const hstack_t hstack)
{

    while ((stack_valid_handler(hstack) == 0)          //
           && (descriptor_table[hstack]->top != NULL)) //
    {
        descriptor_table[hstack]->node_count--;
        node_t *ptrPrev = descriptor_table[hstack]->top->prev;

        free(descriptor_table[hstack]->top);
        descriptor_table[hstack]->top = ptrPrev;
    }
    return;
}

int stack_valid_handler(const hstack_t hstack)
{
    if ((hstack <= stack_descriptor_id) //
        && (hstack >= 0))               //
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

unsigned int stack_size(const hstack_t hstack)
{
    if (stack_valid_handler(hstack) == 0)
    {
        return descriptor_table[hstack]->node_count;
    }
    else
    {
        return 0;
    }
}

void stack_push(const hstack_t hstack, const void *data_in, const unsigned int size)
{

    if ((stack_valid_handler(hstack) == 0) //
        && (data_in != NULL)               //
        && (size > 0))                     //
    {

        node_t *ptr_node = (node_t *)malloc(sizeof(node_t) + sizeof(char) * size);

        if (ptr_node == NULL)
        {
            return;
        }

        ptr_node->prev = descriptor_table[hstack]->top;
        ptr_node->size = size;
        memcpy(ptr_node->data, data_in, size);

        descriptor_table[hstack]->top = ptr_node;
        descriptor_table[hstack]->node_count++;
    }
}

unsigned int stack_pop(const hstack_t hstack, void *data_out, const unsigned int size)
{
    if ((stack_valid_handler(hstack) == 0)               //
        && (descriptor_table[hstack]->node_count > 0)    //
        && (size >= descriptor_table[hstack]->top->size) //
        && (data_out != NULL))
    {
        node_t *ptr_top = descriptor_table[hstack]->top;

        descriptor_table[hstack]->top = ptr_top->prev;
        memcpy(data_out, ptr_top->data, ptr_top->size);
        free(ptr_top);
        ptr_top = NULL;
        descriptor_table[hstack]->node_count--;
        return ptr_top->size;
    }
    return 0;
}