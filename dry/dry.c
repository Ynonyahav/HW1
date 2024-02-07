//Programming errors1: the error was because the "". I changed it to <>.
//the inclode wite "" is used for local files, and the include with <> is used for system files.
//the origin code is #include "stdlib.h"...
#include <stdlib.h>
#include <string.h>
#include <assert.h>


char* stringDuplicator(char* s, int times){
    //Programming errors2: the use of assert is wrong because the assert is for make sure that the s is not NULL.
    //the origin code is assert(!s);
    assert(s);

    assert(times > 0);

    //Convention error1: LEN was chenged to len because capital letters are used for macros & constants.
    //the origin code is int LEN = strlen(s);
    int len = strlen(s);

    //Programming errors3: the use of malloc is wrong. I changed it to malloc((len*times)+1). 
    //because the size of the string is len*times and we need to add 1 for the null terminator.
    char* out = malloc((len*times)+1);

    //Programming errors4: the use of assert is wrong. I changed it to if.
    //the origin code is assert(out);
    if (!out){
        return NULL;
    }

    //Convention error2: the content of the for loop was need one indentation to the right.
    //Programming errors5: i != times becuase we need to copy the string times times and not times-1.
    //the origin code is for (int i=0; i<=times; i++){
    //Programming errors6: the line strcpy(out,s); need to be before the line out = out + len; because we need to copy the string before we move the pointer.
    for (int i=0; i<times; i++){

        //Programming errors4
        strcpy(out,s);

        out = out + len;
    }
    //Programming errors6: the return value is wrong. I changed it to return out - (len*times).
    //because the pointer out is moved to the end of the string, so we need to move it back to the start of the string.
    //the origin code is return out;
    return out - (len*times);

}