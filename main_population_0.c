
/*
============================================================================
Authors:
    Edwin Alvarez-Mamani and Jose Luis Soncco-Alvarez*
    *Department of Informatics 
    Universidad Nacional de San Antonio Abad del Cusco (UNSAAC) - Perú
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clusterCenter.h"
#include "spider.h"
#include "population.h"
#include "utils.h"

int main(int argc, char *argv[]){
    int *columns = NULL;
    int column;
    double **dataset = NULL;
    
    char *fileNameColumns = argv[1];
    int numberClusters = atoi(argv[2]);
    int row = atoi(argv[3]);
    char *fileNameRows = argv[4];
    int seed = atoi(argv[5]);

    int populationSize = 100;
    printf("%d\n", seed);

    allocateMemoryReadColumn(&columns, &column, fileNameColumns);
    allocateMemoryReadDataset(&dataset, row, column, columns, fileNameRows);

    generateSeed(seed);
    generatePopulation(populationSize, numberClusters, dataset, row, column);

    freeMemoryReadColumn(columns);
    freeMemoryReadDataset(dataset, row);

    return 0;
}

// Run:
// $ ./main_population dataset/iris.cols 3 150 dataset/iris.data 169735477 > population/iris.data 