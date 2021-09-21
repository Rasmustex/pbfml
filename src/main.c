#include <stdio.h>
#include <stdlib.h>
#include "../include/interpreter.h"
#include "../include/file.h"

int main( int argc, char** argv ) {
    bfmlFile* f = read_file( "test.bfml" );
    cell* c =parse_bf(f->program, f->textlen);

    free( c );
    free( f->program );
    free( f->text );
    free( f );
    return 0;
}