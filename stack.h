#ifndef _STACK_H_
#define _STACK_H_

typedef struct stack stack_t;

stack_t *stack_ctor();
void stack_dtor(stack_t *s);
void stack_push(stack_t *s, int elt);
int stack_top(stack_t *s);
void stack_pop(stack_t *s);
int stack_empty(stack_t *s);

#endif
