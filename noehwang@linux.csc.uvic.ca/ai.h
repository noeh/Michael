//
//  ai.h
//  2connect2
//
//  Created by Noe Hwang on 13-06-23.
//  Copyright 2013 __MyCompanyName__. All rights reserved.
//
#ifndef AI_H
#define AI_H

#include "globalDefines.h"
#include "newMinmax.h"

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
 * File-Scope Global Variables                                                 *
 \******************************************************************************/
int piece_counter;

/******************************************************************************\
 * Function Prototypes                                                          *
 \******************************************************************************/
void readboard(void);
void dispboard(void);
void freeboard(void);

#endif