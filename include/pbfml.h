#ifndef PBFML_H
#define PBFML_H

#ifdef __cplusplus
extern "C" {
#endif

    #include <stdbool.h>
    /*
     * Cells
     */

    /* 
     * Cell declaration. The brainfuck tape is made of these.
     * Lower holds the 32 least significant bits of the cell, and upper holds the 4 most significant ones, making for a 36-bit cell.
     * Upper is really 8 bits but capped by functions.
     */
    typedef struct ce cell;
    struct ce {
        cell *prev;
        unsigned int lower;
        unsigned char upper;
        bool is_in_text; 
        cell* next;
    };

    // Prints the values of upper and lower in hex. Upper and lower values are separated by a space.
    void print_cell( cell* c ); 
    // Add num to the cell's value with wraparound.
    void add_cell( cell* c, unsigned long num ); 
    // Subtract num from the cell's value with wraparound.
    void subtract_cell( cell* c, unsigned long num ); 
    // 0-initializes cell values and makes its prev point to prev and next point to next
    void initialise_cell( cell* c, cell* prev, cell* next );
    // find head of cell list
    cell* find_head( cell* c );
    cell* find_tail( cell* c );

    /* 
     * File handling
     */

    // BFML file declaration. Contains program and text to be marked up as well as lengths of program and text.
    typedef struct {
        char* program ;
        char* text;
        unsigned long proglen;
        unsigned long textlen;
    } bfmlFile;

    // free all cells in a cell list 
    void free_cells( cell* c );

    // Reads file with name filename and outputs a BFML file
    bfmlFile* read_file( char* filename );

    // Interprets the BF program on the first line of the BFML file, and return the resulting tape.
    cell* run_bf( bfmlFile* f );

    /*
     * html conversion 
     */ 

    // Representes the bits that need to be set in the cell's upper data in order for certain attributes to be true.
    #define TEXT_BOLD 8
    #define TEXT_ITALICS 4
    #define TEXT_UNDERLINE 2

    // converts a BFML file into an HTML file using the output of the interpretation of the BF program on the first line
    void to_html( cell* c, bfmlFile* f, char* fname );

    /*
     * basic features such as error handling
     */

    enum error_type {
        FILE_ERROR = 1,
        ARGUMENT_ERROR = 2,
        BRACKET_MISMATCH_ERROR = 3,
        ALLOCATION_ERROR = 4
    };

    // Prints error, frees memory taken by the given pointers, and exits
    void print_error( const char* error, int error_code, void** ptrs, int ptrc );
    // Frees the memory taken by the given pointers
    void cleanup( void** ptrs, int ptrc );
    // Prints the help menu
    void print_help();

#ifdef __cplusplus
}
#endif 
#endif