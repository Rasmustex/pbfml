#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/pbfml.h"


void print_cell( cell* c ) {
    printf( "%x %x\n", c->upper, c->lower );

    return;
}

void add_cell( cell* c, unsigned long num ) {
    unsigned long c_rep = (unsigned long)c->upper;
    c_rep = c_rep<<32;
    c_rep += (unsigned long)c->lower;
    unsigned long max = (unsigned long)__UINT32_MAX__ + ((unsigned long)15<<32);
    unsigned long diff = max - c_rep;
    if( num > diff ) {
        num -= diff + 1; // if c_ref == max, diff will be 0, but we will want to remove 1 from num on wraparound
        while( num > max )
            num -= max;
        c_rep = num;
    } else {
        c_rep += num;
    }
    c->lower = (c_rep & 0xFFFFFFFF);
    c->upper = (c_rep>>32);

    return;
}

void subtract_cell( cell* c, unsigned long num ) {
    unsigned long c_rep = (unsigned long)c->upper;
    c_rep = c_rep<<32;
    c_rep += (unsigned long)c->lower;
    unsigned long max = (unsigned long)__UINT32_MAX__ + ((unsigned long)15<<32);

    if( num > c_rep ) {
        num -= c_rep + 1; // +1 so we land on the correct number on wraparound (we land on max if we subract 1 from 0)
        while( num > max ) 
            num -= max;
        c_rep = max - num;
    } else 
        c_rep -= num;

    c->lower = (c_rep & 0xFFFFFFFF);
    c->upper = (c_rep>>32);

    return;
}

cell* find_head( cell* c ) {
    while( c->prev != NULL ) {
        c = c->prev;
    }
    
    return c;
}

void initialise_cell( cell* c, cell* prev, cell* next ) {
    c->prev = prev;
    c->next = next;
    c->upper = 0;
    c->lower = 0;
}

void free_cells( cell* c, bfmlFile* f ) {
    c = find_head( c );
    cell* next;
    bool freeflag = true;
    int i = 0;
    while( c != NULL ) { // the first part of the tape is a real big block, so we need to make sure that that is only freed once
        next = c->next;
        free( c );
        c = next;
    }

    return;
}