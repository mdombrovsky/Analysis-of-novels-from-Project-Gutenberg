#include "text.h"

struct node_struct *txt2words( FILE *fp ){
    const char blank [10]="\n";
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

void ftext( FILE *fp, struct node_struct *list ){

    /*int characters=0;*/

    while(list!=NULL){
        if(list->data!=NULL){
            
            /*1. Print current word
             *2. Check if you add a white space
             *3. Determine if it is a space or newline
             */

            /*1. Print current word*/
            fprintf(fp,"%s\n",(char*)list->data);


            /*This part for later*/
            /*if(*((char*)list->data)=='\n'){
                characters=0;
            } else{
                characters+=strlen((char*)list->data);
            }*/

            /*2. Check if you add a white space*/
            /*if(list->next!=NULL){
                if(list->next->data!=NULL){
                    if((isConditionOne((char*)list->data)&&!isConditionTwo((char*)list->next->data))||(isConditionThree((char*)list->data)&&isConditionFour((char*)list->next->data))){

                        *//*3. Determine if it is a space or newline*/
                        /*if((characters+strlen((char*)list->next->data)+1)<80){

                            *//*Space*//*
                            fprintf(fp," ");
                            characters++;
                        } else{
                            
                            *//*New line*//*
                            fprintf(fp,"***CHARACTERS: %d\n",characters);
                            characters=0;
                        }

                    }
                }
            }*/

        }
        list=list->next;

    }

}

/**
 * If word is (,) or (;) or (!) or (") or (.)
 **/ 
int isConditionOne(char *string){
    /*switch(*string){
        case ',': case ';': case: '!': case '\"': case ".":
            return 1;
        default:
            return 0;
    }*/
    return(strcmp(string,",")*strcmp(string,";")*strcmp(string,"!")*strcmp(string,"\"")*strcmp(string,".")==0)?1:0;
}

/**
 * If word is (") or (--)
 **/
int isConditionTwo(char *string){
    return(strcmp(string,"\"")*strcmp(string,"--")==0)?1:0;
}

/**
 * If last character is a letter or a number
 **/
int isConditionThree(char *string){
    if(strlen(string)<1){
        return 0;
    }
    return isAlphaNum(string[strlen(string)-1]);
}

/**
 * If first character is a letter or a number
 **/
int isConditionFour(char *string){
    return isAlphaNum(string[0]);
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