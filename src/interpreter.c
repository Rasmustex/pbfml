#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "../include/pbfml.h"

/* 
 * Takes the starting point of a number in a string, the offset to the end of the number (starting at 1), and the string.
 * Returns the number as an unsigned long
 */
unsigned long extract_long ( int start, int offset, char* program ) {
	char* selection = malloc((offset) * sizeof(char)); // allocate a string with size of the int
	memcpy(selection, &program[start + 1], offset - 1); // copy program at int into string
	*(selection + offset - 1) = '\0';
	unsigned long extracted = (unsigned long)atol(selection); // convert to long 
	free(selection);
	return extracted;
}

unsigned long get_repetitions( int start, char* program ) {
	int offset = 1;
	char currchar = *(program + start + offset);
	bool num_ended;
	unsigned long num;

	if( currchar >= '0' && currchar <= '9' ) { // character is a number
		num_ended = false;
		while( !num_ended ) {
			currchar = *(program + start + (++offset));
			if( currchar < '0' || currchar > '9' ) { // no longer a number
				num_ended = true;
				num = extract_long( start, offset, program );
			}
		}
	} else {
		num = 1;
	}
	return num;
}

// TODO: Filelength for EOF checking 
cell* run_bf( bfmlFile* f ) {
	// create tape and init to 0.
	cell* tape = (cell*)malloc( f->textlen * sizeof(cell) );
	for( unsigned int i = 0; i < f->textlen; i++ ) {
		(tape + i)->lower=0; 
		(tape + i)->upper=0; 
	}

	char currchar;
	cell* ptr = tape; 
	int neededopposites;
	unsigned long reps;

	for( int i = 0; i < f->proglen; i++ ) {
		currchar = *(f->program + i);
		// Let's add the entire amount at once instead of decrementing in a loop
		switch( currchar ) {
			case '+':
				reps = get_repetitions( i, f->program );
				add_cell( ptr, reps );
				break;
			case '-':
				reps = get_repetitions( i, f->program );
				for( unsigned long j = 0; j < reps; j++ )
					decrement_cell(ptr);
				break;
			case '>':
				reps = get_repetitions( i, f->program );
				for( unsigned long j = 0; j < reps; j++ )
					ptr < tape + f->textlen - 1 ? (ptr++) : (ptr = tape);
				break;
			case '<':
				reps = get_repetitions( i, f->program );
				for( unsigned long j = 0; j < reps; j++ )
					ptr > tape ? (ptr--) : (ptr = tape + f->textlen - 1);
				break;
			case '[':
				if( !(ptr->lower || ptr->upper) ) {
					neededopposites = 1;
					while( neededopposites > 0 ) {
						if( i < f->proglen ) {
							currchar = *(f->program + (++i));
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
				if( ptr->lower || ptr->upper ) {
					neededopposites = 1;
					while ( neededopposites > 0 ) {
						if( i > 0 ) {
							currchar = *(f->program + (--i));
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
				ptr->upper = 0;
				if( ptr - tape <= f->textlen ) {
					ptr->lower = 0;
				} else {
					ptr->lower = 1;
				}
			default: 
				break;
		}
	}
	
	return tape;
}