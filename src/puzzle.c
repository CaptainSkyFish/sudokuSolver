#include "sudoku.h"

Square ***setUpPuzzle(int **puzzle)
{
    Square ***sudoku;
    int i, j, k;

    sudoku = (Square ***)malloc(sizeof(Square **) * 9);

    for (i = 0; i < SIZE_ROWS; i++)
    {
        sudoku[i] = (Square **)malloc(sizeof(Square *) * 9);
        for (j = 0; j < SIZE_COLUMNS; j++)
        {
            sudoku[i][j] = (Square *)malloc(sizeof(Square) * 9);
            sudoku[i][j]->number = puzzle[i][j];

            sudoku[i][j]->row = i;
            sudoku[i][j]->column = j;
            sudoku[i][j]->solvable = 9;

            for (k = 0; k < SIZE_ROWS; k++)
            {
                sudoku[i][j]->possible[k] = 0;
            }
        }
    }

    for (i = 0; i < SIZE_ROWS; i++)
    {
        for (j = 0; j < SIZE_COLUMNS; j++)
        {
            if (sudoku[i][j]->number != 0)
            {
                sudoku[i][j]->solvable = 0;
                updateSudoku(sudoku, i, j);
                UNSOLVED--;
            }
        }
    }

    return sudoku;
};

int updateSudoku(Square ***sudoku, int row, int column)
{
    int i;
    int number = sudoku[row][column]->number;
    for (i = 0; i < SIZE_ROWS; i++)
    {
        if (sudoku[i][column]->possible[number - 1] == 0)
        {
            sudoku[i][column]->solvable--;
        }
        sudoku[i][column]->possible[number - 1] = 1;
    }
    for (i = 0; i < SIZE_COLUMNS; i++)
    {
        if (sudoku[row][i]->possible[number - 1] == 0)
        {
            sudoku[row][i]->solvable--;
        }
        sudoku[row][i]->possible[number - 1] = 1;
    }

    return 1;
}

int checkPuzzle(Square ***sudoku)
{
    int i, j;
    for (i = 0; i < SIZE_ROWS; i++)
    {
        for (j = 0; j < SIZE_COLUMNS; j++)
        {
            if (sudoku[i][j]->solvable == 1)
            {
                solveSquare(sudoku[i][j]);
                updateSudoku(sudoku, i, j);
            }
        }
    }
    return 1;
}

int **createPuzzle()
{
    int **puzzle;
    int i, j;
    int array[9][9] = {5, 3, 0, 0, 7, 0, 0, 0, 0,
                       6, 0, 0, 1, 9, 5, 0, 0, 0,
                       0, 9, 8, 0, 0, 0, 0, 6, 0,
                       8, 0, 0, 0, 6, 0, 0, 0, 3,
                       4, 0, 0, 8, 0, 3, 0, 0, 1,
                       7, 0, 0, 0, 2, 0, 0, 0, 6,
                       0, 6, 0, 0, 0, 0, 2, 8, 0,
                       0, 0, 0, 4, 1, 9, 0, 0, 5,
                       0, 0, 0, 0, 8, 0, 0, 7, 9};

    puzzle = (int **)malloc(sizeof(int *) * 9);

    for (i = 0; i < SIZE_ROWS; i++)
    {
        puzzle[i] = (int *)malloc(sizeof(int) * 9);

        for (j = 0; j < SIZE_COLUMNS; j++)
        {
            puzzle[i][j] = array[i][j];
        }
    }

    return puzzle;
}

void printPuzzle(Square ***puzzle)
{
    printf("-------------------------------\n");
    for (int i = 0; i < 9; i++)
    {
        if (i % 3 == 0 && i != 0)
            printf("-------------------------------\n");
        for (int j = 0; j < 9; j++)
        {
            if (j % 3 == 0)
                printf("|");
            printf(" %d ", puzzle[i][j]->number);
        }
        printf("|\n");
        if (i == 8)
            printf("-------------------------------\n");
    }
}