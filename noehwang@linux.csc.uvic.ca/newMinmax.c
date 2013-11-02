//
//  newMinmax.c
//  2connect2
//
//  Created by Noe Hwang on 13-06-23.
//  Copyright 2013 __MyCompanyName__. All rights reserved.
//

#include "newMinmax.h"

#define ZZZ

int maxdepthval;
int evaluated_column;

static int order10[10] = {5,6,4,7,3,8,2,9,1,10};
static int order8[8] = {4,5,3,6,2,7,1,8};
static int order4[4] = {2,3,1,4};
static int * order;


/******************************************************************************\
 * Evaluate                                                                     *
 \******************************************************************************/
int Evaluate()
{
    int val = 0;
    val = checkCompForEval(evaluated_column, total_rows, board);
 	return val;
} /* Evaluate */

/******************************************************************************\
 * AddToBoard                                                                   *
 \******************************************************************************/
void AddToBoard(int column, int piece)
{
	int row;
    
	for (row = rows - 1; (board[column * total_rows + row] == SPACE)&& row >-1; row--) ;
	row++;
    
	board[column * total_rows + row] = piece;
}

/******************************************************************************\
 * RemoveFromBoard                                                              *
 \******************************************************************************/
void RemoveFromBoard(int column)
{
	int row;
    
	for (row = rows - 1; (board[column * total_rows + row] == SPACE); row--) ;
    
	board[column * total_rows + row] = SPACE;
    
}


/******************************************************************************\
 * MinMax                                                                       *
 \******************************************************************************/
int* MinMax(int depth)
{
	maxdepthval = depth;
    evaluated_column = last_column;
    // decides the column order
    if(columns == 10)
    {
        order = order10;
    }
    else if(columns == 8)
    {
        order = order8;
    }
    else 
        order = order4;
    int best = Max(depth, -INFINITY, INFINITY);
//    int val = AlphaBeta(depth, -INFINITY, INFINITY, 1);
    static int result[2];
    result[0] = column;
    result[1] = piece;
    return result;
} /* MinMax */

/******************************************************************************\
 * Max  (4,4,0,0,0,0,b,r,r,s,b,s,s,s,s,s,s,s,s,s,s,s)                                                                     *
 \******************************************************************************/
int Max(int depth, int alpha, int beta)
{
    /* int best = -INFINITY;                                                      */
	int val;
	int *legal_columns;
	int *legal_pieces;
	int max_legal;
	int i;
    
    /*check win*/
    val = checkComp(evaluated_column, total_rows, board);
    if (val != 0) // if finds win, return
    {
#ifdef ZZZ
        printf("FOUND WIN: column%d val:%d\n", evaluated_column, val);

        dispboard();
#endif
        return val;
    }
    
	if (depth <= 0)
    {
        val = Evaluate(); // reached the terminal without finding a win. apply heuristics.
#ifdef ZZZ
         printf("Depth %d: did not find win, Column:%d val:%d\n",maxdepthval, evaluated_column, val);
#endif
        if (val>0)
        {
            val = val * -1;
        }
		return val;
    }
    
    /* GenerateLegalMoves();                                                      */
	max_legal = 0;
	legal_columns = (int*)calloc(columns*2,sizeof(int));
	if (legal_columns == NULL)
		return alpha;
    
	legal_pieces = (int*)calloc(columns*2,sizeof(int));
    
	if (legal_pieces == NULL)
	{
		free(legal_columns);
		return alpha;
	}

        
	for (i = 0; i < columns; i++)
    {
		if (board[order[i] * total_rows + rows - 1] == SPACE)
		{
			legal_columns[max_legal] = order[i];
			legal_pieces[max_legal++] = BLUE;
			legal_columns[max_legal] = order[i];
			legal_pieces[max_legal++] = GREEN;
		}
    }
    
    if(max_legal == 0)// full board
        return alpha;
    
    /* while (MovesLeft()) {                                                      */
	for (i = 0; i < max_legal; i++) {
        
        /*    MakeNextMove();                                                         */
		AddToBoard(legal_columns[i], legal_pieces[i]);
        
        /*    val = Min(depth - 1);                                                   */
        evaluated_column = legal_columns[i];
        
        /* FOR DEBUGGING */
        /* FOR DEBUGGING */
        static int count = 0;
#ifdef ZZZ
        printf("\t\tMAX called %d times.\n", ++count);

        dispboard();
#endif
        /* FOR DEBUGGING */
        /* FOR DEBUGGING */
        
		val = Min(depth - 1, alpha, beta);
#ifdef ZZZ
        printf("MAX::Depth:%d column:%d piece:%d val:%d best:%d\n", maxdepthval - depth, evaluated_column, legal_pieces[i], val, alpha);
#endif

        
        /*    UnmakeMove();                                                           */
		RemoveFromBoard(legal_columns[i]);
        
        /*    if (val > best)                                                         */
        /*       best = val;
         */
		if (val > alpha)
		{
			alpha = val;
			if (depth == maxdepthval)
			{
                
				piece = legal_pieces[i];
				column = legal_columns[i];
#ifdef ZZZ
                printf("MAX::Best has changed:%d, column:%d, piece:%d \n", alpha, column, piece);
#endif
			}
		}
        /* }                                                                          */
	}
    
	free(legal_columns);
	free(legal_pieces);
    
    /* return best;                                                               */
	return alpha;
} /* Max */

/******************************************************************************\
 * Min                                                                          *
 \******************************************************************************/
int Min(int depth, int alpha, int beta)
{
    /* int best = INFINITY;  // <-- Note that this is different than in "Max".    */
	int val;
	int *legal_columns;
	int *legal_pieces;
	int max_legal;
	int i;
    
    
    /*check win*/
    val = checkComp(evaluated_column, total_rows, board);
    if (val != 0) // if finds win, return
    {

#ifdef ZZZ
        printf("FOUND WIN: column%d val:%d\n", evaluated_column, val);
        dispboard();
#endif
        return val;
    }
    
    /* if (depth <= 0)                                                            */
    /*    return Evaluate();                                                      */
	if (depth <= 0)
    {
        val = Evaluate(); // reached the terminal without finding a win
                            // heuristics to apply
#ifdef ZZZ
        printf("Depth %d: did not find win, Column:%d val:%d\n",maxdepthval, evaluated_column, val);
        dispboard();
#endif
		return val;
    }
    
    /* GenerateLegalMoves();                                                      */
	max_legal = 0;
	legal_columns = (int*)calloc(columns*2,sizeof(int));
	if (legal_columns == NULL)
		return beta;
	legal_pieces = (int*)calloc(columns*2,sizeof(int));
	if (legal_pieces == NULL)
	{
		free(legal_columns);
		return beta;
	}
	for (i = 0; i < columns; i++)
    {
		if (board[order[i] * total_rows + rows - 1] == SPACE)
		{
			legal_columns[max_legal] = order[i];
			legal_pieces[max_legal++] = RED;
			legal_columns[max_legal] = order[i];
			legal_pieces[max_legal++] = GREEN;
		}
    }
    if(max_legal == 0)// full board
        return beta;
    /* while (MovesLeft()) {                                                      */
	for (i = 0; i < max_legal; i++) {
        
        /*    MakeNextMove();                                                         */
		AddToBoard(legal_columns[i], legal_pieces[i]);
        
        /*    val = Max(depth - 1);                                                   */
        evaluated_column = legal_columns[i];
        
        /* FOR DEBUGGING */
        /* FOR DEBUGGING */
        static int min_count = 0;
#ifdef ZZZ
        printf("\t\tMIN called %d times.\n", ++min_count);        
        dispboard();
        printf("\n");
        printf("\n");
        printf("\n");
        /* FOR DEBUGGING */
        /* FOR DEBUGGING */
#endif        
		val = Max(depth - 1, alpha, beta);
#ifdef ZZZ
        printf("MIN::Depth:%d column:%d piece:%d val:%d best:%d\n", maxdepthval - depth, evaluated_column, legal_pieces[i], val, beta);
#endif

        //        printf("val:%d\n", val);
        
        /*    UnmakeMove();                                                           */
		RemoveFromBoard(legal_columns[i]);
        
        /*    if (val < best)  // <-- Note that this is different than in "Max".      */
        /*       best = val;                                                          */
        
		if (val < beta){
			beta = val;
#ifdef ZZZ
            printf("MIN::Best has changed:%d\n", beta);
#endif
        }

        /* }                                                                          */
	}
    
	free(legal_columns);
	free(legal_pieces);
    
	return beta;
    
} /* Min */

int AlphaBeta(int depth, int alpha, int beta, int turn)// turn=1 if blue; else 0;
{
    int val;
    int * legal_columns;
    int * legal_pieces;
    int max_legal;
    int i;
    
    
    /*check win*/
    val = checkComp(evaluated_column, total_rows, board);
    if (val != 0) // if finds win, return
    {
#ifdef ZZZ
        printf("FOUND WIN: column%d val:%d\n", evaluated_column, val);
        
        dispboard();
#endif
        return val;
    }

    if(depth == 0)
    {
        val = Evaluate();
        return val;
    }
    /* GenerateLegalMoves();                                                      */
	max_legal = 0;
	legal_columns = (int*)calloc(columns*2,sizeof(int));
	if (legal_columns == NULL)
		return alpha;
    
	legal_pieces = (int*)calloc(columns*2,sizeof(int));
    
	if (legal_pieces == NULL)
	{
		free(legal_columns);
		return alpha;
	}
    
    if (turn == 1) 
    {
        for (i = 0; i < columns; i++)
        {
            if (board[order[i] * total_rows + rows - 1] == SPACE)
            {
                legal_columns[max_legal] = order[i];
                legal_pieces[max_legal++] = BLUE;
                legal_columns[max_legal] = order[i];
                legal_pieces[max_legal++] = GREEN;
            }
        }
    }
    else
    {
        for (i = 0; i < columns; i++)
        {
            if (board[order[i] * total_rows + rows - 1] == SPACE)
            {
                legal_columns[max_legal] = order[i];
                legal_pieces[max_legal++] = RED;
                legal_columns[max_legal] = order[i];
                legal_pieces[max_legal++] = GREEN;
            }
        }
    }

    turn = turn==1?0:1; // swithch turn
    if(max_legal == 0)// full board
        return alpha;
    
    
    /* while (MovesLeft()) {                                                      */
	for (i = 0; i < max_legal; i++) {
        
        /*    MakeNextMove();                                                         */
		AddToBoard(legal_columns[i], legal_pieces[i]);
        
        /*    val = Min(depth - 1);                                                   */
        evaluated_column = legal_columns[i];
        
        /* FOR DEBUGGING */
        /* FOR DEBUGGING */
        static int count = 0;
#ifdef ZZZ
        printf("\t\tMAX called %d times.\n", ++count);
        
        dispboard();
#endif
        /* FOR DEBUGGING */
        /* FOR DEBUGGING */
        
		val = -AlphaBeta(depth-1, -beta, -alpha, turn);
#ifdef ZZZ
        printf("MAX::Depth:%d column:%d piece:%d val:%d best:%d\n", maxdepthval - depth, evaluated_column, legal_pieces[i], val, alpha);
#endif
        
        
        /*    UnmakeMove();                                                           */
		RemoveFromBoard(legal_columns[i]);
        
        /*    if (val > best)                                                         */
        /*       best = val;
         */
		if (val > alpha)
		{
			alpha = val;
			if (depth == maxdepthval)
			{
                
				piece = legal_pieces[i];
				column = legal_columns[i];
//                if(best == 1000)// blocking case
//                    piece = BLUE;
#ifdef ZZZ
                printf("MAX::Best has changed:%d, column:%d, piece:%d \n", alpha, column, piece);
#endif
			}
		}
        /* }                                                                          */
	}
    free(legal_columns);
	free(legal_pieces);
    return alpha;
    
}
/******************************************************************************\
 * dispboard                                                                    *
 \******************************************************************************/
void dispboard(void)
{
    
	int ir;
	int ic;
    
	for (ir = total_rows-1; ir >= 0; ir--)
	{
		for (ic = 0; ic < total_cols; ic++)
			printf("+---");
		printf("+\n");
        
		for (ic = 0; ic < total_cols; ic++)
			switch (board[ic*total_rows+ir])
        {
            case RED:
                printf("| r ");
                break;
            case BLUE:
                printf("| b ");
                break;
            case GREEN:
                printf("| g ");
                break;
            case SPACE:
                printf("|   ");
                break;
        } /* switch */
        
		printf("|\n");
	} /* for */
    
	for (ic = 0; ic < total_cols; ic++)
		printf("+---");
	printf("+\n");
    
	for (ic = 0; ic < total_cols; ic++)
		printf("| %d ", ic);
	printf("|\n");
    
} /* dispboard */
