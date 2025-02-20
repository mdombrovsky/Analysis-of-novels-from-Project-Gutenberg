#include "text.h"

/**
 * Splits a list into 2 sub lists
 **/
int split(struct node_struct * list, struct node_struct ** one, struct node_struct ** two) {

    int i;
	int len = length(list);

	/*Set one to be the original list*/
    ( * one) = list;

    /*If it already a single item list, exit*/
    if (list -> next == NULL) {
      /*Already Split up*/
	  ( * two) = NULL;
      return 1;
    }

    /*Find end of first list*/
    for (i = 0; i < (len / 2) - 1; i++) {
      list = list -> next;
    }

    /*Create second list*/
    ( * two) = list -> next;
    list -> next = NULL;

    return 0;
}

/**
 * Sorts a linked list
 **/
struct node_struct * sort(struct node_struct * list, int( * compar)(const void *, const void * )) {

    Node * copiedList;

    /*Creates copy that I can mess around with*/
    copiedList = copy(list, NULL);

    return mergeSort(copiedList, compar);
}

/**
 * Merge sort implementation of sorting a linked list
 **/
struct node_struct * mergeSort(struct node_struct * list, int( * compar)(const void *, const void * )) {

	Node * one;
	Node * two;

	if (list == NULL) {
		return list;
	}

	if ((list -> next) == NULL) {
		return list;
	}

	/*Splits up list*/
	split(list, & one, & two);

	/*Recursivley sorts it*/
	one = mergeSort(one, compar);
	two = mergeSort(two, compar);

	return merge(one, two, compar);

}

/**
 * Merges sorted sub lists into a sorted list
 **/
struct node_struct * merge(struct node_struct * one, struct node_struct * two, int( * compar)(const void * , const void * )) {

	Node * head;
	Node * node;
	Node * temp;

	head = initHead();
	node = head;

	/*While both are not null*/
	while (one != NULL && two != NULL) {

		/*Make sure that the data is not null
		*This should never be executed
		*But I have it in here because I dont like segmentation faults
		*/
		if (one -> data == NULL) {
		temp = one;
		one = one -> next;
		temp -> next = NULL;
		free_list(temp, 0);
		continue;
		}

		if (two -> data == NULL) {
		temp = two;
		two = two -> next;
		temp -> next = NULL;
		free_list(temp, 0);
		continue;
		}

		/*Decides what next element of list will be*/
		if ((( * compar)((void * ) one -> data, (void * ) two -> data)) <= 0) {
		node -> next = one;
		node = one;
		one = one -> next;
		node -> next = NULL;

		} else {
		node -> next = two;
		node = two;
		two = two -> next;
		node -> next = NULL;
		}
	}

	/*If one is not null*/
	while (one != NULL) {
		/*Make sure that the data is not null*/
		if (one -> data == NULL) {
		temp = one;
		one = one -> next;
		temp -> next = NULL;
		free_list(temp, 0);
		continue;
		}
		node -> next = one;
		node = one;
		one = one -> next;
		node -> next = NULL;

	}

	/*If two is not  null*/
	while (two != NULL) {
		/*Make sure that the data is not null*/
		if (two -> data == NULL) {
		temp = two;
		two = two -> next;
		temp -> next = NULL;
		free_list(temp, 0);
		continue;
		}
		node -> next = two;
		node = two;
		two = two -> next;
		node -> next = NULL;

	}

	return headPlusOne(head);
}

/**
 * Reads in text from file and stores it in a linked list
 **/
struct node_struct * txt2words(FILE * fp) {
	const char blank[10] = "\n";
	Node * head;
	Node * node;
	char * data;
	char * toFree;
	char * string;

	head = initHead();

	node = head;

	string = (char * ) malloc(sizeof(char) * 257);
	toFree = string;


	while (fgets(string, 257, fp) != NULL) {

		/*If first line is a blank line*/
		if (lineEnds( & string) == 1) {
		data = malloc(strlen(blank) + 1);
		strcpy(data, blank);
		node -> next = malloc(sizeof(Node));
		node = node -> next;
		node -> data = data;
		node -> next = NULL;

		} else {
		/*Add nodes*/
		while (lineEnds( & string) != 1) {

			node -> next = malloc(sizeof(Node));
			node = node -> next;
			node -> data = getWord( & string);
			node -> next = NULL;
		}
		}

		if (toFree) {
		free(toFree);
		toFree = NULL;
		}

		string = (char * ) malloc(sizeof(char) * 257);
		toFree = string;

	}

	/*Frees string*/
	if (toFree) {
		free(toFree);
		toFree = NULL;

	}

	return headPlusOne(head);
}

/**
 * Initializes head pointer
 **/
struct node_struct * initHead() {
	Node * head;

	/*Allocate the head*/
	head = malloc(sizeof(Node));
	head -> data = NULL;
	head -> next = NULL;
	return head;
}

/**
 * Discards current head and returns the next element
 */
struct node_struct * headPlusOne(struct node_struct * head) {
	Node * node;
	/*This is the easiest way */
	node = head -> next;

	if ((head -> data) != NULL) {
		free(head -> data);
		head -> data = NULL;
	}
	if (head != NULL) {
		free(head);
		head = NULL;
	}
	return node;

}

/**
 * Copies data pointers into a new list
 **/
struct node_struct * copy(struct node_struct * start, struct node_struct * end) {
	Node * head;
	Node * node;
	Node * toCopy;

	head = initHead();

	node = head;

	toCopy = start;

	while (toCopy != NULL && (toCopy != end)) {
		node -> next = malloc(sizeof(Node));
		node = node -> next;
		node -> data = toCopy -> data;
		node -> next = NULL;
		toCopy = toCopy -> next;

	}

	return headPlusOne(head);

}

/**
 * Removes repeated values 
 **/
void remove_repeats(struct node_struct * list, int( * compar)(const void *, const void * )) {

	Node * node;
	Node * prevNode;

	/*While the list is not null*/
	while (list != NULL) {
		/*While the list data is not null*/
		if (list -> data != NULL) {

			/*Keep track of last node*/
			prevNode = list;
			node = prevNode -> next;

			while (node != NULL) {
				if (node -> data != NULL) {

				/*If same value is found*/
				if ((( * compar)((void * ) list -> data, (void * ) node -> data)) == 0) {
					prevNode -> next = node -> next;
					node -> next = NULL;
					free_list(node, 0);
					node = prevNode -> next;
				} else {
					prevNode = node;
					node = prevNode -> next;
				}

				} else {
				prevNode = node;
				node = prevNode -> next;
				}

			}
		}

		/*Increments list*/
		list = list -> next;
	}

}

/**
 * Creates a list of all found terms
 **/
struct node_struct * search(struct node_struct * list, char * target, int( * compar)(const void *, const void * )) {

	Node * head;
	Node * node;

	head = initHead();
	node = head;

	/*Goes through list*/
	while (list != NULL) {
		if (list -> data != NULL) {
		if (( * compar)((void * ) list -> data, (void * ) target) == 0) {
			/*Found*/
			node -> next = malloc(sizeof(Node));
			node = node -> next;
			node -> data = list;
			node -> next = NULL;
		}

		}

		list = list -> next;
	}

	return headPlusOne(head);
}

/**
 * If line ends
 **/
int lineEnds(char ** string) {

	/*Gets rid of spaces*/
	while (((** string) == ' ')) {
		( * string) ++;
	}


	if (( ** (string) == '\n') || (( ** string) == '\0') || (( ** string) == '\r')) {
		( * string) ++;
		return 1;
	}
	return 0;

}

/**
 * Returns length of list
 **/
int length(struct node_struct * list) {
	int count = 0;
	while (list != NULL) {
		list = list -> next;
		count++;
	}
	return count;
}

/**
 * Prints output to file
 */
void ftext(FILE * fp, struct node_struct * list) {

	int characters = 0;
	int isNewLine;

	while (list != NULL) {
		if (list -> data != NULL) {
		/*1. Print current word
		*2. Check if you add a white space
		*3. Determine if it is a space or newline
		*/
	
			isNewLine=0;
			if (((* ((char * ) list -> data) == '\n'))) {
				fprintf(fp, "\n");
				if(characters != 0){
					fprintf(fp, "\n");
					
				}				
				characters = 0;
				isNewLine=1;
			} else if ((((* ((char * ) list -> data) == '\r')))&&(* ((char * ) (list + 1) -> data) == '\n')) {

			}
			else {
				characters += strlen((char * ) list -> data);
				/*1. Print current word*/
				fprintf(fp, "%s", (char * ) list -> data);
			}

			/*2. Check if you add a white space*/
			if ((list -> next != NULL) && (isNewLine ==0)) {
				if (list -> next -> data != NULL) {
					
					if (((isConditionOne((char * ) list -> data) && (isConditionTwo((char * ) list -> next -> data))==0)) || ((isConditionThree((char * ) list -> data) && isConditionFour((char * ) list -> next -> data)))) {

						/*3. Determine if it is a space or newline*/
						if ((characters + strlen((char * ) list -> next -> data) + 1) < 80) {

							/*Space*/
							fprintf(fp, " ");
							characters++;
						} else {

							/*New line*/
							fprintf(fp, "\n");
							/*fprintf(fp, "***CHARACTERS: %d\n", characters);*/
							
							characters = 0;
						}

					}
				}
			
			}

		}
		list = list -> next;

	}

}

/**
 * Prints output to file, one item per line
 **/
void ftextDEBUG(FILE * fp, struct node_struct * list) {

	while (list != NULL) {
		if (list -> data != NULL) {

		fprintf(fp, "%s\n", (char * ) list -> data);

		}
		list = list -> next;

	}

}

/**
 * If word is (,) or (;) or (!) or (") or (.)
 **/
int isConditionOne(char * string) {
	if(strlen(string) == 1){
  		return ((((*string) == ',') + ((*string) == ';') + ((*string) == '!') + ((*string) == '"') + (strcmp(string, "”") == 0) + (strcmp(string, "“") == 0) + ((*string) == '.')));
	}

	return ((strcmp(string, "”") == 0) || (strcmp(string, "“") == 0));
}

/**
 * If word is (") or (--)
 **/
int isConditionTwo(char * string) {
	if(strlen(string) == 1){
  		return ((((*string) == '"') || (strcmp(string, "”") == 0) || (strcmp(string, "“") == 0)  || (((*string) == '-') && ((*(string+1)) == '-'))));

	}

	return ((strcmp(string, "”") == 0) || (strcmp(string, "“") == 0));
}

/**
 * If last character is a letter or a number
 **/
int isConditionThree(char * string) {
	if (strlen(string) < 1) {
		return 0;
	}
	return isAlphaNum(string[strlen(string) - 1]);
}

/**
 * If first character is a letter or a number
 **/
int isConditionFour(char * string) {
  	return isAlphaNum(string[0]);
}

/**
 * Searches for words using string
 **/
char * getWord(char ** string) {
	int count;

	char * subString;
	char * data;
	char unique;
	count = 0;

	/*Gets rid of spaces*/
	while (( ** string) == ' ') {
		( * string) ++;
	}

	if (isType1( * string)) {

		subString = * string;

		while (isType1( * string)) {
		( * string) ++;
		count++;
		}
		data = malloc(count + 1);
		strncpy(data, subString, count);
		data[count] = '\0';

	} else {
		subString = * string;

		unique = ** string;
		while ( ** string == unique) {
		( * string) ++;
		count++;
		}
		data = malloc(count + 1);

		data[count] = '\0';
		strncpy(data, subString, count);

	}


	return data;

}

/**
 * If free data is 0 dont free data, otherwise free data
 * Free list regardless
 */
void free_list(struct node_struct * list, int free_data) {
	Node * temp;

	while (list != NULL) {
		temp = list;

		list = list -> next;

		if (free_data != 0) {
		if (temp -> data) {

			free(temp -> data);
			temp -> data = NULL;
		}
		}

		if (temp) {
		free(temp);
		temp = NULL;
		}

	}

}

/**
 * If a string is a word
 **/
int isType1(char * string) {
	if ((isAlphaNum( * string)) || (( * (string) == '\'') && ( * (string + 1) != ('\''))) || (( * (string) == '-') && (( * (string + 1) != ('-'))))) {
		return 1;
	} else {
		return 0;
	}
}

/**
 * If character is alphanumeric
 **/
int isAlphaNum(char c) {
  	return (isdigit(c) || isalpha(c));
}