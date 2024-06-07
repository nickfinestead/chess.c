#ifndef CHESS_H
#define CHESS_H


#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stddef.h>
#include <stdlib.h>
// Defines the board length/height. 
// This is the only supported board currently.
// May add functionality to support different sizes later
#define bool unsigned char
#define HEADER 1
#define BODY 1

#define false 0
#define true 1

extern bool POSSIBLE_ENPASSANT;
extern char ENPASSANT_LOC[3]; 

typedef struct
{
	char *name;
	char location[3];
	char color;
	wchar_t value;
}PIECE;
	

typedef struct
{
	PIECE pieces[16];
	wchar_t captures[15];
	
}PLAYER;

typedef struct 
{
	PIECE* table[8][8]; // row, col
}BOARD;


PLAYER white;
PLAYER black;
BOARD board;

// IMPLEMENTED FUNCTIONS
void print_board();
void print_header();



// IN PROGRESS: Fix numbering of chess board, and setup. *HIGH PRIORITY*
//              DONE: Fixed Setup of Board
//              TODO: Fix Movement function for PAWN
void create_board(); // indentation is shown to show helper functions
    
    void create_body();
    wchar_t get_code(char side, char piece); // gets unicode for a specific peice
// Pieces can move
// TODO: Implement checks, pieces being blocked
// TODO: Implement castling
// TODO: Implement Taking Pieces
//void move_piece(wchar_t table[][HEADER], bool turn); // going to validate user input and check if piece is on square.




// FUTURE IMPLEMENTATIONS
// TODO: add validation to see if piece can move
// TODO: mark spaces that are currently free with an X to indicate possible square
//          could make a new function to print the possible moves?
// TODO: Implement a game log to output file? could be cool


//void print_moves(wchar_t table[][HEADER]); // kind of tricky, not sure ab implementation yet. may not implement bc im lazy
// TODO: could use some ds or array to hold the possible amount of moves, temporarily modify array, then set it back

// TODO: Add a output file denoting the moves of the game in a certain format, possibly for evaluation?
#endif
