#ifndef PBFML_H
#define PBFML_H

#ifdef __cplusplus
extern "C" {
#endif

    #include <stdbool.h>
    // cell stuff
    typedef struct
    {
        unsigned int lower;
        unsigned char upper;
    } cell;

    void print_cell( cell* c );
    void increment_cell( cell* c );
    void decrement_cell( cell* c );
    // long comparecells( cell* c1, cell* c2 ); implement one that returns diff. Currently irrelevant 
    bool compare_cells( cell* c1, cell* c2 );
    void add_cell( cell* c, unsigned long num );
    void subtract_cell( cell* c, unsigned long num );

    // file reading
    typedef struct 
    {
        char* program ;
        char* text;
        unsigned long proglen;
        unsigned long textlen;
    } bfmlFile;

    bfmlFile* read_file( char* filename );

    // interpreter function declaration 
    cell* run_bf( bfmlFile* f );

    // html conversion functions and structures

    // for bitwise and with the upper bytes of the char 
    #define TEXT_BOLD 8
    #define TEXT_ITALICS 4
    #define TEXT_UNDERLINE 2

    void to_html( cell* c, bfmlFile* f, char* fname );
    // as for text size, we will have to get those bits into their own variable and just convert to decimal to insert into our HTML file

    // colour should be VERY doable 

    /* 
     * Need to make functions that check bit values of cell and can return a state
     * Needs to compare to state of previous char 
     * make necessary changes
     * need to define what different states do
     * template of wrapping stuff in paragraphs
     * We're doing that tomorrow tho ( the 22nd )
     */

#ifdef __cplusplus
}
#endif 
#endif