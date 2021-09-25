#include <stdio.h>
#include <stdlib.h>
#include "../include/pbfml.h"

int main( int argc, char** argv ) {
    bfmlFile* f = read_file( "test.bfml" );
    if( !f->proglen ) {
		printf("Error: no program on 1st line");
        if( f->textlen )
            free( f->text );
	} else if( !f->textlen ) {
        printf("Error: no text to be marked up");
        free( f->program );
    } else {
    cell* c =run_bf( f );
    to_html( c, f, "test.html");
    free( c );
    free( f->program );
    free( f->text );
    }
    free( f );
    return 0;
}