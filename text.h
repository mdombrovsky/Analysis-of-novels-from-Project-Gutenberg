#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

struct node_struct{
    void *data;
    struct node_struct *next;
};

typedef struct node_struct Node;

/**
 * 
 * MANDATORY FUNCTIONS
 * 
 **/

/*Done*/
struct node_struct *txt2words( FILE *fp ); 

/*Done*/
struct node_struct *search( struct node_struct *list, char *target, int (*compar)(const void *, const void *) ); 

/*Done*/
struct node_struct *copy( struct node_struct *start, struct node_struct *end ); 

/*Done*/
void ftext( FILE *fp, struct node_struct *list ); 

struct node_struct *sort( struct node_struct *list, int (*compar)(const void *, const void *) ); 

void remove_repeats ( struct node_struct *list, int (*compar)(const void *, const void *) ); 

/*Done*/
int length( struct node_struct *list ); 

/*Done*/
void free_list( struct node_struct *list, int free_data ); 


/**
 * 
 * HELPER FUNCTIONS
 * 
 **/

struct node_struct *initHead();

int isType1(char *string);

int isAlphaNum (char c);

char *getWord(char **input);

int lineEnds (char **string);

int isConditionOne(char *string);

int isConditionTwo(char *string);

int isConditionThree(char *string);

int isConditionFour(char *string);

struct node_struct *headPlusOne(struct node_struct *head);