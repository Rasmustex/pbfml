#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include "../include/pbfml.h"

/* 
 * Takes the starting point of a number in a string, the offset to the end of the number (starting at 1), and the string.
 * Returns the number as an unsigned long
 */
unsigned long extract_long ( int start, int offset, char* program ) {
	char* selection = malloc((offset) * sizeof(char)); // allocate a string with size of the int
	assert( selection );
	memcpy(selection, &program[start + 1], offset - 1); // copy program at int into string
	*(selection + offset - 1) = '\0';
	unsigned long extracted = (unsigned long)atol(selection); // convert to long 
	free(selection);
	return extracted;
}

// Get how many times a given instruction in the BF program is supposed to be repeated based on the number after the instruction
unsigned long get_repetitions( int start, char* program ) {
	int offset = 1;
	char currchar = *(program + start + offset); // get character after found character
	bool num_ended;
	unsigned long num;

	if( currchar >= '0' && currchar <= '9' ) { // character is a number
		num_ended = false;
		while( !num_ended ) { 
			currchar = *(program + start + (++offset)); // check next char
			if( currchar < '0' || currchar > '9' ) { // no longer a number
				num_ended = true;
				num = extract_long( start, offset, program ); // extract the entire number
			}
		}
	} else {
		num = 1;
	}
	return num;
}

cell* run_bf( bfmlFile* f ) {
	// create tape and init to 0.
	cell* tape = (cell*)malloc( 2 * f->textlen * sizeof(cell) );
	assert( tape );
	initialise_cell( tape, NULL, tape + 1 );
	tape->is_in_text = true;
	for( unsigned int i = 1; i < f->textlen * 2; i++ ) {
		initialise_cell( tape + i, tape + i - 1, tape + i + 1 ); 
		(tape + i)->is_in_text = i < f->textlen ? true : false;
	}
	(tape + 2 * f->textlen - 1)->next = NULL;

	char currchar;
	cell* ptr = tape; 
	int neededopposites;
	unsigned long reps;

	for( int i = 0; i < f->proglen; i++ ) {
		currchar = *(f->program + i);
		switch( currchar ) {
			case '+':
				reps = get_repetitions( i, f->program );
				add_cell( ptr, reps );
				break;
			case '-': 
				reps = get_repetitions( i, f->program );
				subtract_cell( ptr, reps );
				break;
			case '>':
				reps = get_repetitions( i, f->program );
				for( unsigned long j = 0; j < reps; j++ ) {
					if( !ptr->next ) {
						ptr->next = (cell*)malloc( sizeof(cell) );
						initialise_cell( ptr->next, ptr, NULL );
					}
					ptr = ptr->next;
					ptr->is_in_text = false;
					assert( ptr );
				}
				break;
			case '<':
				reps = get_repetitions( i, f->program );
				for( unsigned long j = 0; j < reps; j++ ) {
					if( !ptr->prev ) {
						ptr->prev = (cell*)malloc( sizeof(cell) );
						initialise_cell( ptr->prev, NULL, ptr );
					}
					ptr = ptr->prev; 
					ptr->is_in_text = false;
					assert( ptr );
				}
				break;
			case '[':
				if( !(ptr->lower || ptr->upper) ) {
					neededopposites = 1;
					while( neededopposites > 0 ) {
						if( i < f->proglen ) {
							currchar = *(f->program + (++i));
						}
						else {
							free_cells( tape, f );
							void* ptrs[] = {(void*)f->text, (void*)f->program, (void*)f};
							print_error("bracket mismatch: too many [", BRACKET_MISMATCH_ERROR, ptrs, 3);
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
							free_cells( tape, f );
							void* ptrs[] = {(void*)f->text, (void*)f->program, (void*)f};
							print_error("bracket mismatch: too many ]", BRACKET_MISMATCH_ERROR, ptrs, 3);
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
				if( ptr->is_in_text ) {
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