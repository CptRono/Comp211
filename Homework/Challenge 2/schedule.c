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

// list-backed queue of tasks
/**
 * where sch : schedule, sch has a set of linked nodes N
 * repr(sch) = {sch->head, sch->head->next, ... sch->head->next^k}
 *         where k <= sch.size
 *         sch.size = number of nodes in schedule
*/
typedef struct schedule{
    node* head;
    int size;
} schedule;

// Function to create a new schedule
/**
 * create_schedule() = sch : schedule
 * post-condition: sch.head = NULL
 *                sch.size = 0
 * repr(sch) = {sch->head} where sch->head = NULL
*/
schedule* create_schedule()
{
    schedule* s = malloc(sizeof(schedule));
    s->head = NULL;
    s->size = 0;
    return s;
}

// Function to add a task to the scheduler
/**
 * add_task(s, n) = s' : schedule
 * post-condition: s'.head = n
 *                n.next = s.head
 *                s'.size = s.size + 1
 * repr(s') = {s.head, ..., n} = {s->head, s->head->next, ..., s->head->next^k, n}
 *             where k <= s.size
*/
void add_task(schedule* s, node* n)
{
    node* new_task = malloc(sizeof(node));
    // copy data to new node
    new_task->vertex = n->vertex;
    new_task->next = NULL;

    // add new node to end of schedule
    node* current = s->head;
    if(current == NULL)
    {
        s->head = new_task;
        s->size++;
        return;
    }
    while(current != NULL)
    {
        if(current->next == NULL)
        {
            current->next = new_task;
            break;
        }
        current = current->next;
    }
}

// Function to check if task is in the scheduler
/**
 * sch_has_task(s : schedule, n : int) = true, if n is in s
 *                    = false, otherwise
 * true if: repr(s) = {s->head, s->head->next, ... s->head->next^k} where k <= s.size and n = s->head->vertex or n = s->head->next^k->vertex
 * 
*/
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

/**
 * Prints contents of a graph
*/
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

/**
 * prints contents of a schedule
*/
void print_schedule(schedule* sch)
{
    node* current = sch->head;

    printf("\n");
    while(current != NULL)
    {
        printf("%d\n", current->vertex);
        current = current->next;
    }
    printf("\n");
}
schedule* scheduler(struct graph* g, schedule* sch, int total_tasks, int total_edges)
{
    stack* stk = create_stack();
    node* init_node = g->adjacency_list[0];
    push(stk, init_node);  // push first node to stack

    // while stack is not empty
    while(!stk_empty(stk))
    {
        // take the top node from stack and add directly connected nodes to stack in the while loop
        node* top_of_stack = stk->head;

        // add to schedule if node has no dependencies
        if(g->adjacency_list[top_of_stack->vertex]->next == NULL)
        {
            node* popped = pop(stk);
            add_task(sch, popped);
            continue;
        }

         // go to adjacency list of current node
        node* current = g->adjacency_list[top_of_stack->vertex];

        // if 1st node in adjlist has been scheduled, all nodes in that list have been scheduled
        // so pop top node in stack and add to schedule
        if(sch_has_task(sch, current->next))
        {
            node* popped = pop(stk);
            add_task(sch, popped);
            continue;
        }
        // else push directly connected nodes to stack
        while(current->next != NULL)
        {
            current = current->next;
            if(stk_has_task(stk, current))  // node already in stack, hence cycle detected
            {
                sch->head = NULL;
                return sch; 
            }
            push(stk, current);
        }
    }
    // reverse the schedule
    //reverse_schedule(sch);
    return sch;
}

int main(void)
{
    schedule* sch = create_schedule();


    char filename[100];
    printf("Please enter name of file: ");
    scanf("%s", filename);

    FILE* fptr;
    
    fptr = fopen(filename, "r");
    if(fptr == NULL)
    {
        printf("Error opening file\n");
        return 1;
    }

    
    int from, to;
    int nodes_count, vertices_count;

    fscanf(fptr, "%d\n", &nodes_count);
    fscanf(fptr, "%d\n", &vertices_count);

    graph* g = graph_create(nodes_count);
    
    for(int i = 0; i < vertices_count; i++)
    {
        fscanf(fptr,"%d -> %d\n", &from, &to);
        graph_add_edge(g, from, to);
    }
    
    
    


/*     graph_add_edge(g, 0, 1);
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
    //graph_add_edge(g, 8, 2);
    print_graph(g);
    printf("5\n");
    */

    scheduler(g, sch, 9, 11);
    if(sch->head == NULL) printf("Cycle detected.\n");
    else print_schedule(sch);
}