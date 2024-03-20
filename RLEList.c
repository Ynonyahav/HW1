#include "RLEList.h"
#include <stdlib.h>
#include <string.h>

//--------------------------------list of aid functions---------------------------------------

RLEList listToZipList(RLEList list, RLEListResult* result);// for given list return new list that ziped in RLE way
int NodeCounter(RLEList list);                             //for given list ,count the number of nodes
int NumOfDigits(RLEList list);                             //count all the digit in all the appeares    
int IntToString(int appears, int index, char* string);     //convert large int to string digit by digit

//--------------------------------------------------------------------------------------------

struct RLEList_t 
{
    int appears;
    char symbol;
    struct RLEList_t *next;
};

//---------------------------------all functions here------------------------------------------------//

// function number 1
RLEList RLEListCreate()
{
    RLEList new_node= malloc(sizeof(new_node));
    if(!new_node)
    {
        return NULL;
    }
    new_node->next=NULL;
    new_node->appears=0;
    new_node->symbol='\0';
    return new_node;
}

// function number 2
void RLEListDestroy(RLEList list){
    if(list==NULL){
        return;
    }
    RLEList previous_node=list;
    while(list!=NULL){
        list=list->next;
        free(previous_node);
        previous_node=list;
    }
    return;
}

// function number 3
RLEListResult RLEListAppend(RLEList list, char value){ 
    if((list==NULL)||(value<0)||(value>255))
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    if(list->appears==0)             //check if its the initial_index node
    {
        list->symbol=value;
        list->appears=1;
        return RLE_LIST_SUCCESS;
    }
    RLEList searching_the_last_node=list;
    while((searching_the_last_node->next)!=NULL)
    {
        searching_the_last_node=searching_the_last_node->next;
    }
    if(searching_the_last_node->symbol==value)    //check if the last node contain same value
    {
        searching_the_last_node->appears++;
        return RLE_LIST_SUCCESS;
    }
    RLEList new_node=RLEListCreate(); //otherwise create new node to store the char inside
    if(new_node==NULL)
    {
        return RLE_LIST_OUT_OF_MEMORY;
    }
    new_node->symbol=value;
    new_node->appears=1;
    searching_the_last_node->next=new_node;
    return RLE_LIST_SUCCESS;
}

// function number 4
int RLEListSize(RLEList list){  //this function work for every size of each node
    if(list==NULL)              //its mean that he sum all the appears together
    {   
        return -1;
    }
    int symbols_digit_counter=list->appears;
    while(list->next!=NULL)
    {
        list=list->next;
        symbols_digit_counter+= (list->appears);
    }
    return symbols_digit_counter;
}

// function number 5                                  
RLEListResult RLEListRemove(RLEList list, int index){ 
    if((list==NULL)||(index<0)){
        return RLE_LIST_NULL_ARGUMENT;
    }
    if(RLEListSize(list)-1<index){
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }
    int symbols_digit_counter=list->appears-1;
    RLEList current_node_list=list;
    RLEList previous_list=list;
    while(symbols_digit_counter<index)
    {
        previous_list=current_node_list;
        current_node_list=current_node_list->next;
        symbols_digit_counter+=current_node_list->appears;
    }
    if(current_node_list->appears>1)
    {
        current_node_list->appears-=1;
    }
    else
    {
        if(current_node_list->next==NULL)
        {
            free(current_node_list);
            previous_list->next=NULL;
        }
        previous_list->next=current_node_list->next;
        free(current_node_list);
    }
    return RLE_LIST_SUCCESS;
}

// function number 6
char RLEListGet(RLEList list, int index, RLEListResult *result)
{
    if((list==NULL)||(index<0))      // check the input is not null
    {
        if(result!=NULL)
        {
            *result=RLE_LIST_NULL_ARGUMENT;
        }
        return 0;
    }
    int list_size=RLEListSize(list);
    if(list_size-1<index)   // check the index in bounds of list
    { 
        if(result!=NULL)
        {
            *result=RLE_LIST_INDEX_OUT_OF_BOUNDS;
        }
        return 0;
    }
    int symbols_digit_counter=list->appears-1;
    while(symbols_digit_counter<index)
    {
        list=list->next;
        symbols_digit_counter+=list->appears;
    }
    result=RLE_LIST_SUCCESS;
    return list->symbol;
}

//function 7
char* RLEListExportToString(RLEList list, RLEListResult* result)
{
    RLEList ziped_list=listToZipList(list,result);   //already checks that the argument are not null
    if(ziped_list==NULL)
    {
        return NULL;
    }
    int sum_of_digits=NumOfDigits(ziped_list);
    int sum_of_nodes=NodeCounter(ziped_list);
    char *ziped_string=malloc(sum_of_digits+(sum_of_nodes*2)+1);
    int index_of_string=0;
    while(ziped_list!=NULL)
    {
        ziped_string[index_of_string++]=ziped_list->symbol;
        index_of_string=IntToString(ziped_list->appears,index_of_string,ziped_string);
        ziped_string[index_of_string++]='\n';
        ziped_list=ziped_list->next;
    }
    RLEListDestroy(ziped_list);
    ziped_string[sum_of_digits+(sum_of_nodes*2)]='\0';
    return ziped_string;
}

//function number 8
RLEListResult RLEListMap(RLEList list, MapFunction map_function){
    if(list==NULL || map_function==NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    RLEList current_node_node= list;
    current_node_node->symbol=map_function(current_node_node->symbol);
    while(current_node_node->next!=NULL)
    {
        current_node_node= current_node_node->next;
        current_node_node->symbol=map_function(current_node_node->symbol);
    }
    return RLE_LIST_SUCCESS;
}


//---------------alot of aid function that help to function 7--------------------------//

//aid function1 to function7
RLEList listToZipList(RLEList list, RLEListResult* result){//convert normal list to ziped list
    if(list==NULL)                                         // check the input is not null
    {           
        if(result!=NULL)
        {
            *result=RLE_LIST_NULL_ARGUMENT;
        }
        return NULL;
    }
    RLEList ziped_list=RLEListCreate();
    if(ziped_list==NULL)
    {       
        if(result!=NULL)
        {
            *result=RLE_LIST_OUT_OF_MEMORY;
        }
        return NULL;
    }
    ziped_list->appears=list->appears;
    ziped_list->symbol=list->symbol;
    int size_of_list=RLEListSize(list);
    char temp_char='\0';
    RLEListResult result2=RLE_LIST_SUCCESS;
    *result=RLE_LIST_SUCCESS;
    for(int i=list->appears;i<size_of_list;i++)
    {
        temp_char=RLEListGet(list,i,result);
        if(*result!=RLE_LIST_SUCCESS)
        {
            return NULL;
        }
        result2=RLEListAppend(ziped_list,temp_char);
        if(result2!=RLE_LIST_SUCCESS)
        {
            return NULL;
        }
    }
    return ziped_list;
}

//aid function2 to function7
int NodeCounter(RLEList list)  //count all the node in the list
{    
    if(list==NULL)
    {
        return 0;
    }
    int node_counter=1;
    while(list->next!=NULL)
    {
        node_counter+=1;
        list=list->next;
    }
    return node_counter;
}

//aid function3 to function7
int NumOfDigits(RLEList list)  //count all the digit in all the appeares
{
    int appears = 0, digit_counter = 0;
    RLEList current_node = list;
    while(current_node)
     {
        appears = current_node->appears;
        while(appears > 0) 
        {
            appears /= 10;
            digit_counter++;
        }
        current_node = current_node->next;
    }
    return digit_counter;
}

//aid function4 to function7
int IntToString(int appears, int index, char* string)  //convert large int to string digit by digit
{
    int initial_index = index;
    char temp_char = '\0';
    while(appears > 0) 
    {
        string[index] = (appears % 10) + 48;  //this is convert the int to his ascii value
        appears /= 10;                        //bcs 0 its 48 in ascii and so on
        index++;
    }
    for(int i = 0; i < (index - initial_index)/2; i++)  //mirroring the string number u get
    {
        temp_char = string[initial_index + i];
        string[initial_index + i] = string[index - i - 1];
        string[index - i - 1]  = temp_char;
    }
    return index;     //Returns the next open index in the string.
}
