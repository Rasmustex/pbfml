#include <stdio.h>
#include <stdlib.h>
#include "../include/pbfml.h"

void cleanup ( void** ptrs, int ptrc ) {
    for( int i = 0; i < ptrc; i++ )
        free( ptrs[i] );
    return;
}

void print_error( const char* error, int error_code, void** ptrs, int ptrc ) {
    printf( "\033[0;31m" );
    printf( "Error: " );
    printf( "\033[0m" );
    printf( "%s\n", error );

    cleanup( ptrs, ptrc );

    exit( error_code );
}

void print_help() {
    printf( "Usage: pbfml <filename> [OPTIONS]...\n" );
    printf( "\n" );
    printf( "pbfml is a BFML to HTML transpiler.\n" );
    printf( "It takes a BFML file as input, and outputs the converted file.\n" );
    printf( "Running pbfml <filname> results in an output file called out.html.\n" );
    printf( "\n" );
    printf( "Options:\n" );
    printf( "    -h              show help.\n" );
    printf( "    -o <filename>   output the resulting html file to <filename>.\n" );
    return;
}