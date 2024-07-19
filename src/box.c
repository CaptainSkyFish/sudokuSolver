#include "sudoku.h"

int boxSingles(Square ***sudoku, Box **boxes)
{
    int i, j, k;
    int count, temp;
    // loop through boxes
    for (i = 0; i < 9; i++)
    {
        // loop through possible arrays
        for (j = 0; j < 9; j++)
        {
            count = 0;
            // loop through squares
            for (k = 0; k < 9; k++)
            {
                if (boxes[i]->squares[k]->number != 0)
                    continue;
                if (boxes[i]->squares[k]->possible[j] == 0)
                {
                    count++;
                    temp = k;
                }
                if (count > 2)
                    break; // the number is unsolvable in the current box so break
            }
            if (count = 1)
            {
                boxes[i]->squares[temp]->number = j + 1;
                UNSOLVED--;
                boxes[i]->squares[temp]->solvable = 0;

                updateSudoku(sudoku, boxes[i]->squares[temp]->row, boxes[i]->squares[temp]->column);
            }
        }
    }
}

Box **createBoxes()
{
    int i, j;
    Box **boxes;

    boxes = malloc(sizeof(Box *) * 9);

    for (i = 0; i < 9; i++)
    {
        boxes[i] = malloc(sizeof(Box));
        boxes[i]->squares = malloc(sizeof(Square *) * 9);
        boxes[i]->numbers = 0;
        boxes[i]->solvable = 9;

        for (j = 0; j < 9; j++)
        {
            boxes[i]->possible[j] = 0;
        }
    }
    return boxes;
}

int updateBoxes(Square ***sudoku, int row, int column)
{
    int i;
    int number = sudoku[row][column]->number;

    Box *box;
    box = sudoku[row][column]->box;

    for (i = 0; i < 9; i++)
    {
        if (box->squares[i]->possible[number - 1] == 0)
        {
            box->squares[i]->solvable--;
            box->squares[i]->possible[number - 1] = 1;
        }
    }
}