#include "stack.h"
#include <stdlib.h>
#include "graph.h"

// Function to create a new stack
/**
 * create_stack() = s : stack
 * post-condition: s.head = NULL
 *                s.size = 0
 * repr(s) = {s->head} where s->head = NULL
*/
stack* create_stack()
{
    stack* s = malloc(sizeof(stack));
    s->head = NULL; //
    s->size = 0;
    return s;
}

// Function to push a node onto the stack
/**
 * push(s, n) = s' : stack
 * post-condition: s'.head = n
 *                n.next = s.head
 *                s'.size = s.size + 1
 * repr(s') = {n, s.head, ...} = {n, s->head, s->head->next, ..., s->head->next^k}
 *             where k <= s.size
*/
void push(stack* s, node* n)
{
    node* new_node = malloc(sizeof(node));
    // copy data to new node
    new_node->vertex = n->vertex;
    new_node->next = s->head;
    // make new node the head
    s->head = new_node;
    s->size++;
}

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
node* pop(stack* s)
{
    if (s->size == 0) return NULL;
    node* n = s->head;
    s->head = s->head->next;
    s->size--;
    return n;
}

// Function to check if task is in the stack
/**
 * stk_has_task(s : stack, n : int) = true, if n is in s
 *                    = false, otherwise
 * true if: repr(s) = {s->head, s->head->next, ... s->head->next^k} where k <= s.size and n = s->head->vertex or n = s->head->next^k->vertex
 * 
*/
bool stk_has_task(stack* s, node* n)
{
    node* current = s->head;
    while (current != NULL)
    {
        if(current->vertex == n->vertex) return true;
        current = current->next;
    }
    return false;
}

// Function that checks if stack is empty
/**
 * stk_empty(s : stack) = true, if s.size = 0
 *                     = false, otherwise
*/
bool stk_empty(stack* s)
{
    return s->size == 0;
}

/**
 * Prints contents of a stack
*/
void print_stack(stack* s)
{
    node* current = s->head;
    while(current != NULL)
    {
        printf("--%d--", current->vertex);
        current = current->next;
    }
    printf("\n");
}
