#ifndef HW1_RLELIST_H
#define HW1_RLELIST_H


#include "RLEList.h"
#include <stdlib.h>

struct RLEList_t {
    int appears;
    char symbol;
    struct RLEList_t *next;
};

typedef struct RLEList_t *RLEList;

// function number 1
RLEList RLEListCreate(){ //be ready to final check
    RLEList new_node= malloc(sizeof(new_node));
    if(!new_node){
        return NULL;
    }
    new_node->next=NULL;
    new_node->appears=1;
    new_node->symbol='\0';
    return new_node;
}

// function number 2
void RLEListDestroy(RLEList list){ //be ready to final check
    if(list==NULL){
        return;
    }
    RLEList current_node=list;
    while(list->next!=NULL){
        if(current_node->next==NULL){
            free(current_node);
            current_node=list;
            continue;
        }
        current_node=current_node->next;
    }
    free(list);
    return;
}

// function number 3
RLEListResult RLEListAppend(RLEList list, char value){ //be ready to final check
    if((list==NULL)||(value<0)){
        return RLE_LIST_NULL_ARGUMENT;
    }
    RLEList searching_the_last_node=list;
    while((searching_the_last_node->next)!=NULL){
        searching_the_last_node=searching_the_last_node->next;
    }
    if(searching_the_last_node->symbol==value){ // check if the last char equal to the new char
        searching_the_last_node->appears+=1;
        return RLE_LIST_SUCCESS;
    }
    RLEList new_node=RLEListCreate(); //otherwise create new node to store the char
    if(new_node==NULL){
        return RLE_LIST_OUT_OF_MEMORY;
    }
    new_node->symbol=value;
    new_node->appears=1;
    searching_the_last_node->next=new_node;
    return RLE_LIST_SUCCESS;
}

// function number 4
int RLEListSize(RLEList list){ //be ready to final check
    if(list==NULL){
        return -1;
    }
    int symbols_counter=list->appears;
    RLEList current_list=list;
    while(current_list->next!=NULL){
        current_list= current_list->next;
        symbols_counter+= (current_list->appears);
    }
    return symbols_counter;
}

// function number 5
RLEListResult RLEListRemove(RLEList list, int index){ //almost share that be ready to final check
    if((list==NULL)||(index<0)){
        return RLE_LIST_NULL_ARGUMENT;
    }
    if(RLEListSize(list)<index){
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }
    int symbols_counter=list->appears;
    RLEList current_list=list;
    RLEList previous_list=list;
    while(symbols_counter<index){
        previous_list=current_list;
        current_list=current_list->next;
        symbols_counter+=current_list->appears;
    }
    if(current_list->appears>1){
        current_list->appears-=1;
    }
    else{
        if(current_list->next==NULL){
            free(current_list);
            previous_list->next=NULL;
        }
        previous_list->next=current_list->next;
        free(current_list);
    }
    return RLE_LIST_SUCCESS;
}

// function number 6
char RLEListGet(RLEList list, int index, RLEListResult *result){ //should be work
    if((list==NULL)||(index<0)){  // check the input is not null
        if(result!=NULL){
            *result=RLE_LIST_NULL_ARGUMENT;
        }
        return 0;
    }
    if(RLEListSize(list)<index){ // check the index in bounds of list
        if(result!=NULL){
            *result=RLE_LIST_INDEX_OUT_OF_BOUNDS;
        }
        return 0;
    }
    int apears_counter=list->appears;
    RLEList current_node=list;
    while(apears_counter<index){
        current_node=current_node->next;
        apears_counter+=current_node->appears;
    }
    result=RLE_LIST_SUCCESS;
    return current_node->symbol;
}

//function 7
char* RLEListExportToString(RLEList list, RLEListResult* result){
    if(list==NULL){  // check the input is not null
        if(result!=NULL){
            *result=RLE_LIST_NULL_ARGUMENT;
        }
        return NULL;
    }
    RLEList ziped_list=RLEListCreate();
    ziped_list->appears=list->appears;
    ziped_list->symbol=list->symbol;
    RLEList pointer_to_list=list;
    while(pointer_to_list!=NULL){ //comprese the list to ziped_list
        pointer_to_list=pointer_to_list->next;
        *result=RLEListAppend(ziped_list,pointer_to_list->appears);
        if(*result==RLE_LIST_OUT_OF_MEMORY){
            return NULL;
        }
    }
    int node_counter=1;
    RLEList current_list=ziped_list;
    while(current_list->next!=NULL){ // count the number of node in the ziped_list
        current_list= current_list->next;
        node_counter+=1;
    }
    char *new_ziped_string=malloc(sizeof(char)*node_counter*3);
    if(new_ziped_string==NULL){
        *result=RLE_LIST_OUT_OF_MEMORY;
        return NULL;
    }
    new_ziped_string[0]=ziped_list->symbol; //starting to enter the value into the string
    new_ziped_string[1]=ziped_list->appears;
    new_ziped_string[2]='\n';
    int index_of_ziped_string=3;
    while(ziped_list->next!=NULL){
        ziped_list=ziped_list->next;
        new_ziped_string[0+index_of_ziped_string]=ziped_list->symbol;
        new_ziped_string[1+index_of_ziped_string]=ziped_list->appears;
        new_ziped_string[2+index_of_ziped_string]='\n';
        index_of_ziped_string+=3;
    }
    result=RLE_LIST_SUCCESS;
    return new_ziped_string;
}

//function number 8
RLEListResult RLEListMap(RLEList list, MapFunction map_function){
    if(list==NULL){                // check the input is not null
        return RLE_LIST_NULL_ARGUMENT;
    }
    int size_of_list= RLEListSize(list);
    RLEList current_node= list;
    current_node->symbol=map_function(current_node->symbol);
    while(current_node->next!=NULL){
        current_node= current_node->next;
        current_node->symbol=map_function(current_node->symbol);
    }
    return RLE_LIST_SUCCESS;
}


int main(){
    printf("all right");
    return 0;
}


#endif // HW1_RLELIST_H