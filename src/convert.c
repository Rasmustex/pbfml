#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include "../include/pbfml.h"


// use spans for font size change 
void to_html ( cell* c, bfmlFile* f, char* fname ) {

    cell tempcell = {.lower = 0,
                    .upper = 0};
    cell* currcell;
    cell* prevcell = &tempcell;
    FILE* ht = fopen( fname, "w+" );
    unsigned int colors[] = {0, 0, 0};
    unsigned int prev_colors[] = {0, 0, 0};
    bool same_colors;

    fprintf( ht, "<!DOCTYPE html>\n<html lang=\"en\">\n<head>\n\t<title>%s</title>\n\t<meta charset=\"utf-8\">\n</head>\n<body>\n<p>\n", fname );
    for( int i = 0; i < f->textlen; i++ ) {
        same_colors = true;
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

        // get colors, b, g and r. This implementation does not work, somehow
        for( int i = 0; i < 3; i++ ) {
            if( (colors[i] = ((currcell->lower>>(i * 8)) & 0xFF)) != prev_colors[i]) {
                same_colors = false;
            }
        }
        print_cell(currcell);
        if( !same_colors ) {
            if( prev_colors[0] + prev_colors[1] + prev_colors[2] )
                fprintf( ht, "</span>" );
            if( colors[0] + colors[1] + colors[2] ) 
                fprintf( ht, "<span style=\"color: rgb(%d, %d, %d)\">", colors[2], colors[1], colors[0]);
        }

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
        for( int i = 0; i < 3; i++ )
            prev_colors[i] = colors[i];
    }
    fprintf( ht, "</p>\n</body>\n</html>\n" );
    fclose( ht );
}