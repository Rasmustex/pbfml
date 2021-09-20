#include <stdio.h>
#include <stdlib.h>
#include "../include/cell.h"
#include "../include/interpreter.h"

int main( int argc, char** argv ) {
    cell* c =parsebf("++[>+<-]>.", 3);
    free( c );
    return 0;
}