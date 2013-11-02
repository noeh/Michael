
#include "ai.h"

/******************************************************************************\
 * freeboard                                                                    *
 \******************************************************************************/
void freeboard(void)
{
	free(board);
} /* freeboard */





/******************************************************************************\
 * readboard                                                                    *
 \******************************************************************************/
void readboard(void)
{
	int i, j;
    
	scanf("(%d,%d,%d,%d,%d,%d", &columns, &rows, &last_column, &total_time, &player_1_time, &last_move_time);
    total_cols = columns + BUFFER_SIZE*2;
    total_rows = rows + BUFFER_SIZE;
	board = (int *)calloc(sizeof(int), total_rows * total_cols);
    
    piece_counter = 0;
    for (i = 0; i < total_rows * total_cols; i++)
    {
        board[i] = SPACE;
    }
	for (i = 1; i < columns+1; i++)
    {
		for (j = 0; j < rows; j++)
        {
            char tmp;
			scanf(",%c", &tmp);
            switch(tmp)
            {
                case 's':
                    board[i*total_rows+j] = SPACE;
                    break;
                case 'r':
                    board[i*total_rows+j] = RED;
                    piece_counter ++;
                    break;
                case 'b':
                    board[i*total_rows+j] = BLUE;
                    piece_counter ++;
                    break;
                case 'g':
                    board[i*total_rows+j] = GREEN;
                    piece_counter ++;
                    break;
            }
                    }
    }
} /* readboard */




/******************************************************************************\
 * fullColumnCheck                                    *
 \******************************************************************************/
int fullColumnCheck(int col)
{
    if((board[col * total_rows + rows]) == SPACE)
    {
        return 0;
    }
    return 1;
}

/******************************************************************************\
 * main                                    *
 \******************************************************************************/
int main(void)
{
	char p;
    
	readboard();
    
    if(piece_counter < 4)
    {
        if(board[columns/2 * total_rows + 0] == SPACE){
            column = columns/2;
            piece = BLUE;
        }
            
        else {
            column = columns/2 +1;
            piece = BLUE;
        }

    }
    else
    {
        int * result;
        result = MinMax(7);
        column = result[0];
        piece = result[1];
    }
    

    
	freeboard();
    
    switch(piece)
    {
        case SPACE:
            p = 's';
            break;
        case RED:
            p = 'r';
            break;
        case BLUE:
            p = 'b';
            break;
        case GREEN:
            p = 'g';
            break;
    }
	printf("(%d, %c)", column, p);
    
	return 0;
} /* main */
