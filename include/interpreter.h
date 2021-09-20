#ifndef BF_INTERPRETER_H
#define BF_INTERPRETER_H
#include "cell.h"

cell* parsebf( char* program, unsigned int tapesize );
char* readFile( char* filename ); 

#endif
