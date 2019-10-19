#include <stdlib.h>

#include <stdio.h>

#include <string.h>

#include <ctype.h>

struct node_struct {
  void * data;
  struct node_struct * next;
};

typedef struct node_struct Node;

/**
 * 
 * MANDATORY FUNCTIONS
 * 
 **/

struct node_struct * txt2words(FILE * fp);

struct node_struct * search(struct node_struct * list, char * target, int( * compar)(const void *, const void * ));

struct node_struct * copy(struct node_struct * start, struct node_struct * end);

void ftext(FILE * fp, struct node_struct * list);

struct node_struct * sort(struct node_struct * list, int( * compar)(const void *, const void * ));

void remove_repeats(struct node_struct * list, int( * compar)(const void *, const void * ));

int length(struct node_struct * list);

void free_list(struct node_struct * list, int free_data);

/**
 * 
 * HELPER FUNCTIONS
 * 
 **/

void ftextDEBUG(FILE * fp, struct node_struct * list);

struct node_struct * mergeSort(struct node_struct * list, int( * compar)(const void * ,
  const void * ));

int split(struct node_struct * list, struct node_struct ** one, struct node_struct ** two);

struct node_struct * merge(struct node_struct * one, struct node_struct * two, int( * compar)(const void *, const void * ));

struct node_struct * initHead();

int isType1(char * string);

int isAlphaNum(char c);

char * getWord(char ** input);

int lineEnds(char ** string);

int isConditionOne(char * string);

int isConditionTwo(char * string);

int isConditionThree(char * string);

int isConditionFour(char * string);

struct node_struct * headPlusOne(struct node_struct * head);