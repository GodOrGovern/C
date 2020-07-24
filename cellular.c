#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

typedef struct Cell
{
    struct Cell* left;
    struct Cell* right;
    bool state;
}
Cell;

int getInt();
void getInput(Cell* startNode);
void binary(int decNum, bool binNum[], int length);
Cell* padCells(Cell* curCell);
void nextGen(bool rule[], Cell* curCell);
short findNeighbors(Cell* curCell);
void printGen(Cell* curCell);
void freeCells(Cell* curCell);

int main(void)
{
    printf("Rule (0-255): ");
    int rule = getInt();
    bool binRule[8];
    binary(rule, binRule, 8);

    Cell* startCell = (Cell*)malloc(sizeof(Cell));
    startCell->left = NULL, startCell->right = NULL;
    printf("Start pattern: ");
    getInput(startCell);

    printf("Iterations: ");
    int iters = getInt();

    for (int i = iters; i > 0; i--)
    {
        printf("%*s", i, "");
        printGen(startCell);
        startCell = padCells(startCell);
        nextGen(binRule, startCell);
        usleep(100000);
    }

    freeCells(startCell);

    return 0;
}

int getInt()
{
    int input;
    int result = scanf("%d", &input);

    int c = EOF;
    while ((c = getchar()) != '\n' && c != EOF);

    if (result == EOF)
        return -1;
    else if (result != 1)
        return -2;

    return input;
}

void getInput(Cell* startNode)
{
    if (startNode)
    {
        int c = EOF;
        Cell* curNode = startNode;

        while ((c = getchar()) != '\n' && c != EOF)
        {
            curNode->state = c - '0';
            Cell* nextNode = (Cell*)malloc(sizeof(Cell));
            curNode->right = nextNode;
            nextNode->left = curNode;
            nextNode->right = NULL;
            curNode = nextNode;
        }

        curNode = curNode->left;
        free(curNode->right);
        curNode->right = NULL;
    }
}

void binary(int decNum, bool binNum[], int length)
{
    int powTwo = 1;

    for (int i = length - 1; i >= 0; i--)
    {
        if (decNum & powTwo)
            binNum[i] = 1;
        else
            binNum[i] = 0;

        powTwo <<= 1;
    }
}

Cell* padCells(Cell* curCell)
{
    Cell* leftCell = (Cell*)malloc(sizeof(Cell));
    Cell* rightCell = (Cell*)malloc(sizeof(Cell));
    leftCell->state = 0, rightCell->state = 0;
    leftCell->left = NULL, rightCell->right = NULL;

    while (curCell->left != NULL)
        curCell = curCell->left;

    curCell->left = leftCell;
    leftCell->right = curCell;

    while (curCell->right != NULL)
        curCell = curCell->right;

    curCell->right = rightCell;
    rightCell->left = curCell;

    return leftCell;
}

void nextGen(bool rule[], Cell* curCell)
{
    short index = findNeighbors(curCell);
    bool prevState = rule[7-index];
    curCell = curCell->right;

    for (; curCell->right != NULL; curCell = curCell->right)
    {
        index = findNeighbors(curCell);
        curCell->left->state = prevState;
        prevState = rule[7-index];
    }

    index = findNeighbors(curCell);
    curCell->left->state = prevState;
    curCell->state = rule[7-index];
}

short findNeighbors(Cell* curCell)
{
    bool nHood[3];
    nHood[1] = curCell->state;

    if (curCell->left != NULL)
        nHood[0] = curCell->left->state;
    else
        nHood[0] = 0;

    if (curCell->right != NULL)
        nHood[2] = curCell->right->state;
    else
        nHood[2] = 0;

    return (nHood[0] << 2) + (nHood[1] << 1) + nHood[2];
}

void printGen(Cell* curCell)
{
    for (; curCell != NULL; curCell = curCell->right)
    {
        if (curCell->state)
            printf("\033[0;47m \033[0m");
        else
            printf("\033[0;0m \033[0m");
    }

    printf("\n");
}

void freeCells(Cell* curCell)
{
    while (curCell->left != NULL)
        curCell = curCell->left;

    Cell* nextCell;
    while (curCell != NULL)
    {
        nextCell = curCell->right;
        free(curCell);
        curCell = nextCell;
    }
}
