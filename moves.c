#include "moves.h"

#define h_delta	(((destination[0] - 65) - (self->location[0] - 65)))
#define v_delta (((destination[1] - 48) - (self->location[1] - 48)))


typedef struct
{
	int hStart;
	int vStart;
	int hStop;
	int vStop;
	int hIndex; // Change in position for loop
	int vIndex; // Change in position for loop
	char color;
}MOVE;





// c is column
// r is row
bool isFree(char c, char r)
{
	if (c < 8 && r < 8)
		return (board.table[r][c] == 0);
	return (board.table[row(r)][column(c)] == 0);
}


// Returns false if the space if free
// Returns true if the target space contains a piece with the opposite color
bool isOpponent(char c, char r, char color)
{
	if(isFree(c, r))
		return false;
	if (c < 8 && r < 8)
		return (board.table[r][c]->color != color);
	return (board.table[row(r)][column(c)]->color != color);
}

bool loop(MOVE move)
{
	bool ret_value;
	//printf("hStart:%d\tvStart:%d\thStop:%d\tvStop:%d\thIndex:%d\tvIndex:%d\n",move.hStart,move.vStart,move.hStop,move.vStop,move.hIndex,move.vIndex);
	for( int i = move.vStart, j = move.hStart; i != move.vStop || j != move.hStop ; i+=move.vIndex, j+=move.hIndex)
	{
		//printf("row %d, col %d\n",i, j); 
		//printf("%x\n", board.table[i][j]);
		if(!isFree(j,i) && !isOpponent(j, i, move.color))
			return false;
	}
	
	return true;
}


bool pawn_move(char destination[3], PIECE *self)
{
	int v_dist = abs(v_delta);
	int h_dist = abs(h_delta);
	
	//printf("Delta total %d\th: %d\tv:%d\n",abs(h_delta) + abs(v_delta),abs(h_delta), abs(v_delta));
	//printf("%d %d %d %d\n",self->hasMoved == false, v_delta == 2, v_delta == 1, isFree(destination[0],destination[1]));
	if(h_dist > 1)
		return false;
	if(v_dist > 2 || v_dist <= 0)
		return false;
	
	if(((self->hasMoved == false && v_dist == 2) || v_dist == 1) && isFree(destination[0],destination[1])) 
		return true;
	if(isOpponent(destination[0],destination[1], self->color) && h_dist == 1 && v_dist == 1)
		return true;
	
	
	// TODO: Implement En Passant
	// TODO: Implement promotion
}



bool rook_move(char destination[3], PIECE *self)
{
	int v_dist = v_delta;
	int h_dist = h_delta;
	if( (v_dist == 0 && h_delta == 0) || (v_dist != 0 && h_dist != 0) )
		return false;
	
	int curr_row = row(self->location[1]);
	int curr_col = column(self->location[0]);
	int dest_row = row(destination[1]);
	int dest_col = column(destination[0]);
	
	if( v_dist < 0 )    // 8 --> 1 input, backwards in array notation
		return loop((MOVE){dest_col, dest_row + 1, curr_col, dest_col + 1, 0, 1, self->color});
	else if(v_dist > 0) // 1 --> 8 input
		return loop((MOVE){curr_col, curr_row - 1, dest_col, dest_row - 1, 0, -1, self->color});
	else if(h_dist < 0) // H --> A input
		return loop((MOVE){dest_col - 1, dest_row, curr_col - 1, curr_row, 1, 0, self->color});
	else if(h_dist > 0) // A --> H input
		return loop((MOVE){curr_col + 1, curr_row, dest_col + 1, dest_row, 1, 0, self->color});
	return false;
}


bool knight_move(char destination[3], PIECE *self)
{
	if(abs(h_delta) + abs(v_delta) != 3)
		return false;
	if(isOpponent(destination[0],destination[1], ((PIECE*)self)->color) || isFree(destination[0],destination[1]))
		return true;
	return false;
}


bool bishop_move(char destination[3], PIECE *self)
{
	int h_dist = h_delta;
	int v_dist = v_delta;
	//printf("%d %d\n", destination[1] - 48, self->location[1] - 48);
	//printf("%d %d\n", h_dist, v_dist);
	
	int curr_row = row(self->location[1]);
	int curr_col = column(self->location[0]);
	int dest_row = row(destination[1]);
	int dest_col = column(destination[0]);
	
	if (h_dist == 0 || v_dist == 0 || abs(h_dist) != abs(v_dist))
		return false;
	
	if (h_dist > 0) // A --> H
	{
		if(v_dist < 0 ) // in array this will be from 0 -- > 7 and in input with be from 8 --> 1
			return loop((MOVE){curr_col + 1, curr_row + 1, dest_col + 1, dest_row + 1, 1, 1, self->color});
		else if(v_dist > 0) 
			return loop((MOVE){curr_col + 1, curr_row - 1, dest_col + 1, dest_row - 1, 1, -1, self->color});
	}
	if (h_dist < 0)
	{
		if(v_dist < 0 )
			return loop((MOVE){curr_col - 1, curr_row + 1, dest_col - 1, dest_row + 1, -1, 1, self->color});
		else if(v_dist > 0)
			return loop((MOVE){curr_col - 1, curr_row - 1, dest_col - 1, dest_row - 1, -1, -1, self->color});
	}
	
	return false;
}



bool queen_move(char destination[3], PIECE *self)
{
	return rook_move(destination, self) || bishop_move(destination,self);
}


bool king_move(char destination[3], PIECE *self)
{
	int h_dist = abs(h_delta);
	int v_dist = abs(v_delta);

	if(v_dist > 1 || h_dist > 2 || (v_dist == 0 && h_dist == 0))
		return false;
	// TODO: Implement Castle algorithm
	if(self->hasMoved == false && h_delta == 2 && (destination[1] == '1' || destination[1] == '8'))
	{
		// TODO: Check if rooks have moved, will do clever trick by using known constant(s) for destination[1] and just checking the A column and the H column
	}

	
	
}