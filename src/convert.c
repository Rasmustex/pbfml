#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "../include/pbfml.h"

void to_html ( cell* c, bfmlFile* f, char* fname ) {

    const char* bold = "<b>";
    const char* boldend = "</b>";

    const char* html = "<!DOCTYPE html>\n<html lang=\"en\">\n<head>\n\t<title>testing</title>\n\t<meta charset=\"uft-8\">\n</head>\n<body>\n<p>\n";
    
    const char* htmend = "</p>\n</body>\n</html>\n";

    cell tempcell = {.lower = 0,
                    .upper = 0};
    cell* currcell;
    cell* prevcell = &tempcell;
    FILE* ht = fopen( fname, "w+" );

    fprintf( ht, "%s", html );
    for( int i = 0; i < f->textlen; i++ ) {
        // go through each cell and print required tags - keep track of whether the previous cell had the same tags
        // so we can avoid wasting file space
    }
    fprintf( ht, "%s", htmend );
    fclose( ht );
}