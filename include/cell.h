#ifndef CELL_H
#define CELL_H

#ifdef __cplusplus
extern "C" {
#endif 
    
    typedef struct
    {
        /* data */
        unsigned int lower;
        unsigned char upper;
    } cell;

    void print_cell( cell* c );
    void increment_cell( cell* c );
    void decrement_cell( cell* c );
    

#ifdef __cplusplus
}
#endif 

#endif 