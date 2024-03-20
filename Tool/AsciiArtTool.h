// .h class for functions

#ifndef HW1_ASCIIART_H
#define HW1_ASCIIART_H

#include "RLEList.h"

/**
* Run Length Encoding List
*
* The following functions are available:
*   asciiArtRead	        - Read file into new RLEList .
*   asciiArtPrint		    - write all the character in RLEList to file .
*   asciiArtPrintEncoded    - wrte the ascii art in ziped way to the file.
*/

/**
 * asciiArtRead : get file from user and convert the file to RLEList
 * 
 * this function use others function from RLEList.h to create a chain of nodes 
 * and enter all the chars from to the file to the node
 * @param in_stream file to read the ascii arrt from him
 * @return
 * -the function return NULL if allocate of node will fail
 * -in case of succes, return pointer to RLEList, and the RLEList is nodes that contain
 *  all the chars from file
*/
RLEList asciiArtRead(FILE* in_stream);

/**
 * asciiArtPrint : write RLEList that present ascii art to new file that given by the user
 * @param RLEList that contain chars of  ascii art picture 
 * @param out_stream that a pointer to the file that the RLEList will 
 * @return RLEListResult that resamble:
 *      -RLE_LIST_NULL_ARGUMENT if the pointer to list was NULL
 *      -RLE_LIST_ERROR f the file pointer is NULL
 *      -RLE_LIST_OUT_OF_MEMORY if allocate memory to ne 
 *      -RLE_LIST_SUCCESS if all going right
*/
RLEListResult asciiArtPrint(RLEList list, FILE *out_stream);

/**
* asciiArtPrintEncoded: Writes the compressed picture into a file.
*
* @param list - The list of the type RLEList containing the values in the picture.
* @param out_stream - The file to be written in
* @return
*   RLE_LIST_NULL_ARGUMENT if one of the given parameters is NULL.
*   RLE_LIST_SUCCESS if writing the compressed picture into the file succeeds.
*/
RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream);

#endif