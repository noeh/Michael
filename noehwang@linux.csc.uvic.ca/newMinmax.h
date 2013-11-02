//
//  newMinmax.h
//  2connect2
//
//  Created by Noe Hwang on 13-06-23.
//  Copyright 2013 __MyCompanyName__. All rights reserved.
//
#ifndef NEWMINMAX_H
#define NEWMINMAX_H

#include "globalDefines.h"
#include "Evaluate.h"
#include "isWin.h"

/******************************************************************************\
 * External Global Variables                                                   *
 \******************************************************************************/
int* board;
int columns;
int rows;
int last_column;
int total_time;
int player_1_time;
int last_move_time;
int total_cols;
int total_rows;
int column;
int piece;

/******************************************************************************\
 * Function Prototypes                                                          *
 \******************************************************************************/
int* MinMax(int depth);
int Max(int depth, int alpha, int beta);
int Min(int depth, int alpha, int beta);
void dispboard(void);
int AlphaBeta(int depth, int alpha, int beta, int turn);

#endif