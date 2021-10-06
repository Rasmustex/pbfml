#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include "../include/pbfml.h"

void to_html ( cell* c, bfmlFile* f, char* fname ) {

    cell tempcell = {
        .next = c,
        .is_in_text = false,
        .lower = 0,
        .upper = 0
    };

    cell* prev = &tempcell;

    FILE* ht = fopen( fname, "w+" );
    unsigned int colors[] = {0, 0, 0};
    unsigned int prev_colors[] = {0, 0, 0};
    bool same_colors;
    unsigned int font_size = 0;
    unsigned int prev_font_size = 0;
    unsigned long i = 0;

    fprintf( ht, "<!DOCTYPE html>\n<html lang=\"en\">\n<head>\n\t<title>%s</title>\n\t<meta charset=\"utf-8\">\n</head>\n<body>\n<p style=\"white-space: pre\">", fname );
    while( c->is_in_text ) {
        same_colors = true;

        // go through each cell and print required tags - keep track of whether the previous cell had the same tags
        // so we can avoid wasting file space

        /* 
         * font size
         */
        font_size = ((c->upper & 0b00000001)<<7);
        font_size += ((c->lower>>25) & 0b01111111);

        if( font_size != prev_font_size ) {
            if( prev_font_size )
                fprintf( ht, "</span>" );
            if( font_size )
                fprintf( ht, "<span style=\"font-size: %dpt\">", font_size );
        }

        /*
         * colors
         */

        // get colors, b, g and r. 
        for( int i = 0; i < 3; i++ ) {
            if( (colors[i] = ((c->lower>>(i * 8)) & 0xFF)) != prev_colors[i] ) {
                same_colors = false;
            }
        }

        if( !same_colors ) {
            if( prev_colors[0] + prev_colors[1] + prev_colors[2] )
                fprintf( ht, "</span>" );
            if( colors[0] + colors[1] + colors[2] ) 
                fprintf( ht, "<span style=\"color: rgb(%d, %d, %d)\">", colors[2], colors[1], colors[0] );
        }

        /*
         * checking state
         */

        // bold 
        
        if( (c->upper & TEXT_BOLD) ) {
            if( !(prev->upper & TEXT_BOLD) )
                fprintf( ht, "<b>" );
        } else if( prev->upper & TEXT_BOLD )
            fprintf( ht, "</b>");

        //italics
        if( (c->upper & TEXT_ITALICS) ) {
            if( !(prev->upper & TEXT_ITALICS) )
                fprintf( ht, "<em>" );
        } else if( prev->upper & TEXT_ITALICS )
            fprintf( ht, "</em>");

        // underline 
        if( (c->upper & TEXT_UNDERLINE) ) {
            if( !(c->upper & TEXT_UNDERLINE) )
                fprintf( ht, "<u>" );
        } else if( prev->upper & TEXT_UNDERLINE )
            fprintf( ht, "</u>");

        // print the character 
        switch ( *(f->text + i)) {
        case '<':
            fprintf( ht, "&lt;" );
            break;
        case '>':
            fprintf( ht, "&gt;");
            break;         
        default:
            fprintf( ht, "%c", *(f->text + i) );
            break;
        }

        prev = c;
        c = c->next;
        for( int i = 0; i < 3; i++ )
            prev_colors[i] = colors[i];
        prev_font_size = font_size;
        i++;
    }
    // closing off any potentially open tags
    if( prev_font_size )
        fprintf( ht, "</span>" );
    
    if( prev_colors[0] + prev_colors[1] + prev_colors[2] )
        fprintf( ht, "</span>" );

    if( c->upper & TEXT_BOLD)
        fprintf( ht, "</b>");

    if( c->upper & TEXT_ITALICS )
        fprintf( ht, "</em>");
    
    if( c->upper & TEXT_UNDERLINE )
        fprintf( ht, "</u>");
    
    fprintf( ht, "</p>\n</body>\n</html>\n" );
    fclose( ht );
}