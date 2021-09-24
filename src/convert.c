#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "../include/interpreter.h"

void to_html ( cell* c, bfmlFile* f, char* fname ) {
    cell tempcell = {.lower = 0,
                    .upper = 0};
    cell* currcell;
    cell* prevcell = &tempcell;
    FILE* ht = fopen( fname, "w+" );

    fprintf( ht, "%s", html );
    for( int i = 0; i < f->textlen; i++ ) {
        currcell = (c + i);
        //check if state is the same pls 
        if( !compare_cells( currcell, prevcell ) ) {
            // don't change state 
        } else {
            if( currcell->upper & TEXT_BOLD && !(prevcell->upper & TEXT_BOLD) );
                // fprintf(ht, "%s", bold);
            else if (prevcell->upper & TEXT_BOLD);
                // fprintf(ht, "%s", boldend);
        }
        // if((c + i)->upper & TEXT_BOLD) {
        //     // do bold text
        // }
        // if((c + i)->upper & TEXT_ITALICS) {
        //     // do italics
        // }
        // if((c + i)->upper & TEXT_UNDERLINE) {
        //     // do underline
        // }
        prevcell = currcell;
    }
    // fprintf( ht, "%s", htmend );
    fclose( ht );
}