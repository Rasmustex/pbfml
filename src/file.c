#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../include/file.h"

bfmlFile* read_file( char* filename ) {
    bfmlFile* file = (bfmlFile*)malloc(sizeof(bfmlFile));
    FILE* f;

    if(!access( filename, F_OK )) {
        f = fopen( filename, "r" );
    } else {
        free( file );
        printf("File reading error");
        exit(-1);
    }

    unsigned long charcounter = 0;
    while(fgetc(f) != '\n') {
        charcounter++;
    }
    file->program = (char*)malloc(charcounter + 1);
    fseek(f, 0, SEEK_SET);
    fgets(file->program, charcounter + 1, f);
    file->program[charcounter] = '\0';

    fseek( f, 0, SEEK_END );
    unsigned long textsize = ftell(f) - charcounter;
    fseek(f, charcounter, SEEK_SET);
    file->text = (char*)malloc(textsize + 1);
    for( int i = 0; i < textsize; i++ ) {
        file->text[i] = fgetc( f );
    }
    file->text[textsize] = '\0';
    fclose(f);
    file->proglen = strlen(file->program);
    file->textlen = strlen(file->text);

    return file; 
}