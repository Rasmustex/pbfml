#ifndef BF_INTERPRETER_H
#define BF_INTERPRETER_H
#ifdef __cplusplus
extern "C" {
#endif 

    #include "cell.h"

    cell* parse_bf( char* program, unsigned int tapesize );
    char* readFile( char* filename ); 

#ifdef __cplusplus
}
#endif 
#endif
