#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "../include/interpreter.h"
#include "../include/cell.h"

cell* parsebf( char* program, unsigned int tapesize ) {
	// create tape and init to 0.
	cell* tape = (cell*)malloc( tapesize * sizeof(cell) );
	for( unsigned int i = 0; i < tapesize; i++ ) {
		(tape + i * sizeof(cell))->lower=0; 
		(tape + i * sizeof(cell))->upper=0; 
	}

	cell* ptr = tape; 
	int programlength = strlen( program );
	int neededopposites;
	char currchar;

	for( int i = 0; i < programlength; i++ ) {
		currchar = *(program + i);
		
		switch( currchar ) {
			case '+':
				increment_cell(ptr);
				break;
			case '-':
				decrement_cell(ptr);
				break;
			case '>':
				ptr < tape + tapesize -1 ? (ptr++) : (ptr = tape);
				break;
			case '<':
				ptr > tape ? (ptr--) : (ptr = tape + tapesize - 1);
				break;
			case '[':
				if( !(ptr->lower || ptr->upper) ) {
					neededopposites = 1;
					while( neededopposites > 0 ) {
						if( i < programlength ) {
							currchar = *(program + (++i));
						}
						else {
							free( tape );
							printf("bracket error");
							exit(1);
						}
						if( currchar == '[' )
							neededopposites++;
						else if( currchar == ']' )
							neededopposites--;
					}
				}
				break;
			case ']':
				// printf("reached right paren\n");
				if( ptr->lower || ptr->upper ) {
					neededopposites = 1;
					while ( neededopposites > 0 ) {
						if( i > 0 ) {
							currchar = *(program + (--i));
							// printf("%c", currchar);
						}
						else {
							free( tape ); 
							printf("bracket error");
							exit(1);
						}
						if( currchar == ']' )
							neededopposites++;
						else if( currchar == '[' ) 
							neededopposites--;
					}
				}
				break;
			case '.':
				print_cell( ptr );
			default: 
				break;
		}
	}
	
	return tape;
}