#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "interpreter.h"

unsigned long* parsebf( char* program, unsigned int tapesize ) {
	// create tape and init to 0.
	unsigned long* tape = (unsigned long*)malloc( tapesize * sizeof(unsigned long) );
	for( unsigned int i = 0; i < tapesize; i++ ) {
		*(tape + i) = 0; 
	}

	unsigned long* ptr = tape; 
	int programlength = strlen( program );
	int neededopposites;
	char currchar;

	for( int i = 0; i < programlength; i++ ) {
		currchar = *(program + i);
		
		switch( currchar ) {
			case '+':
				++*ptr;
				break;
			case '-':
				--*ptr;
				break;
			case '>':
				ptr < tape + tapesize -1 ? (ptr++) : (ptr = tape);
				break;
			case '<':
				ptr > tape ? (ptr--) : (ptr = tape + tapesize - 1);
				break;
			case '[':
				if( !(*ptr) ) {
					neededopposites = 1;
					while( neededopposites > 0 ) {
						if( i < tapesize ) {
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
				if( *ptr ) {
					neededopposites = 1;
					while ( neededopposites > 0 ) {
						if( i > 0 ) {
							currchar = *(program + (--i));
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
				printf("%lu", *ptr);
			default: 
				break;
		}
	}
	
	return tape;
}
