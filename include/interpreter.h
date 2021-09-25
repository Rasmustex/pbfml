#ifndef BF_INTERPRETER_H
#define BF_INTERPRETER_H
#ifdef __cplusplus
extern "C" {
#endif 

    #include "cell.h"
    #include "file.h"
    #include "convert.h"

    cell* run_bf( bfmlFile* f );

#ifdef __cplusplus
}
#endif 
#endif
