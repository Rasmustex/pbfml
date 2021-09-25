#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "../include/pbfml.h"


// use spans for font size change 
void to_html ( cell* c, bfmlFile* f, char* fname ) {

    cell tempcell = {.lower = 0,
                    .upper = 0};
    cell* currcell;
    cell* prevcell = &tempcell;
    FILE* ht = fopen( fname, "w+" );

    fprintf( ht, "<!DOCTYPE html>\n<html lang=\"en\">\n<head>\n\t<title>%s</title>\n\t<meta charset=\"utf-8\">\n</head>\n<body>\n<p>\n", fname );
    for( int i = 0; i < f->textlen; i++ ) {
        currcell = c + i;

        // go through each cell and print required tags - keep track of whether the previous cell had the same tags
        // so we can avoid wasting file space
        /*
         * checking state
         */
        // bold 
        
        if( (currcell->upper & TEXT_BOLD) ) {
            if( !(prevcell->upper & TEXT_BOLD) )
                fprintf( ht, "<b>" );
        } else if( prevcell->upper & TEXT_BOLD )
            fprintf( ht, "</b>");

        //italics
        if( (currcell->upper & TEXT_ITALICS) ) {
            if( !(prevcell->upper & TEXT_ITALICS) )
                fprintf( ht, "<em>" );
        } else if( prevcell->upper & TEXT_ITALICS )
            fprintf( ht, "</em>");

        // underline 
        if( (currcell->upper & TEXT_UNDERLINE) ) {
            if( !(prevcell->upper & TEXT_UNDERLINE) )
                fprintf( ht, "<u>" );
        } else if( prevcell->upper & TEXT_UNDERLINE )
            fprintf( ht, "</u>");

        // print the character or line break
        if( *(f->text + i) == '\n' )
            fprintf( ht, "<br>\n" );
        else if( *(f->text + i ) == '<' )
            fprintf( ht, "&lt;" );
        else if( *(f->text + i) == '>' )
            fprintf( ht, "&gt;");
        else
            fprintf( ht, "%c", *(f->text + i) );
        prevcell = currcell;
    }
    fprintf( ht, "</p>\n</body>\n</html>\n" );
    fclose( ht );
}