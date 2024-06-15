#include "graph.h"
#include "stack.h"
#include "schedule.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

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
    s->size++;
}

// Function to check if task is in the scheduler
/**
 * sch_has_task(s : schedule, n : node*) = true, if n is in s
 *                    = false, otherwise
 * true if: repr(s) = {s->head, s->head->next, ... s->head->next^k} where k <= s.size and n->vertex = s->head->vertex or n->vertex = s->head->next^k->vertex
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

/**
 * scheduler(g, sch, total_tasks, total_edges) = sch' : schedule
 * post-condition: sch'.head = NULL if cycle detected
 *               sch'.head = {n_1, n_2, ..., n_i} where n_i is a node in g
 *              sch'.size = total_tasks
 * repr(sch') = {sch'.head, sch'.head->next, ... sch'.head->next^k} where k <= sch'.size
*/
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
    assert(sch->size == total_tasks);

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
    scheduler(g, sch, 9, 11);
    if(sch->head == NULL) printf("Cycle detected.\n");
    else print_schedule(sch);
}