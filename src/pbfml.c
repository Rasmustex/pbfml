#include <stdio.h>
#include <stdlib.h>
#include "../include/pbfml.h"

void cleanup ( void** ptrs, int ptrc ) {
    for( int i = 0; i < ptrc; i++ )
        free( ptrs[i] );
    return;
}

void print_error( const char* error, int error_code, void** ptrs, int ptrc ) {
    printf("\033[0;31m");
    printf("Error: ");
    printf("\033[0m");
    printf( "%s\n", error );

    cleanup( ptrs, ptrc );

    exit(error_code);
}