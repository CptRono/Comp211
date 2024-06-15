typedef struct node node;

typedef struct graph {
    node** adjacency_list ; // array of pointers to nodes
    int num_vertices ;
    int num_edges ;
} graph ;

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
schedule* create_schedule(void);

// Function to add a task to the scheduler
/**
 * add_task(s, n) = s' : schedule
 * post-condition: s'.head = n
 *                n.next = s.head
 *                s'.size = s.size + 1
 * repr(s') = {s.head, ..., n} = {s->head, s->head->next, ..., s->head->next^k, n}
 *             where k <= s.size
*/
void add_task(schedule*, node*);

// Function to check if task is in the scheduler
/**
 * sch_has_task(s : schedule, n : node*) = true, if n is in s
 *                    = false, otherwise
 * true if: repr(s) = {s->head, s->head->next, ... s->head->next^k} where k <= s.size and n->vertext = s->head->vertex or n = s->head->next^k->vertex
 * 
*/
bool sch_has_task(schedule* , node* );

/**
 * prints contents of a schedule
*/
void print_schedule(schedule*);

/**
 * scheduler(g, sch, total_tasks, total_edges) = sch' : schedule
 * post-condition: sch'.head = NULL if cycle detected
 *               sch'.head = {n_1, n_2, ..., n_i} where n_i is a node in g
 *              sch'.size = total_tasks
 * repr(sch') = {sch'.head, sch'.head->next, ... sch'.head->next^k} where k <= sch'.size
*/
schedule* scheduler(struct graph* g, schedule* sch, int total_tasks, int total_edges);