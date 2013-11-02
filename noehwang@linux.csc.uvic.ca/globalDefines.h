
#ifndef GLOBAL_DEFINES_H
#define GLOBAL_DEFINES_H
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
/******************************************************************************\
 * Global Defines                                                               *
 \******************************************************************************/
#define INFINITY 2147483647
#define BUFFER_SIZE 1
#define RED      3
#define BLUE     2
#define GREEN    5
#define SPACE    1



/******************************************************************************\
 * Global Variables                                                             *
 \******************************************************************************/
extern int *board;
extern int columns;
extern int rows;
extern int last_column;
extern int total_time;
extern int player_1_time;
extern int last_move_time;
extern int total_cols;
extern int total_rows;



extern int column;
extern int piece;

#endif // GLOBAL_DEFINES_H
