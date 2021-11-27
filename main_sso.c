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
    int populationSize = 100;

    allocateMemoryReadColumn(&columns, &column, fileNameColumns);
    allocateMemoryReadDataset(&dataset, row, column, columns, fileNameRows);

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

    showAllResults(&population, numberGenerations, dataset, row, column);
    // showMetricBestSpider(&population);
    showBestSpider(&population);
    // Save centroids and labels
    saveClusterBestSpider(&population, dataset, row, column);

    freeMemoryReadColumn(columns);
    freeMemoryReadDataset(dataset, row);
    freeMemoryPopulation(&population, &auxPopulation, &auxSpider);

    return 0;
}

// Run:
// $ ./main_sso dataset/iris.cols 3 150 dataset/iris.data 169735477
// $ ./main_sso dataset/locations.cols 5 1635 dataset/locations.data 169735477