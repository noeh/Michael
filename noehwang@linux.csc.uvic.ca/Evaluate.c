//
//  Evaluate.c
//  2connect2
//
//  Created by Noe Hwang on 13-06-23.
//  Copyright 2013 __MyCompanyName__. All rights reserved.
//

#include "Evaluate.h"

typedef struct item_t { 
    int entry;
    int points; 
} item_t;

item_t evaltable[] = {
    //    //RRGS
    {3351, -50},
    //    //RRSG
    {3315, -50},
    //    //GSRR
    {5133, -50},
    //    //SGRR
    {1533, -50},
    //    //RGSR
    {3513, -40},
    //    //RSGR
    {3153, -40},
    //    //GRRS
    {5331, -40},
    //    //SRRG
    {1335, -40},
    //    //RGRS
    {3531, -30},
    //    //RSRG
    {3135, -30},
    //    //GRSR
    {5313, -30},
    //    //SRGR
    {3135, -30},
    //    //GGRS
    {5531, -50},
    //    //GGSR
    {5513, -50},
    //    //RSGG
    {3155, -50},
    //    //SRGG
    {1355, -50},
    //    //GRSG
    {5315, -40},
    //    //GSRG
    {5135, -40},
    //    //RGGS
    {3551, -40},
    //    //SGGR
    {1553, -40},
    //    //GRGS
    {5351, -30},
    //    //GSGR
    {5153, -30},
    //    //RGSG
    {3515, -30},
    //    //SGRG
    {1535, -30},
    //    
    //    //BBGS
    {2251, 50},
    //    //BBSG
    {2215, 50},
    //    //GSBB
    {5122, 50},
    //    //SGBB
    {1522, 50},
    //    //BGSB
    {2512, 40},
    //    //BSGB
    {2152, 40},
    //    //GBBS
    {5221, 40},
    //    //SBBG
    {1225, 40},
    //    //BGBS
    {2521, 30},
    //    //BSBG
    {2125, 30},
    //    //GBSB
    {5212, 30},
    //    //SBGB
    {1252, 30},
    //    //GGBS
    {5521, 50},
    //    //GGSB
    {5512, 50},
    //    //BSGG
    {2155, 50},
    //    //SBGG
    {1255, 50},
    //    //GBSG
    {5215, 40},
    //    //GSBG
    {5125, 40},
    //    //BGGS
    {2551, 40},
    //    //SGGB
    {1552, 40},
    //    //GBGS
    {5251, 30},
    //    //GSGB
    {5152, 30},
    //    //BGSG
    {2515, 30},
    //    //SGBG
    {1525, 30},
    // SB combination    
    { 1212, 3},
    { 2121, 3},
    { 2112, 4},
    { 1122, 5},
    { 2211, 5},
    // SR combination
    { 1313, -3},
    { 3131, -3},
    { 3113, -4},
    { 1133, -5},
    { 3311, -5},
    {0,0}
};

/******************************************************************************\
 * Global Variables                                                             *
 \******************************************************************************/
static int COMPOSITION[7]; 

/******************************************************************************\
 * resetCompositionBufferForEval                                                      *
 \******************************************************************************/
void resetCompositionBufferForEval(void)
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


int evaluationLookup(int lookupval) {
    
    
    item_t *p;
    for (p = evaltable; p->entry != 0; ++p) {
        if (p->entry == lookupval) {
            return p->points;
        }
    }
    return 1;
}

/******************************************************************************\
 * checkArrays                                                               *
 \******************************************************************************/
int checkArraysForEval()
{
    
    int starting = 0;
    int i;
    int decimal;
    int lookupval;
    int points=0;
    int temp = 0;
   
    
    
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
        
        temp = evaluationLookup(lookupval); 
        
        if(temp != 0)
            points += temp;
        
    }
    return points;
}


/******************************************************************************\
 * checkComp                                                                     *
 \******************************************************************************/
int checkCompForEval(int last_col, int total_rows, int* board)
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
    resetCompositionBufferForEval();
    COMPOSITION[mid] = last_piece;
    count = 1;  
    /**#######################
     GO HORIZONTAL
     ########################*/
    for (i = 1; i < 4; i++ )// to the left
    {
        int curr_piece = board[(last_col-i) * total_rows + last_row];
        if (last_col-i > 0 )
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
        if (last_col+i < columns )
        {
            COMPOSITION[mid+i] = curr_piece;
            count ++;
        }
        else
            break;
    }
    
    if (count > 1)
    {
        final_point += checkArraysForEval();
    }
    
    
    
    
    
    /**########################
     GO DIAGNAL 1 (top left to bottom right)
     ##########################*/
    
    // reset values
    resetCompositionBufferForEval();
    COMPOSITION[mid] = last_piece;
    count = 1;
    
    for (i = 1; i < 4; i++ )// top left
    {
        int curr_piece = board[(last_col-i) * total_rows + last_row+i];
        if (last_col-i > 0 && last_row+i < rows)
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
        if (last_col-i < columns )
        {
            COMPOSITION[mid+i] = curr_piece;
            count ++;
        }
        else
            break;
    }
    if (count > 1)
    { 
        final_point += checkArraysForEval();
    }
    
    
    /**########################
     GO DIAGNAL 2 (top right to bottom left)
     ##########################*/
    
    // reset values
    resetCompositionBufferForEval();
    COMPOSITION[mid] = last_piece;
    count = 1;
    
    for (i = 1; i < 4; i++ )// top right
    {
        int curr_piece = board[(last_col+i) * total_rows + (last_row+i)];
        if (last_col-i < columns && last_row+i < rows)
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
        if (last_col-i > 0 )
        {
            COMPOSITION[mid+i] = curr_piece;
            count ++;
        }
        else
            break;
    }
    if (count > 1)
    {
        final_point += checkArraysForEval();
    }
    
    /**########################
     GO VERTICAL
     ##########################*/
    // reset values
    resetCompositionBufferForEval();
    COMPOSITION[mid] = last_piece;
    count = 1;
    
    for (i = 1; i < 4; i++ )
    {
        if(last_row-i < 0)// reality check
            break;
        int curr_piece = board[last_col * total_rows + (last_row-i)];

            COMPOSITION[mid+i] = curr_piece;
            count ++;

    }
    
    if (count > 1)
    {      
        final_point += checkArraysForEval();
    }
    //    printf("final_point:%d\n", final_point);
	return final_point;
}

