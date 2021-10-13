#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <assert.h>
#include "../include/pbfml.h"

int main( int argc, char** argv ) {

    assert(sizeof(char) == 1);
    assert(sizeof(unsigned int) == 4);
    assert(sizeof(unsigned long) == 8);

    if( argc <  2 ) {
        print_help();
        void* ptrs[] = {NULL};
        print_error( "Invalid number of arguments", ARGUMENT_ERROR, ptrs, 0 );
    }
    char* outname;
    int option;
    int oflag = 0; 

    while( ( option = getopt( argc, argv, "o:h" ) ) != -1 ) {
        switch ( option ) {
            case 'o':
                outname = optarg;
                oflag++;
                break;
            case 'h':
                print_help();
                exit(0);
            default:
                break;
        }
    }
    if( !oflag )
        outname = "out.html";

    char* inname = argv[optind];
    /*
     * Run and convert input file 
     */    

    bfmlFile* f = read_file( inname );
    cell* c = run_bf( f );
    to_html( c, f, outname );
    free_cells( c, f );
    void* ptrs[] = {(void*)f->program, (void*)f->text, (void*)f};
    cleanup( ptrs, 3 );
    return 0;
}