#ifndef PBFML_H
#define PBFML_H

#ifdef __cplusplus
extern "C" {
#endif

    #include <stdbool.h>
    /*
     * Cells
     */

    // cell declaration
    typedef struct
    {
        unsigned int lower;
        unsigned char upper;
    } cell;

    // cell functions
    void print_cell( cell* c );
    void increment_cell( cell* c );
    void decrement_cell( cell* c );
    // long comparecells( cell* c1, cell* c2 ); implement one that returns diff. Currently irrelevant 
    bool compare_cells( cell* c1, cell* c2 );
    void add_cell( cell* c, unsigned long num );
    void subtract_cell( cell* c, unsigned long num );

    /* 
     * File handling
     */

    // BFML file declaration. Contains program and text to be marked up as well as lengths
    typedef struct 
    {
        char* program ;
        char* text;
        unsigned long proglen;
        unsigned long textlen;
    } bfmlFile;

    // reads file with name filename and outputs a BFML file
    bfmlFile* read_file( char* filename );

    // interpret program 
    cell* run_bf( bfmlFile* f );

    /*
     * html conversion 
     */ 

    // for bitwise and with the upper bytes of the char 
    #define TEXT_BOLD 8
    #define TEXT_ITALICS 4
    #define TEXT_UNDERLINE 2

    // converts a BFML file into an html file using the output of a BF program
    void to_html( cell* c, bfmlFile* f, char* fname );

    /*
     * basic features such as error handling
     */

    enum error_type {
        FILE_ERROR = 1,
        ARGUMENT_ERROR = 2,
        BRACKET_MISMATCH_ERROR = 3,
        ALLOCATION_ERROR
    };

    // Prints error, frees memory taken by the given pointers, and exits
    void print_error( const char* error, int error_code, void** ptrs, int ptrc );
    // Frees the memory taken by the given pointers
    void cleanup( void** ptrs, int ptrc );

#ifdef __cplusplus
}
#endif 
#endif