#include <stdio.h>
#include <math.h>
#include <string.h>

#include "helpers.h"

float** loadData(int count, int dimension, FILE* data, char** names);
float* squareMag(int count, int dimension, float** vector);
void dotProduct(int count, int dimension, float** vector, float* storeMag, char** names);

int main(int argc, char** argv)
{
    if (argc != 3)
    {
        printf("Usage: ./vector [path to file] [# of dimensions]\n");
        return 1;
    }

    FILE* data;
    data = fopen(argv[1], "r");

    if (data == NULL)
    {
        printf("Error Reading File\n");
        return 2;
    }

    int dimension = atoi(argv[2]);
    int count = countLines(data);

    char** names = malloc(count * sizeof(char *));
    float** vector = loadData(count, dimension, data, names);
    float* storeMag = squareMag(count, dimension, vector);

    dotProduct(count, dimension, vector, storeMag, names);

    free(storeMag);
    free2DArr((void**) vector, count);
    free2DArr((void**) names, count);
    fclose(data);
    return 0;
}

// Stores the square of each vector's magnitude in a buffer
float* squareMag(int count, int dimension, float** vector)
{
    float buffer[dimension];
    float* storeMag = malloc(count * sizeof(float));

    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < dimension; j++)
            buffer[j] = vector[i][j] * vector[i][j];

        storeMag[i] = sumArr(buffer, dimension);
    }

    return storeMag;
}

/* 
 * Finds all possible dot products and magnitude multiplications (with two
 * vectors). Uses them to find inner angle, which is written to output.csv along
 * with the names associated with each vector
 */
void dotProduct(int count, int dimension, float** vector, float* storeMag, char** names)
{
    int crosses = ((count - 1) * count) / 2;
    float magnitude[crosses];
    float dotProd[crosses];
    float results[crosses];
    float buffer[dimension];

    FILE* output;
    output = fopen("output.csv", "w");

    for (int i = 0; i < count; i++)
    {
        for (int j = i + 1; j < count; j++)
        {
            int temp = i + j - 1;
            for (int k = 0; k < dimension; k++)
                buffer[k] = vector[i][k] * vector[j][k];

            dotProd[temp] = sumArr(buffer, dimension);
            magnitude[temp] = sqrtf(storeMag[i]) * sqrtf(storeMag[j]);
            results[temp] = acosf(dotProd[temp] / magnitude[temp]);

            fprintf(output, "%s,%s,%f\n", names[i], names[j], results[temp]);
        }
    }

    fclose(output);
}