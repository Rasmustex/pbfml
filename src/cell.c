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