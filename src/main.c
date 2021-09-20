#include <stdio.h>
#include <stdlib.h>
#include "../include/cell.h"

int main( int argc, char** argv ) {
    cell c1 = {
        .lower = 0xFFFFFFFF,
        .upper = 15
    };

    print_cell( &c1 );
    increment_cell( &c1 );
    print_cell( &c1 );

    return 0;
}