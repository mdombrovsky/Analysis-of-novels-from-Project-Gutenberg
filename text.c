#include "text.h"

struct node_struct *txt2words( FILE *fp ){
    const char blank [100]="BLANK LINE";
    Node *head;
    Node* node;
    char *data;
    int count;
    char *toFree;
    char *string;
    head=NULL;
    /*Allocate the head*/
    head=malloc(sizeof(Node));
    head->data=NULL;
    node=head;
    node->next=NULL;



    string=(char*)malloc(sizeof(char)*257);
    toFree=string;

    count=0;

    /*Count is how many times this should be executed for debugging*/
    while(fgets(string,257,fp)!=NULL&&count>=0){       

        count++;

        /*If first line is a blank line*/
        if(lineEnds(&string)==1){
            data=malloc(strlen(blank)+1);
            strcpy(data,blank);
            node->next=malloc(sizeof(Node));
            node=node->next;
            node->data=data;
            node->next=NULL;
        
        } else{
            /*Add nodes*/
            while(lineEnds(&string)!=1){

                node->next=malloc(sizeof(Node));
                node=node->next;
                node->data=getWord(&string);
                node->next=NULL;
            }
        }

        if(toFree){
            free(toFree);
            toFree=NULL;
        }
        string=(char*)malloc(sizeof(char)*257);
        toFree=string;

    }

    if(toFree){
        free(toFree);
        toFree=NULL;

    }
   
    /*This is the easiest way */
    node=head->next;

    if((head->data)!=NULL){
        free(head->data);
        head->data=NULL;
    }
    if(head!=NULL){
        free(head);
        head=NULL;
    }
    return node;
}

int lineEnds (char **string){
    
    /*Gets rid of spaces*/
    while(**string==' '){
        (*string)++;
    }
    if((**(string)=='\n')||((**string)=='\0')){
        (*string)++;
        return 1;
    }
    return 0;

}

char *getWord(char **string){
    int count;
    
    char *subString;
    char *data;
    char unique;
    count=0;

    /*Gets rid of spaces*/
    while((**string)==' '){
        (*string)++;
    }

    if(isType1(*string)){
        
        subString=*string;
     
        while(isType1(*string)){
            (*string)++;
            count++;
        }
        data=malloc(count+1);
        strncpy(data,subString,count);
        data[count]='\0';
        /*printf("Data: |%s|\n",data);*/
  
    } else {
        subString=*string;

        unique=**string;
        while(**string==unique){
            (*string)++;
            count++;
        }
        data=malloc(count+1);

        data[count]='\0';
        strncpy(data,subString, count);
        /*printf("Data: |%s|\n",data);*/



    }
    return data;
    


}

/**
 * If free data is 0 dont free data 
 */
void free_list( struct node_struct *list, int free_data ){
    Node *temp;

    /*printf ("Free list\n");*/
    while(list!=NULL){
        temp=list;
    
        list=list->next;
        /*printf("Freeing: %s\n",(char*) temp->data);*/

        if(free_data!=0){
            if(temp->data){
                /*printf("Freed\n");*/

                free(temp->data);
                temp->data=NULL;
            }
        }

        if(temp){
            free(temp);
            temp=NULL;
        }

    }


}



int isType1(char *string){
    if((isAlphaNum(*string))||((*(string)=='\'')&&((*(string+1)==('-'))||(isAlphaNum(*(string+1)))))||((*(string)=='-')&&((*(string+1)==('\''))||(isAlphaNum(*(string+1))))))
    {
        return 1;
    } else{
        return 0;
    }
}

int isAlphaNum (char c){
    return (isdigit(c)||isalpha(c));
}