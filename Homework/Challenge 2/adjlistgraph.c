#include "graph.h"
#include <stdlib.h>
#include <stdio.h>

// program to create directed graph using adjacency list

typedef struct node node;

/**
 *  The type of a directed graph.
 * where g : graph, g has a set of vertices V and a set of edges E
 *     where u,v ∈ V. If there is an edge from u to v, then (u,v) ∈ E
 * 
 *     g.adjacency_list = [u_1, u_2, u_3, ..., u_i] where u_i ∈ V
 *                invariant: i <= g.num_vertices
 * 
 *     g.adjacency_list[u_i] = {u_i, v_1, v_2, ..., v_j} where v_j ∈ V
 *     repr( g.adjacency_list[u_i] ) = {u_i, g.adjacency_list[u_i]->next, g.adjacency_list[u_i]->next^k, ...}
 *                                     where g.adjacency_list[u_i]->next^k = NULL and k <= g.num_edges
 *                                     v_j = g.adjacency_list[u_i]->next^k
 *     invariant: v_j != u_i
 *                i <= g.num_vertices
 *                j <= g.num_edges
 *                (u,v) ∈ E only if v ∈ g.adjacency_list[u]
 */
typedef struct graph {
    node** adjacency_list ; // array of pointers to nodes
    int num_vertices ;
    int num_edges ;
} graph ;

/**
 *  graph_create(n) = g, a graph with n nodes and no edges.
 * post-condition:
 * g.adjacency_list = [u_1, u_2, u_3, ..., u_i] where u_i ∈ V 
 *          
 * g.adjacency_list[u_i] = {u_i} where u_i ∈ V
 * repr( g.adjacency_list[u_i] ) = {u_i, g.adjacency_list[u_i]->next} where g.adjacency_list[u_i]->next = NULL
 *              invariant: i <= g.num_vertices
 *                         g.num_vertices = n
 *                         g.num_edges = 0
 * 
 * 
 */
struct graph* graph_create(int n)
{
    graph* g = malloc(sizeof(struct graph));
    g->num_vertices = n;
    g->num_edges = 0;
    g->adjacency_list = malloc(sizeof(node*) * n);
    
    for (int i = 0; i < n; i++)
    {
        g->adjacency_list[i] = malloc(sizeof(node));
        g->adjacency_list[i]->vertex = i;
        g->adjacency_list[i]->next = NULL;
    }
    return g;
}

/**
 * graph_size(g) = the number of vertices in g
 * time-complexity: O(1)
 */
int graph_size(struct graph* g) 
{
    return g->num_vertices;
}

/**
 * graph_num_edges(g) = the number of edges in g.
 * time-complexity: O(1)
 */
int graph_num_edges(struct graph* g)
{
    return g->num_edges;
}

/* graph_has_edge(g, i, j) = true,  if there is an edge from i to j in g
 *                         = false, otherwise.
 *
 * Precondition:  0 <= i, j < graph_size(g).
 * true if: g.adjacency_list[i] = {i, v_1, v_2, ..., v_j} where v_j = j for some j
 *          g->adjacency_list[i]->next^k->vertex = j for some k
 *          false otherwise
 */
bool graph_has_edge(struct graph* g, int i, int j)
{
    node* current = g->adjacency_list[i];
    while (current != NULL)
    {
        if(current->vertex == j) return true;
        current = current->next;
    }
    return false;
}

/* graph_add_edge(g, i, j): add an edge from node i to node j in g.  If there
 * is already an edge from i to j, this function has no effect.
 *
 * Precondition:  0 <= i, j < graph_size(g).
 *                g.adjacency_list[i] = {i, v_1, v_2, ..., v_j} 
 *                g->adjacency_list[i] = {g->adjacency_list[i]->vertex, g->adjacency_list[i]->next^k->vertex,..., NULL}
 *                                       for some k where 0 <= k <= g.num_edges
 *                where v_j == j, the function has no effect
 * post-condition: g.adjacency_list[i] = {i, j, v_1, v_2, ..., v_j} where v_j != j
 *                g->adjacency_list[i] = {g->adjacency_list[i]->vertex, j,  g->adjacency_list[i]->next->next^k->vertex,..., NULL}
 *                                      for some k where 0 <= k <= g.num_edges  
 *                g.num_edges = g.num_edges + 1
 * 
 * invariant: i != j
 * 
 */
void graph_add_edge(struct graph* g, int i, int j)
{
    if(!graph_has_edge(g, i, j) && i != j)
    {
        node* new_node = malloc(sizeof(node));
        new_node->vertex = j;
        // add new node to the "begining" of the linked list(just after i)
        new_node->next = g->adjacency_list[i]->next;
        g->adjacency_list[i]->next = new_node;
        
        g->num_edges++;
    }
}

/* graph_get_edges(g, i) = p, where p is the first node in a linked sequence
 * that represents the nodes j such that there is an edge from i to j.  If
 * there are no such nodes, return NULL.
 *
 * The sequence of nodes returned by this function are dynamically allocated
 * and must be freed by the client.
 *
 * The sequence of nodes returned by this function are independent of the edges
 * in g; changes to this sequence will not affect edges in g.
 *
 * Precondition:  0 <= i < graph_size(g).
 * 
 * graph_get_edges(g, i) = p : list
 *           where p = {g.adjacency_list[i]->next, g.adjacency_list[i]->next^k, ...}
 *           where g.adjacency_list[i]->next^k = NULL
 *           where k <= g.num_edges && k <= g.num_vertices
 */
struct node* graph_get_edges(struct graph* g, int i)
{
    node* p = g->adjacency_list[i];
    p = p->next;    // skip the first node, i
    return p;
}

/**
 * TESTS
 * 
 * 
// Function to test graph_create()
void test_graph_create() {
    struct graph* g = graph_create(5);
    if (g->num_vertices == 5 && g->num_edges == 0) {
        printf("graph_create() test passed.\n");
    } else {
        printf("graph_create() test failed.\n");
        printf("num_vertices: %d\nnum_edges: %d\n", g->num_vertices, g->num_edges);
    }
}

// Function to test graph_size()
void test_graph_size() {
    struct graph* g = graph_create(8);
    int size = graph_size(g);
    if (size == 8) {
        printf("graph_size() test passed.\n");
    } else {
        printf("graph_size() test failed.\n");
    }
}

// Function to test graph_num_edges()
void test_graph_num_edges() {
    struct graph* g = graph_create(5);
    graph_add_edge(g, 0, 1);
    graph_add_edge(g, 1, 2);
    int num_edges = graph_num_edges(g);
    if (num_edges == 2) {
        printf("graph_num_edges() test passed.\n");
    } else {
        printf("graph_num_edges() test failed.\n");
    }
}

// Function to test graph_has_edge()
void test_graph_has_edge() {
    struct graph* g = graph_create(5);
    graph_add_edge(g, 0, 1);
    graph_add_edge(g, 1, 2);
    bool has_edge = graph_has_edge(g, 0, 1);
    if (has_edge) {
        printf("graph_has_edge() test passed.\n");
    } else {
        printf("graph_has_edge() test failed.\n");
    }
}

// Function to test graph_add_edge()
void test_graph_add_edge() {
    struct graph* g = graph_create(5);
    graph_add_edge(g, 0, 1);
    graph_add_edge(g, 1, 2);
    bool has_edge = graph_has_edge(g, 0, 1);
    if (has_edge) {
        printf("graph_add_edge() test passed.\n");
    } else {
        printf("graph_add_edge() test failed.\n");
    }
}

// Function to test graph_get_edges()
void test_graph_get_edges() {
    struct graph* g = graph_create(5);
    graph_add_edge(g, 0, 1);
    graph_add_edge(g, 0, 2);
    struct node* edges = graph_get_edges(g, 0);
    if (edges->vertex == 2 && edges->next->vertex == 1) {
        printf("graph_get_edges() test passed.\n");
    } else {
        printf("graph_get_edges() test failed.\n");
    }
}


int main() {
    test_graph_create();
    test_graph_size();
    test_graph_num_edges();
    test_graph_has_edge();
    test_graph_add_edge();
    test_graph_get_edges();
    return 0;
} */

