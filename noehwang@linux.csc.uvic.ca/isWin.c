//
//  isWin.c
//  2connect2
//
//  Created by Noe Hwang on 13-06-23.
//  Copyright 2013 __MyCompanyName__. All rights reserved.
//

#include "isWin.h"


typedef struct item_t { 
    int entry;
    int points; 
} item_t;

item_t wintable[] = {
    { 5252, 300},//win cases
    { 2525, 300},
    { 2552, 400},
    { 5225, 400},
    { 5522, 500},
    { 2255, 500},
    { 5353, -300},
    { 3535, -300},
    { 3553, -400},
    { 5335, -400},
    { 5533, -500},
    { 3355, -500},
    { 0, 0}
};

/******************************************************************************\
 * Global Variables                                                             *
 \******************************************************************************/
static int COMPOSITION[7]; 


/******************************************************************************\
 * resetCompositionBuffer                                                      *
 \******************************************************************************/
void resetCompositionBuffer(void)
{
    int i;
    for (i = 0; i < 7; i++)
    {
        COMPOSITION[i] = SPACE;
    }
}


/******************************************************************************\
 * lookup                                                                     *
 \******************************************************************************/
int lookup(int lookupval)
{

    item_t *p;
    for (p = wintable; p->entry != 0; ++p) {
        if (p->entry == lookupval) {
            return p->points;
        }
    }
    return 0;
}

/******************************************************************************\
 * checkArrays                                                               *
 \******************************************************************************/
int checkArrays()
{
    
    int starting = 0;
    int i;
    int decimal;
    int lookupval;
    int temp;
    int points =0;

    
    
    
    // look at all possible piece-sequences in the array to determine if it is a win 
    for(starting = 0; starting < 4; starting++)
    {
        //convert the array of int to int
        decimal = 1000;
        lookupval = 0;
        for(i = 0; i < 4; i++)
        {
            lookupval += COMPOSITION[starting + i]*decimal;
            decimal /= 10;
        }
        //lookup


            temp = lookup(lookupval); 

        if(temp != 0){
            
            points += temp;
        }
    }
    return points;
}
/******************************************************************************\
 * checkComp                                                                     *
 \******************************************************************************/
int checkComp(int last_col, int total_rows, int* board)
{
    int i;
    int count;
    int last_row;
    int final_point = 0;

    
    int mid = 3;
    // get the last move position
    for (last_row = 0; last_row <total_rows; last_row++)
    {
        if(board[last_col * total_rows + last_row +1] == SPACE)
        {
            break;
        }
    }
    
    // walk through the neighbours and store the piece in an array(size=7) 
    int last_piece = board[last_col * total_rows + last_row];
    // reset values
    resetCompositionBuffer();
    COMPOSITION[mid] = last_piece;
    count = 1;  
    /**#######################
     GO HORIZONTAL
     ########################*/
    for (i = 1; i < 4; i++ )// to the left
    {
        int curr_piece = board[(last_col-i) * total_rows + last_row];
        if (curr_piece != SPACE )
        {
            COMPOSITION[mid-i] = curr_piece;
            count ++;
        }
        else
            break;
    }
    for (i = 1; i < 4; i++ )// to the right
    {
        int curr_piece = board[(last_col+i) * total_rows + last_row];
        if (curr_piece != SPACE )
        {
            COMPOSITION[mid+i] = curr_piece;
            count ++;
        }
        else
            break;
    }
    
    if (count > 3)
    {
        final_point += checkArrays();
    }
    
    
    
    
    
    /**########################
     GO DIAGNAL 1 (top left to bottom right)
     ##########################*/
    
    // reset values
    resetCompositionBuffer();
    COMPOSITION[mid] = last_piece;
    count = 1;
    
    for (i = 1; i < 4; i++ )// top left
    {
        int curr_piece = board[(last_col-i) * total_rows + last_row+i];
        if (curr_piece != SPACE )
        {
            COMPOSITION[mid-i] = curr_piece;
            count ++;
        }
        else
            break;
    }
    for (i = 1; i < 4; i++ )// bottom right
    {
        if(last_row-i < 0)// reality check
            break;
        int curr_piece = board[(last_col+i) * total_rows + (last_row-i)];
        if (curr_piece != SPACE )
        {
            COMPOSITION[mid+i] = curr_piece;
            count ++;
        }
        else
            break;
    }
    if (count > 3)
    { 
        final_point += checkArrays();
    }
    
    
    /**########################
     GO DIAGNAL 2 (top right to bottom left)
     ##########################*/
    
    // reset values
    resetCompositionBuffer();
    COMPOSITION[mid] = last_piece;
    count = 1;
    
    for (i = 1; i < 4; i++ )// top right
    {
        int curr_piece = board[(last_col+i) * total_rows + (last_row+i)];
        if (curr_piece != SPACE )
        {
            COMPOSITION[mid-i] = curr_piece;
            count ++;
        }
        else
            break;
    }
    
    for (i = 1; i < 4; i++ )// bottom left
    {
        if(last_row-i < 0)// reality check
            break;
        int curr_piece = board[(last_col-i) * total_rows + (last_row-i)];
        if (curr_piece != SPACE )
        {
            COMPOSITION[mid+i] = curr_piece;
            count ++;
        }
        else
            break;
    }
    if (count > 3)
    {
        final_point += checkArrays();
    }
    
    /**########################
     GO VERTICAL
     ##########################*/
    // reset values
    resetCompositionBuffer();
    COMPOSITION[mid] = last_piece;
    count = 1;
    
    if(last_row > 2)// don't even bother if there is no enough piece at the bottom
    {
        for (i = 1; i < 4; i++ )
        {
            if(last_row-i < 0)// reality check
                break;
            int curr_piece = board[last_col * total_rows + (last_row-i)];
            if (curr_piece != SPACE )
            {
                COMPOSITION[mid+i] = curr_piece;
                count ++;
            }
            else
                break;
        }
    }
    if (count > 3)
    {      
        final_point += checkArrays();
    }
    //    printf("final_point:%d\n", final_point);
	return final_point;
}

