#include <stdio.h>
#include <stdbool.h>

typedef struct node node;

// list-backed stack
/**
 * where s : stack, s has a set of linked nodes N
 * repr(s) = {s->head, s->head->next, ... s->head->next^k}
 *         where k <= s.size
 *         s.size = number of nodes in stack
*/
typedef struct stack{
    node* head; 
    int size;
} stack;

/**
 * create_stack() = s : stack
 * post-condition: s.head = NULL
 *                s.size = 0
 * repr(s) = {s->head} where s->head = NULL
*/
stack* create_stack(void);

// Function to push a node onto the stack
/**
 * push(s, n) = s' : stack
 * post-condition: s'.head = n
 *                n.next = s.head
 *                s'.size = s.size + 1
 * repr(s') = {n, s.head, ...} = {n, s->head, s->head->next, ..., s->head->next^k}
 *             where k <= s.size
*/
void push(stack*, node*);

// Function to pop a node from the stack
/**
 * pop(s) = n : node
 * pre-condition: s.size > 0
 *                repr(s) = {s->head, s->head->next, ... s->head->next^k} where k <= s->size
 * post-condition: n = s->head
 *                 s'->head = s->head->next
 *                 s'.size = s.size - 1
 * repr(s') = {s->head->next, ..., s->head->next^k} where s->head->next = n where k <= s->size-1
*/
node* pop(stack*);

// Function to check if task is in the stack
/**
 * stk_has_task(s : stack, n : int) = true, if n is in s
 *                    = false, otherwise
 * true if: repr(s) = {s->head, s->head->next, ... s->head->next^k} where k <= s.size and n = s->head->vertex or n = s->head->next^k->vertex
 * 
*/
bool stk_has_task(stack*, node*);

/**
 * stk_empty(s : stack) = true, if s.size = 0
 *                     = false, otherwise
*/
bool stk_empty(stack*);

/**
 * Prints contents of a stack
*/
void print_stack(stack*);