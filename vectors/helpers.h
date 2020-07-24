#ifndef HELPERS_H
#define HELPERS_H

#include <stdio.h>
#include <stdlib.h>

int countLines(FILE* data);
float** loadData(int count, int dimension, FILE* data, char** names);
float sumArr(float array[], int elements);
void free2DArr(void** array, int rows);

#endif
