#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "../include/interpreter.h"

/*
 * TODO: Repetition of operations in program string.
 * Maybe expand string in the beginning? Would probably be safest
 */
long extract_long ( int start, int offset, char* program ) {
	// printf("%d\n %s\n", offset, program);
	char* selection = malloc((offset + 1) * sizeof(char));
	memcpy(selection, &program[start], offset);
	*(selection + offset) = '\0';
	// printf("%s\n", selection);
	long extracted = atol(selection);
	free(selection);
	return extracted;
}

cell* parse_bf( char* program, unsigned int tapesize ) {
	// create tape and init to 0.
	cell* tape = (cell*)malloc( tapesize * sizeof(cell) );
	for( unsigned int i = 0; i < tapesize; i++ ) {
		(tape + i * sizeof(cell))->lower=0; 
		(tape + i * sizeof(cell))->upper=0; 
	}

	int programlength = strlen( program );
	int offset;
	int endfound;
	int numberindex = 0;
	int maxindex;
	long numbers[programlength][2];
	char currchar;

	// expand numbers in input program string
	for( int i = 0; i < programlength; i++ ) {
		currchar = *(program + i);
		if( currchar >= '0' && currchar <= '9' ) {
			endfound = 0;
			offset = 0;
			while( !endfound ) {
				(i + offset < programlength) ? (++offset) : (endfound = 1);
				currchar = *(program + i + offset);
				if( currchar < '0' || currchar > '9')
					endfound = 1;
			}
			numbers[numberindex][0] = i - 1;
			numbers[numberindex][1] = extract_long( i, offset, program );
			i+=offset - 1;
		}
	}
	maxindex = numberindex;
	// now we want to add in all the repetitions we need. We can do this by going from offset 
	// to offset using numbers[] and pasting the amount of operators we need

	int expsize = 0;
	printf("%lu\n", numbers[0][0]);
	char* expandedprogram = (char*)malloc( numbers[0][0] * sizeof( char ) );
	memcpy( expandedprogram, &program[0], numbers[0][0]);
	long prevp = 0; 
	long preve = 0;

	for( numberindex = 0; numberindex <= maxindex; numberindex++ ) {
		// printf("%lu\n", numbers[numberindex][0]);
		expsize += numbers[numberindex][0] + numbers[numberindex][1];
		expandedprogram = (char*)realloc( expandedprogram, expsize );

		memcpy( &expandedprogram[preve], &program[prevp], numbers[numberindex][0] - prevp );
		// doesn't get in here
		for( int i = 0; i < numbers[numberindex][1] - 1; i++ ) {
			currchar = *(program + numbers[numberindex][0]);
			strcat(expandedprogram, &currchar);
		}
		prevp = numbers[numberindex][0];
		preve = numbers[numberindex][0] + numbers[numberindex][1];
	}
	printf("%s\n", expandedprogram);

	expsize += programlength - numbers[maxindex][0] + 1;
	expandedprogram = (char*)realloc( expandedprogram, expsize );
	strcat(expandedprogram, &program[numbers[maxindex][0]]);
	expandedprogram[expsize] = '\0';
	printf("%s\n", expandedprogram);


	cell* ptr = tape; 
	int neededopposites;

	for( int i = 0; i < expsize; i++ ) {
		currchar = *(expandedprogram + i);
		
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
						if( i < expsize ) {
							currchar = *(expandedprogram + (++i));
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
							currchar = *(expandedprogram + (--i));
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