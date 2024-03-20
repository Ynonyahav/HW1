#include "AsciiArtTool.h"
#include "RLEList.h"
#include <string.h>

//-------------------------this is the map function------------------------------------//
char invert_ascii(char code_char);
//-------------------------------------------------------------------------------------//

int main(int argc,char** argv){
    if(argc<3 || argc>4)      //check that the system gave all the required arguments 
    {  
        return 0;
    }
    char *flag=argv[1];
    char (*invert_ascii_pointer)(char);
    invert_ascii_pointer=invert_ascii;
    RLEListResult result=RLE_LIST_SUCCESS;
    FILE *input= NULL;
    input=fopen(argv[2],"rt");
    if(input == NULL)        // check that the argument of input file is exist
    {  
        result= RLE_LIST_NULL_ARGUMENT;
        return result;
    }
    FILE *output= NULL;
    output=fopen(argv[3],"wt");
    if(output== NULL)
    {
        result= RLE_LIST_NULL_ARGUMENT;
        fclose(input);                 //close input file in case that there is no output file 
        return result;
    }
    if(!strcmp(flag,"-e"))
    {
        RLEList  ascii_art_encoded= asciiArtRead(input);
        result= asciiArtPrintEncoded(ascii_art_encoded,output);
        RLEListDestroy(ascii_art_encoded);
    }
    else if(!strcmp(flag,"-i"))
    {
        RLEList  ascii_art_inverted= asciiArtRead(input);
        RLEListMap(ascii_art_inverted,invert_ascii_pointer);
        result=asciiArtPrint(ascii_art_inverted,output);
        RLEListDestroy(ascii_art_inverted);
    }
    else
    {
        result= RLE_LIST_ERROR;
    }
    fclose(input);
    fclose(output);
    if (result == RLE_LIST_SUCCESS) 
    {
        return result;
    }
    return 0;
}   

char invert_ascii(char code_char){
        if(code_char==' ')
        {
            return '@';
        }
        if(code_char=='@')
        {
            return  ' ';
        }
        return code_char;
    }
