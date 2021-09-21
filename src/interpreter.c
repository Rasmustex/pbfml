#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "../include/interpreter.h"

/*
 * TODO: Repetition of operations in program string.
 * Maybe expand string in the beginning? Would probably be safest
 */
unsigned long extract_long ( int start, int offset, char* program ) {
	char* selection = malloc((offset + 1) * sizeof(char)); // allocate a string with size of the int
	memcpy(selection, &program[start], offset); // copy program at int into string
	*(selection + offset) = '\0';
	unsigned long extracted = (unsigned long)atol(selection); // convert to long 
	free(selection);
	return extracted;
}

cell* parse_bf( char* program, unsigned int tapesize ) {
	// create tape and init to 0.
	cell* tape = (cell*)malloc( tapesize * sizeof(cell) );
	for( unsigned int i = 0; i < tapesize; i++ ) {
		(tape + i)->lower=0; 
		(tape + i)->upper=0; 
	}

	int programlength = strlen( program );
	char currchar;

	/* 
	 * Iterate through program, and add each character of the program to an "extended" program
	 * When a number is found, we get the entire number by going with an offset until there are no more numbers in the sequence
	 * Data of the position is given to extract_long 
	 * We use the extracted long to paste the previous characer n times where n is the extracted number
	 * 
	 * Each time we add a new character, we always realloc for the character first
	 * When we get a repetition due to an extracted long, the expanded program reallocs n bytes of extra memory
	 * We keep track of the expanded program length with a variable called exlen
	 * We can then place single characters at exlen - 1
	 * For pastes of multiple characters, we keep track of a "prev_exlen" sort of variable so we know where to start pasting 
	 */
	char* extprog = (char*)malloc( 1 * sizeof( char ) );
	int exlen = 0; 
	int prev_exlen;
	int offset;
	int num_ended;
	unsigned long num;
	char prevchar;

	for( int i = 0; i < programlength; i++ ) {
		currchar = *(program + i);
		if( currchar >= '0' && currchar <= '9' ) {
			printf("found a number\n");
			offset = 0;
			num_ended = 0;
			prevchar = *(program + i - 1);
			while( !num_ended ) {
				currchar = *(program + i + (++offset));
				if( currchar < '0' || currchar > '9' ) {
					num_ended = 1;
					num = extract_long( i, offset, program );
					printf("the number is: %lu\n", num);
					exlen += num - 1;
					extprog = realloc( extprog, exlen );
					for( int j = 0; j < exlen - prev_exlen; j++ ) {
						*(extprog + prev_exlen + j) = prevchar;
					}
				}
			}
			i += offset - 1;
		} else {
			exlen++;
			extprog = realloc( extprog, exlen );
			*(extprog + exlen - 1) = currchar;
		}
		prev_exlen = exlen;
	}

	exlen++;
	extprog = realloc( extprog, exlen );
	*(extprog + exlen - 1) = '\0';
	printf("%s\n", extprog);

	cell* ptr = tape; 
	int neededopposites;

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
				if( ptr->lower || ptr->upper ) {
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
				print_cell( ptr );
			default: 
				break;
		}
	}
	free( extprog );
	
	return tape;
}