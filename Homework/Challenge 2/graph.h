/* COMP 211 Challenge 2P:  Scheduling tasks.
 *
 * Graph interface.
 *
 * N. Danner
 */

#include <stdbool.h>

/* The type of a directed graph.
 */
struct graph ;

/* The type of a singly linked node (used by graph_get_edges).
 */
struct node {
    int vertex ;
    struct node* next ;
} ;

/* graph_create(n) = a graph with n nodes and no edges.
 */
struct graph* graph_create(int) ;

/* graph_size(g) = the number of vertices in g.
 */
int graph_size(struct graph*) ;

/* graph_num_edges(g) = the number of edges in g.
 */
int graph_num_edges(struct graph*) ;

/* graph_add_edge(g, i, j): add an edge from node i to node j in g.  If there
 * is already an edge from i to j, this function has no effect.
 *
 * Precondition:  0 <= i, j < graph_size(g).
 */
void graph_add_edge(struct graph*, int, int) ;

/* graph_has_edge(g, i, j) = true,  if there is an edge from i to j in g
 *                         = false, otherwise.
 *
 * Precondition:  0 <= i, j < graph_size(g).
 */
bool graph_has_edge(struct graph*, int, int) ;

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
 */
struct node* graph_get_edges(struct graph*, int) ;

