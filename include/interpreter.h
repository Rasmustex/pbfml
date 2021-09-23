#ifndef BF_INTERPRETER_H
#define BF_INTERPRETER_H
#ifdef __cplusplus
extern "C" {
#endif 

    #include "cell.h"
    #include "file.h"

    cell* run_bf( bfmlFile* f );

    char* readFile( char* filename ); 

#ifdef __cplusplus
}
#endif 
#endif
