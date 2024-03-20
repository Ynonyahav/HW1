#include "AsciiArtTool.h"
#include "RLEList.h"
#include <stdlib.h>
#include <string.h>

//function 1
RLEList asciiArtRead(FILE* in_stream)
{
    if(in_stream==NULL){
        return NULL;
    }
    RLEList head=RLEListCreate();
    if(head==NULL){
        return NULL;
    }
    char temp_char = '\0';
    while((temp_char = fgetc(in_stream)) !=EOF){
        if(RLEListAppend(head,temp_char)!=RLE_LIST_SUCCESS){
            RLEListDestroy(head);
            return NULL;
        };
    }
    return head;
}

//function 2
RLEListResult asciiArtPrint(RLEList list, FILE *out_stream){
    if(list==NULL){
        return RLE_LIST_NULL_ARGUMENT;
    }
    if(out_stream==NULL){
        return RLE_LIST_ERROR;
    }
    int size_of_rle_list=RLEListSize(list);
    char char_to_write[]=" ";
    RLEListResult result=RLE_LIST_SUCCESS;
    for(int i=0; i<size_of_rle_list; i++){
        char_to_write[0]=RLEListGet(list,i,&result);
        if(fputs(char_to_write,out_stream)==EOF){
            return RLE_LIST_ERROR;
        }
    }
    return RLE_LIST_SUCCESS;
}

RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream) 
{
    if (!list || !out_stream) 
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    RLEListResult result = RLE_LIST_SUCCESS;
    char* outputString = RLEListExportToString(list, &result);
    if (result != RLE_LIST_SUCCESS) 
    {
        return result;
    }
    char* tempString = outputString;
    while (*(tempString))           //Goes through the string term by term.
    {
        fputc(*tempString, out_stream);
        tempString++;
    }
    free(outputString);
    return RLE_LIST_SUCCESS;
}