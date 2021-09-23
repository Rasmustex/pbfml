#include <stdio.h>
#include <stdlib.h>
#include "../include/interpreter.h"

int main( int argc, char** argv ) {
    bfmlFile* f = read_file( "test.bfml" );
    cell* c =run_bf( f );

    free( c );
    free( f->program );
    free( f->text );
    free( f );
    return 0;
}