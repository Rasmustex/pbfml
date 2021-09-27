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

bool compare_cells( cell* c1, cell* c2 ) {
    if( c1->upper == c2->upper && c1->lower == c2->lower )
        return true;
    else
        return false;
}