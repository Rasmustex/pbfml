#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/pbfml.h"


void print_cell( cell* c ) {
    printf( "%x %x\n", c->upper, c->lower );

    return;
}

void increment_cell( cell* c ) {
    if( c->lower < __UINT32_MAX__ ) {
        c->lower++; 
    } else if( c->upper < 15 ) {
        c->upper++;
        c->lower = 0;
    } else {
        c->upper = 0;
        c->lower = 0; 
    }

    return;
}

void decrement_cell( cell* c ) {
    if( c->lower > 0 ) {
        c->lower--;
    } else if( c->upper ) {
        c->upper--;
        c->lower = __UINT32_MAX__;
    } else {
        c->upper = 15;
        c->lower = __UINT32_MAX__;
    }

    return;
}

bool compare_cells( cell* c1, cell* c2 ) {
    if( c1->upper == c2->upper && c1->lower == c2->lower )
        return true;
    else
        return false;
}