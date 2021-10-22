#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../include/pbfml.h"

bfmlFile* read_file( char* filename ) {
    bfmlFile* file = (bfmlFile*)malloc(sizeof(bfmlFile));
    assert( file != NULL );
    FILE* f;

    if(!access( filename, F_OK )) {
        f = fopen( filename, "r" );
    } else {
        void* ptrs[] = {(void*)file};
        print_error( "Could not open file", FILE_ERROR, ptrs, 1 );
    }

    fseek( f, 0, SEEK_END );
    unsigned long filesize = ftell(f);
    fseek( f, 0, SEEK_SET );

    unsigned long charcounter = 0;
    while(fgetc(f) != '\n') {
        if( charcounter > filesize ) {
            fclose(f);
            void* ptrs[] = {(void*) file};
            print_error( "No text to mark up (remember, first line is read as a brainfuck program, and won't be counted as text)", FILE_ERROR, ptrs, 1 );
        }
        charcounter++;
    }
    file->program = (char*)malloc(charcounter + 1);
    assert( file->program != NULL );
    fseek(f, 0, SEEK_SET);
    fgets(file->program, charcounter + 1, f);
    file->program[charcounter] = '\0';

    fseek( f, 0, SEEK_END );
    unsigned long textsize = ftell(f) - charcounter - 1;
    fseek(f, charcounter + 1, SEEK_SET);
    file->text = (char*)malloc(textsize + 1);
    assert( file->text != NULL );
    for( int i = 0; i < textsize; i++ ) {
        file->text[i] = fgetc( f );
    }
    file->text[textsize] = '\0';
    fclose(f);
    file->proglen = strlen(file->program);
    file->textlen = strlen(file->text);


    return file; 
}