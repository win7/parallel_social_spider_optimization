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
#include <time.h>
#include "clusterCenter.h"
#include "spider.h"
#include "population.h"
#include "utils.h"

int main(int argc, char *argv[]){
    Population population;
    AuxPopulation auxPopulation;
    AuxSpider auxSpider;
    int *columns = NULL;
    int column = 0;
    double **dataset = NULL;
    
    char *fileNameColumns = argv[1];
    int numberClusters = atoi(argv[2]);
    int row = atoi(argv[3]);
    char *fileNameRows = argv[4];
    int seed = atoi(argv[5]);

    int numberGenerations = 100;
    int populationSize = 120; // 100

    allocateMemoryReadColumn(&columns, &column, fileNameColumns);
    allocateMemoryReadDataset(&dataset, row, column, columns, fileNameRows);

    clock_t t1, t2;
    t1 = clock();

    generateSeed(seed);
    generateInitialPopulation(&population, populationSize, numberClusters, dataset, row, column, 0, &auxPopulation, &auxSpider);
    calculateWeightPopulation(&population, dataset, row, column, &auxSpider);
    // showPopulation(&population);

    for(int i = 2; i <= numberGenerations; i++){
        femaleCooperativeOperator(&population, &auxPopulation);
        maleCooperativeOperator(&population, dataset, row, column, &auxPopulation);
        matingOperator(&population, dataset, row, column, &auxPopulation, &auxSpider);
        replacement(&population, &auxPopulation);
        calculateWeightPopulation(&population, dataset, row, column, &auxSpider);

        // showPopulation(&population);
        // showBestFitness(&population, i);
        // showBestSpider(&population);
    }

    double best_metric = population.spiders[population.indexBest]->fitness;
    t2 = clock();

    // printf("[%f, %f]\n", best_metric, ((double) (t2 - t1)) / CLOCKS_PER_SEC);
    printf("Best metric: %f, Runtime: %f sec.\n", best_metric, ((double) (t2 - t1)) / CLOCKS_PER_SEC);

    // showAllResults(&population, numberGenerations, dataset, row, column);
    // showMetricBestSpider(&population);
    showBestSpider(&population);
    // Save centroids and labels
    saveClusterBestSpider(&population, dataset, row, column);

    printf("\n*** The centroids and labels are into output folder *** \n\n");

    freeMemoryReadColumn(columns);
    freeMemoryReadDataset(dataset, row);
    freeMemoryPopulation(&population, &auxPopulation, &auxSpider);

    return 0;
}

// Run:
// $ ./main_sso input/iris.cols 3 150 input/iris.data 169735477
// $ ./main_sso input/locations.cols 5 1635 input/locations.data 169735477