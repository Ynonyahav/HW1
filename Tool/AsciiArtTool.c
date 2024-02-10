#include <stdio.h>
#include <stdlib.h>
#include "RLEList.h"
#include "AsciiArtTool.h"


RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream) 
{
    if (!list || !out_stream) {
        return RLE_LIST_NULL_ARGUMENT;
    }
    RLEListResult result = RLE_LIST_SUCCESS;
    char* outputString = RLEListExportToString(list, &result);
    if (result != RLE_LIST_SUCCESS) {
        return result;
    }
    char* tempString = outputString;
    //Goes through the string term by term.
    while (*(tempString + 3)) {
        fputc(*tempString, out_stream);
        tempString++;
    }
    free(outputString);
    return RLE_LIST_SUCCESS;
}

// RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream){
//     if(list==NULL){
//         return RLE_LIST_NULL_ARGUMENT;
//     }
//     RLEList current_node=list;
//     while(current_node!=NULL){
//         if(current_node->appears>1){
//             fprintf(out_stream,"%d%c",current_node->appears,current_node->symbol);
//         }
//         else{
//             fputc(current_node->symbol,out_stream);
//         }
//         current_node=current_node->next;
//     }
//     return RLE_LIST_SUCCESS;
// }
