#include "helpers.h"

// Counts number of lines in file. It is assumed the last line is not blank
int countLines(FILE* data)
{
    int character = 0;
    int count = 0;
    while(!feof(data))
    {
        character = fgetc(data);
        if(character == '\n')
            count++;
    }

    return count + 1;
}

// Stores the vectors in an array. Stores the corresponding names in a different array
float** loadData(int count, int dimension, FILE* data, char** names)
{
    float** vector = NULL;
    vector = malloc(count * sizeof(float *));

    rewind(data);
    for (int i = 0; i < count; i++)
    {
        vector[i] = malloc(dimension * sizeof(float));
        names[i] = malloc(sizeof(char *));
        fscanf(data, "%s", names[i]);
        for (int j = 0; j < dimension; j++)
            fscanf(data, "%f,", &vector[i][j]);
    }

    return vector;
}

// Adds all elements of an array
float sumArr(float array[], int elements)
{
    float sum = 0;
    for (int i = 0; i < elements; i++)
        sum += array[i];
    return(sum);
}

// Free memory allocated for a 2-d array
void free2DArr(void** array, int rows)
{
    for (int i = 0; i < rows; i++)
        free(array[i]);
    free(array);
}