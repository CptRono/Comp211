/* COMP 211 Homework 10:  Dictionaries
 *
 * Allan Cheruiyot
 * May 3, 2024
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dict.h"

/* The maximum length of any filename.
 */
#define FNAME_MAX_LEN 128

/* Characters used to delimit words.
 */
#define DELIMS " \n\t,./;'[]\\-=<>?:\"{}|!@#$%^&*()_+0123456789"



int main(void) {

    struct dict* d = dict_create();

    /* The file from which to count words (prompted).
     */
    char fname[FNAME_MAX_LEN] ;

    /* File pointer to fname.
     */
    FILE* fp ;

    /* Represents one line of the file.
     */
    char* lineptr = NULL ;

    /* Represents the length of the line.
     */
    size_t len = 0 ;

    /* Open the file, read lines, count words.
     */
    printf("Enter filename: ") ;
    scanf(" %s", fname) ;
    fp = fopen(fname, "r") ;
    assert(fp != NULL) ;

    /* Repeatedly set lineptr to a dynamically-allocated array containing the
     * next line to be read.  getline() returns -1 when there are no more
     * lines to read.
     */
    while (getline(&lineptr, &len, fp) != -1) {

        /* Initialize the tokenizer, which splits the line into words.
         * Basically, each call to strtok() returns the next word in
         * `lineptr`, with the first call returning the first word, the second
         * call returning the second word, etc.  `strtok` returns NULL when
         * there are no more words in the line.
         */

        /* `word` is the first word in the line.  So you can see what is
         * happening, I have printed out the word, but you should delete that
         * line for your client.
         */
        char* word = strtok(lineptr, DELIMS) ;
        /* Edge case:  there are no words in the line.
         */
        if (word == NULL) continue ;

        //printf("%s\n", word) ;

        /* Each time the loop body is executed, `word` is the next word in the
         * line.
         *
         * Here we're using a standard C idiom that we haven't discussed in
         * class.  The key to understanding the test expression is to realize
         * that in C, assignment is actually a kind of *expression*;
         * evaluating an assignment causes the assignment to the variable
         * to happen, and the value of the assignment expression is the value
         * of the RHS.  So when (word = strtok(NULL, DELIMS)) is evaluated,
         * word is assigned the value of strtok(NULL, DELIMS), and the value
         * of (word = strtok(NULL, DELIMS)) is the value of 
         * strtok(NULL, DELIMS).  So this test has two outcomes:
         * - strtok(NULL, DELIMS) returns NULL, in which case word is assigned
         *   NULL and the test is false, so the loop is done; or
         * - strtok(NULL, DELIMS) returns something that is not-NULL, in which
         *   case that not-NULL value is assigned to word and the test is
         *   true, so the loop body is executed.
         */

        
        while ((word = strtok(NULL, DELIMS)) != NULL) {
            /* word is the next word in the line.
             *
             * So you can see what is happening, I have printed out the word,
             * but you should delete that for your client.
             */
            //printf("%s\n", word) ;
            if (dict_contains(d, word))
            {
                int count = dict_get(d, word);
                dict_add(d, word, count + 1);
            }
            else dict_add(d, word, 1) ;
            //printf("%s\n", word) ;

        }

    }


    //dict_print(d);

    
    /* Release the memory allocated for the line and reset to NULL
     * for the next call to getline().
     */
    free(lineptr) ;
    lineptr = NULL ;

    /* Add your code to print out the list of words with their counts here.
     */
    char** keys = malloc(sizeof(char*) * dict_size(d));

    // invariant: size of keys is at least dict_size(d)
    assert(dict_size(d) <= sizeof(char*) * dict_size(d));
    dict_keys_to_array(d, keys);
    //print the array keys
    //for(int i = 0)
    for ( int i = 0; i < dict_size(d); i++)
    {
        printf("%s: %d\n", keys[i], dict_get(d, keys[i]));

    }
    
    /* Make sure to free *all* resources that have been malloc'd!
     */
    free(keys);
    dict_free(d) ;
    return 0 ;

}
