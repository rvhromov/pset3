/**
 * fifteen.c
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE *file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = get_int();
        
        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }
    
    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(void)
{
    int tile_number = d * d - 1;
    
    // Заполняем квадратную матрицу номерами
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            board[i][j] = tile_number--;
        }
    }
    // Если размер квадратной матрицы - чётное число,
    // то меняем номер 1 и номер 2 местами для возможности выиграша
    if(d % 2 == 0)
    {
        board[d - 1][d - 2] = 2;
        board[d - 1][d - 3] = 1;
    }
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    // Выводим матрицу на экран, вместо номера 0 выводим нижнее подчеркивание
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            if(board[i][j] == 0)
                printf("  _");
            else 
                printf("%3i", board[i][j]);
        }
        
        printf("\n");
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
    int tile_x, tile_y, tmp;
    
    // Ищем координаты числа которое выбрал пользователь
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            if(board[i][j] == tile)
            {
                tile_x = i;
                tile_y = j;
            }
        }
    }
    
    // Проверяем, есть ли от этого числа свободное место слева, если да - меняем местами
    if(board[tile_x][tile_y - 1] == 0 && tile_y - 1 >= 0)
    {
        tmp = board[tile_x][tile_y];
        board[tile_x][tile_y] = board[tile_x][tile_y - 1];
        board[tile_x][tile_y - 1] = tmp;
        
        return true;
    }
    // Проверяем, есть ли от этого числа свободное место справа, если да - меняем местами
    if(board[tile_x][tile_y + 1] == 0 && tile_y + 1 < d )
    {
        tmp = board[tile_x][tile_y];
        board[tile_x][tile_y] = board[tile_x][tile_y + 1];
        board[tile_x][tile_y + 1] = tmp;
        
        return true;
    }
    // Проверяем, есть ли от этого числа свободное место сверху, если да - меняем местами
    if(board[tile_x - 1][tile_y] == 0 && tile_x - 1 >= 0)
    {
        tmp = board[tile_x][tile_y];
        board[tile_x][tile_y] = board[tile_x - 1][tile_y];
        board[tile_x - 1][tile_y] = tmp;
        
        return true;
    }
    // Проверяем, есть ли от этого числа свободное место снизу, если да - меняем местами
    if(board[tile_x + 1][tile_y] == 0 && tile_x + 1 < d )
    {
        tmp = board[tile_x][tile_y];
        board[tile_x][tile_y] = board[tile_x + 1][tile_y];
        board[tile_x + 1][tile_y] = tmp;
        
        return true;
    }
    
    return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    int numbers = 1;
    int increase_order = 1;
    
    // Проверяем собрана ли выиграшная комбинация, а именно - 
    // проверяем все ли числа идут по возростанию, кроме последнего
    for (int i = 0; i < d; i++)
    {
       for (int j = 0; j < d; j++)
        {
            if (increase_order == numbers && board[i][j] == numbers)
            {
                if (numbers == d * d - 1)
                    return true;
                    
                numbers++;
            }
            
            increase_order++;
        } 
    }
        
    return false;
}
