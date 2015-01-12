#include "stack.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define INIT_NR 100
#define INCRE 100

struct stack {
    int top;
    int *elts;
    int cap;
};

stack_t *stack_ctor()
{
    stack_t *s = malloc(sizeof (*s));
    assert(s);
    s->top = -1;
    s->elts = malloc(sizeof (int) * INIT_NR);
    assert(s->elts);
    s->cap = INIT_NR;
    return s;
}

void stack_push(stack_t *s, int elt)
{
    if (s->top+1 >= s->cap) {
        s->cap *= 2;
        int *p = malloc(s->cap*sizeof (int));
        assert(p);
        memcpy(p, s->elts, sizeof (int) * (s->top+1));
        free(s->elts);
        s->elts = p;
    }
    s->elts[++s->top] = elt;
}

int stack_top(stack_t *s)
{
    return s->elts[s->top];
}

void stack_pop(stack_t *s)
{
    s->top--;
}

void stack_dtor(stack_t *s)
{
    assert(s);
    assert(s->elts);
    free(s->elts);
    free(s);
}

int stack_empty(stack_t *s)
{
    return (-1 == s->top);
}

#ifdef UNIT_TEST
#include <stdio.h>
int main()
{
    stack_t *s = stack_ctor();
    int i;

    for (i = 0; i < 1000; i++) {
        stack_push(s, i);
    }
    while (!stack_empty(s)) {
        printf("%d ", stack_top(s));
        stack_pop(s);
    }
    printf("\n");
    stack_dtor(s);
    
    return 0;
}
#endif

