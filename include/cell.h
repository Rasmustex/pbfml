#ifndef CELL_H
#define CELL_H

#ifdef __cplusplus
extern "C" {
#endif 
    #include <stdbool.h>
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
    
#ifdef __cplusplus
}
#endif 

#endif 