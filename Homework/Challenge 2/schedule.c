#include "graph.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct node node;

typedef struct graph {
    node** adjacency_list ; // array of pointers to nodes
    int num_vertices ;
    int num_edges ;
} graph ;

// list-backed stack
typedef struct stack{
    node* head;
    node* tail;
    int size;
} stack;

// Function to create a new stack
stack* create_stack()
{
    stack* s = malloc(sizeof(stack));
    s->head = NULL;
    s->tail = NULL;
    s->size = 0;
    return s;
}

// Function to push a node onto the stack
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
node* pop(stack* s)
{
    if (s->size == 0) return NULL;
    node* n = s->head;
    s->head = s->head->next;
    s->size--;
    return n;
}

// list-backed queue of tasks
typedef struct schedule{
    node* head;
    int size;
} schedule;

// Function to create a new scheduler
schedule* create_schedule()
{
    schedule* s = malloc(sizeof(schedule));
    s->head = NULL;
    s->size = 0;
    return s;
}

// Function to add a task to the scheduler
void add_task(schedule* s, node* n)
{
    node* new_task = malloc(sizeof(node));
    // copy data to new node
    new_task->vertex = n->vertex;
    new_task->next = s->head;
    // make new node the head
    s->head = new_task;
    s->size++;
}

// Function to check if task is in the scheduler
bool sch_has_task(schedule* s, node* n)
{
    node* current = s->head;
    while (current != NULL)
    {
        if(current->vertex == n->vertex) return true;
        current = current->next;
    }
    return false;
}

// Function to check if task is in the stack
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
bool stk_empty(stack* s)
{
    return s->size == 0;
}

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

void print_graph(graph* g)
{
    for (int i = 0; i < g->num_vertices; i++)
    {
        node* current = g->adjacency_list[i];
        while(current != NULL)
        {
            printf("--%d--", current->vertex);
            current = current->next;
        }
        printf("\n");
    }
}

void print_schedule(schedule* sch)
{
    node* current = sch->head;

    printf("\n");
    while(current != NULL)
    {
        printf("%d, ", current->vertex);
        current = current->next;
    }
    printf("\n");
}

schedule* scheduler(struct graph* g, schedule* sch, int total_tasks, int total_edges)
{
    if (g == NULL) return NULL;
    stack* stk = create_stack();
    printf("sched 1\n");

    // push tasks to the stack
    for(int i = 0; i < total_tasks; i++)    // PROBLEM?? when should this stop?
    {
        //printf("sched 2\n");

        node* n = g->adjacency_list[i];
        //printf("big loop vertex = %d\n", n->vertex);
        if(n->next == NULL) break;

        //printf("sched 3\n");

        while(stk_has_task(stk, n) && n->next != NULL) n = n->next; // skip to next directly connected node that is not already in stack
        
        //printf("sched 4\n");
        
        while(n != NULL)
        {
            //printf("sched loop 1\n");
            if(!sch_has_task(sch, n) && !stk_has_task(stk, n)) // hasnt been scheduled or waiting to be scheduled
            {
                push(stk, n);   // waiting to be scheduled
                printf("%d pushed to stack.printing stack\n", n->vertex);
                print_stack(stk);
                
            }
            //printf("sched loop 2\n");
            n = n->next;    // move to node directly connected to current node
            if (n == NULL) //has no dependencies
            {
                n = pop(stk);
                printf("%d popped from stack.printing stack\n", n->vertex);
                print_stack(stk);

                add_task(sch, n);
                printf("%d scheduled. printing schedule \n", n->vertex);
                print_schedule(sch);

                free(n);
                break;
            }
            //printf("sched loop 3\n");

            //printf("small loop vertex: %d\n", g->adjacency_list[n->vertex]->vertex);
            
            n = stk->head;   // backtrack to previous node (now at top of stack)
            //n = g->adjacency_list[n->vertex];   // move to current node's adjacency list
            //printf("sched loop 4\n");
        }
    }

    /** pop everything off the stack and push to schedule once all nodes have been visited
    while(!stk_empty(stk))
    {
        node* n = pop(stk);
        add_task(sch, n);
        free(n);
    }
    */
    return sch;
}



int main(void)
{
    printf("1\n");
    schedule* sch = create_schedule();

    printf("2\n");
    
    graph* g = graph_create(9);

    printf("3\n");

    graph_add_edge(g, 0, 1);
    printf("4\n");
    graph_add_edge(g, 0, 2);
    graph_add_edge(g, 0, 3);
    graph_add_edge(g, 1, 4);
    graph_add_edge(g, 2, 5);
    graph_add_edge(g, 2, 6);
    graph_add_edge(g, 3, 7);
    graph_add_edge(g, 4, 7);
    graph_add_edge(g, 5, 7);
    graph_add_edge(g, 6, 7);
    graph_add_edge(g, 7, 8);
    print_graph(g);
    printf("5\n");

    scheduler(g, sch, 9, 11);
    printf("6\n");
    print_schedule(sch);
}