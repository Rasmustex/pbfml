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
    // long comparecells( cell* c1, cell* c2 ); implement one that returns diff. Currently ittelevant 
    bool compare_cells( cell* c1, cell* c2 );

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

    // we can bitwise AND these with the upper byte. Should be endianness-agnostic?
    typedef enum {
        TEXT_BOLD = 8,
        TEXT_ITALICS = 4,
        TEXT_UNDERLINE = 2
    } Attrib;

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