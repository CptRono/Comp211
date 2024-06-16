/* COMP 211 Lab 11:  Hash set implementation.
 *
 * Allan Cheruiyot
 * May 3, 2024
 */

#include "dict.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

#ifndef TBL_SIZE
#define TBL_SIZE 9
#endif

/* hash(s) = the hash code of the string s.
 *
 * Pre-condition:  c is a null-terminated string.
 *
 * This algorithm is adapted from Sedgewick, R., _Algorithms in Java_, 3rd ed.,
 * Addison-Wesley, 2003, p. 604.
 *
 * Modified to prevent overflow as per
 *   https://cp-algorithms.com/string/string-hashing.html
 */
#define P 1000000009
unsigned int hash(char* s) {
    unsigned int h = 0, a = 127 ;

    char* c = s ;

    while (*c != '\0') {
        h += (a*h + (unsigned int)(*c)) % P ;
        c += 1 ;
    }

    return h ;
}

typedef struct node{
    char* key;
    int value;
    struct node* next;
} node;

typedef struct list{
    node* head;
    node* tail;
    int size;
} list;

/** repr(dict) = { (k, v) : k is a key in dict, v is a value where v = dict[k] }
 * the dictionary is not ordered
 * invariant: size of dict is non-negative
 *            there cannot be any duplicate keys in dict
 *            size of dict is the number of key-value pairs in dict
 *            dict is a hash table with TBL_SIZE buckets
 *            each bucket is a linked list of key-value pairs
 *            each key-value pair is a node with a key, value, and next pointer
 *            each node in the linked list has a key and value
 * 
 * 
 * */ 

typedef struct dict{
    list* table[TBL_SIZE];
    int size;
} dict;

/* dict_create() = ∅
 */
struct dict* dict_create()
{
    struct dict* d = malloc(sizeof(struct dict));

    for (int i = 0; i < TBL_SIZE; i++)
    {
        // add list to each index of the table
        list* l = malloc(sizeof(list));
        l->head = malloc(sizeof(node));
        l->tail = malloc(sizeof(node));
        d->table[i] = l;
        // add dummy head and tail nodes to each list in the table
        l->head->key = NULL;
        l->tail->key = NULL;
        l->head->next = l->tail;
        l->tail->next = NULL;
        l->size = 0;
    }
    d->size = 0;
    // invariant: size of dict should be non-negative
    assert(d->size >= 0);
    return d;
}

/* dict_size(s) = the number of key-value pairs in d.
 */
unsigned int dict_size(struct dict* d)
{
    // invariant: size of dict should be non-negative
    assert(d->size >= 0);
    return d->size;
}

/* dict_contains(d, s) = true,  s a key in d
 *                       false, o/w.
 */
bool dict_contains(struct dict* d, char* s)
{
    int index = hash(s) % TBL_SIZE;
    if (d->table[index]->head->next->key == NULL) return false;   // if list is empty

    node* ptr = d->table[index]->head->next;

    while (ptr->key != NULL && ptr != NULL)
    {
        if(strcmp(ptr->key, s) == 0)
        {
            return true;
        }
        ptr = ptr->next;
    }
    return false;
}

/* dict_add(d, s, n):
 * Pre-condition:  d' = d
 * Post-condition: d = d' ∪ {(s, n)}.
 *
 * I.e., add (s, n) to d.  If there is a key value pair in d with key s, 
 * replace it.
 */
void dict_add(struct dict* d, char* s, int n)
{

    //printf("reached dict add 1\n");
    int index = hash(s) % TBL_SIZE;

    //printf("reached dict add 2\n");
    node* ptr = d->table[index]->head->next;     // start at node after dummy head
    //printf("reached dict add 3\n");

    // replace value if key already exists
    if(dict_contains(d, s))
    {
        //printf("reached dict add 4\n");
        while(ptr->key != NULL)     // while not at dummy tail node
        {
            if(strcmp(ptr->key, s) == 0)
            {
                ptr->value = n;
                break;
            }
            ptr = ptr->next;
        }
    }
    

    // add new key-value pair and increment size if key does not exist
    else
    {
        //printf("reached dict add 6\n");
        node* newnode = malloc(sizeof(node));
        newnode->key = malloc(strlen(s) + 1);
        strcpy(newnode->key,s);
        newnode->value = n;

        // add new node after dummy head node
        newnode->next = d->table[index]->head->next;
        d->table[index]->head->next = newnode;
        d->size++;
        d->table[index]->size += 1;    // increment size of list
        //printf("reached dict add 7\n");
    }
    //printf("reached dict add 8\n");
    //dict_print(d);

    // invariant: key s is in dict after function runs
    assert(dict_contains(d, s));
}

/* dict_get(d, s) = v, where (s, v) is a key-value pair in d.
 *
 * Pre-condition:  dict_contains(d, s) = true.
 */
int dict_get(struct dict* d, char* s)
{
    // invariant: key s is in dict
    assert(dict_contains(d, s));

    int index = hash(s) % TBL_SIZE;
    node* ptr = d->table[index]->head->next;

    while(ptr->key != NULL)
    {
        if(strcmp(ptr->key, s) == 0)
        {
            return ptr->value;
        }
        ptr = ptr->next;
    }
    return 0;
}

/* dict_delete(d, s):
 * Pre-condition:  d' = d
 * Post-condition: d = d' - {(s, n)}, if (s, n) is in d'
 *                     d',            otherwise.
 *
 * I.e., remove the key-value pair with key s from d.  Notice that if s is not
 * a key in d, calling dict_delete(d, s) has no effect.
 */

void dict_delete(struct dict* d, char* s)
{
    // invariant: key s is in dict
    if (dict_contains(d, s))
    {
        int index = hash(s) % TBL_SIZE;

        node* ptr = d->table[index]->head->next;     // start at node after dummy head
        node* prev = d->table[index]->head;
        node* next = ptr->next;

        while(ptr->key != NULL)     // while not at dummy tail node
        {
            if(strcmp(ptr->key, s) == 0)
            {
                prev->next = next;
                free(ptr);
                d->size--;
                return;
            }
            prev = ptr;
            ptr = next;
            next = next->next;
        }
        d->table[index]->size -= 1;    // decrement size of list
    }
    // invariant: key s is not in dict when this function terminates
    assert(!dict_contains(d, s));
}

/* to_array(d, ks):  fill ks with the keys of d.
 * Pre-condition:  ks has size at least dict_size(d).
 * Post-condition: the set of keys of d = {ks[i] : 0 <= i < dict_size(d)}.
 *
 * Note:  for 0 <= i < dict_size(d), ks[i] will have been dynamically
 * allocated.  It is up to the caller to free this space.
 */
void dict_keys_to_array(struct dict* d, char* ks[])
{
    int ks_index = 0;

    for (int i = 0; i < TBL_SIZE; i++)
    {
        node* ptr = d->table[i]->head->next;     // start at node after dummy head
        
        for( ; ptr->key != NULL; ks_index++, ptr = ptr->next)
        {
            ks[ks_index] = ptr->key;
        }
    }

    // invariant: ks should have the same number of keys as dict d
    assert(ks_index == dict_size(d));
}

/* dict_free(d):  free all resources associated to d.
 */
void dict_free(struct dict* d)
{
    for (int i = 0; i < TBL_SIZE; i++)
    {
        
        node* ptr = d->table[i]->head;
        
        node* next = ptr->next;
        

        while(next->next != NULL)
        {
            free(ptr);
            ptr = next;
            next = next->next;
        }
        free(ptr);
    }
    free(d);
}

/* dict_print(d):  print information about s.
 *
 * There are no constraints on this function.  I suggest you implement it in a
 * way that prints out the values of everything used to represent your dict.
 */
void dict_print(struct dict* d)
{
    for (int i = 0; i < TBL_SIZE; i++)
    {
        node* ptr = d->table[i]->head->next;     // start at node after dummy head

        printf("{");
        for( int j = 0; j < d->table[i]->size; j++)
        {
            printf("(%s, %d), ", ptr->key, ptr->value);
            ptr = ptr->next;
        }
        printf("}\n");
    }
}

int main(void){
    struct dict* d = dict_create();
    dict_add(d, "hello", 1);
    dict_add(d, "world", 2);
    dict_add(d, "hello", 3);
    dict_add(d, "world", 4);
/*     dict_add(d, "hello", 5);
    dict_add(d, "world", 6);
    dict_add(d, "hello", 7);
    dict_add(d, "world", 8);
    dict_add(d, "hell", 9);
    dict_add(d, "world", 10);
    dict_add(d, "hello", 11);
    dict_add(d, "world", 12);
    dict_add(d, "hello", 13);
    dict_add(d, "world", 14);
    dict_add(d, "hello", 15);
    dict_add(d, "world", 16);
    dict_add(d, "hello", 17);
    dict_add(d, "world", 18);
    dict_add(d, "hello", 19);
    dict_add(d, "world", 20);
    dict_add(d, "hello", 21);
    dict_add(d, "world", 22);
    dict_add(d, "hello", 23);
    dict_add(d, "world", 24);
    dict_add(d, "hello", 25);
    dict_add(d, "world", 26);
    dict_add(d, "hello", 27);
    dict_add(d, "world", 28);
    dict_add(d, "hello", 29);
    dict_add(d, "world", 30);
    dict_add(d, "hello", 31);
    dict_add(d, "world", 32);
    dict_add(d, "hello", 33);
    dict_add(d, "world", 34);
    dict_add(d, "hello", 35);
    dict_add(d, "world", 36);
    dict_add(d, "hello", 37);
    dict_add(d, "world", 38);
    dict_add(d, "hello", 39);
    dict_add(d, "world", 40);
    dict_add(d, "hello", 41);
    dict_add(d, "world", 42);
    dict_add(d, "hello", 43);
    dict_add(d, "world", 44); */
    dict_print(d);
    return 0;
}