#ifndef FILE_H
#define FILE_H

#ifdef __cplusplus
extern "C" {
#endif 
    
    typedef struct 
    {
        char* program ;
        char* text;
        unsigned long proglen;
        unsigned long textlen;
    } bfmlFile;

    bfmlFile* read_file( char* filename );
    
#ifdef __cplusplus
}
#endif 

#endif 