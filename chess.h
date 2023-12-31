#pragma once


#include <stdio.h>
#include <string.h>
// Defines the board length/height. 
// This is the only supported board currently.
#define bool unsigned char
#define HEADER 53 // 51/53
#define BODY 26 // could change to 27 to have extra spacing at bottom


// IMPLEMENTED FUNCTIONS
void print_board(char table[][HEADER]);



void create_board(char table[][HEADER]); // indentation is shown to show helper functions
    void create_header(char table[][HEADER]);
    void create_body(char table[][HEADER]);

// Pieces can move
// TODO: Implement checks, pieces being blocked
// TODO: Implement castling
// TODO: Implement Taking Pieces
void move_piece(char table[][HEADER], char piece[3], bool turn); // going to validate user input and check if piece is on square.




// FUTURE IMPLEMENTATIONS
// TODO: add validation to see if piece can move
// TODO: mark spaces that are currently free with an X to indicate possible square
//          could make a new function to print the possible moves?
// TODO: Implement a game log to output file? could be cool


//void print_moves(char table[][HEADER]); // kind of tricky, not sure ab implementation yet. may not implement bc im lazy
// TODO: could use some ds or array to hold the possible amount of moves, temporarily modify array, then set it back