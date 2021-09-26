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

	// char* extprog = (char*)malloc( 1 * sizeof( char ) );
	// int exlen = 0; 
	// int prev_exlen;
	// int offset; // offset from beginning of found number to end
	// int num_ended; 
	// unsigned long num; // found number 
	// char prevchar; // character before the found number that needs to be repeated


	/*
	 * IMPORTANT TODO
	 * instead of this, let's check repetitions at runtime, doing this same search, but just using a for loop for the repetitions
	 */

	// for( int i = 0; i < f->proglen; i++ ) {
	// 	currchar = *(f->program + i); // iterate through program
	// 	if( currchar >= '0' && currchar <= '9' && i ) { // character is a number
	// 		offset = 0;
	// 		num_ended = 0;
	// 		prevchar = *(f->program + i - 1);
	// 		while( !num_ended ) {
	// 			currchar = *(f->program + i + (++offset)); // check whether next character is a number 
	// 			if( currchar < '0' || currchar > '9' ) {
	// 				num_ended = 1; // The next character is not a number
	// 				num = extract_long( i, offset, f->program ); // extract the found number
	// 				exlen += num - 1; // length of the extended program is extended by the number of repetitions
	// 				extprog = realloc( extprog, exlen ); // reallocate enough memory for repetition
	// 				if( extprog == NULL ) {
	// 					printf("error reallocating\n");
	// 					exit(1);
	// 				}
	// 				for( int j = 0; j < exlen - prev_exlen; j++ ) {
	// 					*(extprog + prev_exlen + j) = prevchar; // place prevchar in the newly reallocated memory
	// 				}
	// 			}
	// 		}
	// 		i += offset - 1; // make i skip past the rest of the number so a number of length n doesn't register as n different numbers.
	// 	} else {
	// 		exlen++; 
	// 		extprog = realloc( extprog, exlen ); // expand exprog by one character
	// 		*(extprog + exlen - 1) = currchar; // the new character slot is filled with the current one in program
	// 	}
	// 	prev_exlen = exlen;
	// }

	// // make space for a null-character
	// exlen++;
	// extprog = realloc( extprog, exlen ); 
	// *(extprog + exlen - 1) = '\0'; 

	cell* ptr = tape; 
	int neededopposites;
	unsigned long reps;

	for( int i = 0; i < f->proglen; i++ ) {
		currchar = *(f->program + i);
		// Let's add the entire amount at once instead of decrementing in a loop
		switch( currchar ) {
			case '+':
				reps = get_repetitions( i, f->program );
				// int h = 0;
				add_cell( ptr, reps );
				// for( unsigned long j = 0; j < reps; j++ )
					// increment_cell(ptr);
					// h++;
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
							// free( extprog );
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
							// free( extprog );
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
	// free( extprog );
	
	return tape;
}