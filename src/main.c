#include <stdio.h>
#include <stdlib.h>
#include "../include/interpreter.h"

int main( int argc, char** argv ) {
    cell* c =parse_bf("+++++31.", 3);
    free( c );
    return 0;
}