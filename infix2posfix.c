#include "stack.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

void *check_alloc(int size)
{
    void *p = calloc(1, size);
    assert(p);
    return p;
}

/*
 * symbol: 'a'
 * concatenation: 'ab'
 * alternation: 'a|b\
 * epsilon: '%'
 * repetion: 'a*'
 */
char *infix_to_posfix(const char *src)
{
    char *dst = check_alloc(strlen(src));
    stack_t *s = stack_ctor();
    
    int priority[256] = {0, };
    priority['*'] = '2';
    priority['.'] = '1';
    priority['|'] = '0';
    
    const char *p = src;
    char *d = dst;
    for (; '\0' != *p; p++) {
        switch (*p) {
        case '|': case '*': case '.':
            while (!stack_empty(s) && stack_top(s) != '(' &&
                   priority[stack_top(s)] >= priority[*p]) {
                *d++ = stack_top(s);
                stack_pop(s);
            }
            stack_push(s, *p);
            break;
        case '(':
            stack_push(s, *p);
            break;
        case ')':
            while (!stack_empty(s) && stack_top(s) != '(') {
                *d++ = stack_top(s);
                stack_pop(s);
            }
            stack_pop(s);
            break;
        default:
            *d++ = *p;
            break;
        }
    }
    while (!stack_empty(s)) {
        *d++ = stack_top(s);
        stack_pop(s);
    }

    stack_dtor(s);
    return dst;
}

int main()
{
    const char *src = "a.b|e.(c.d)*";
    char *dst = NULL;

    dst = infix_to_posfix(src);
    printf("[%s]->[%s]\n", src, dst);
    
    free(dst);
    
    return 0;
}
