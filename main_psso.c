/*
============================================================================
Authors:
    Edwin Alvarez-Mamani and Jose Luis Soncco-Alvarez*
    *Department of Informatics 
    Universidad Nacional de San Antonio Abad del Cusco (UNSAAC) - Perú
============================================================================
*/

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clusterCenter.h"
#include "spider.h"
#include "population.h"
#include "utils.h"
#include "topology.h"

int main(int argc, char *argv[]) {
    Population population;
    AuxPopulation auxPopulation;
    AuxSpider auxSpider;
    Policy policy;
    int *columns = NULL;
    int column = 0;
    double **dataset = NULL;
    
    char *fileNameColumns = argv[1];
    int numberClusters = atoi(argv[2]);
    int row = atoi(argv[3]);
    char *fileNameRows = argv[4];
    char *fileNamePolicy = argv[5];
    int seed = atoi(argv[6]);

    int numberGenerations = 100;
    int populationSize = 100;

    allocateMemoryReadColumn(&columns, &column, fileNameColumns);
    allocateMemoryReadDataset(&dataset, row, column, columns, fileNameRows);
    readPolicy(&policy, fileNamePolicy);
    // showPolicyMigration(&policy);

    int lengthPoint = policy.numberEmiImm * numberClusters * column;
    double *point = NULL;
    allocateMemoryArrayDouble(&point, lengthPoint);

    // Initialize the MPI environment
    double t1, t2; 
    t1 = MPI_Wtime();

    int world_rank;
    int world_size;
    
    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    if (world_size != 24) {
        printf("Quitting. Number of MPI tasks no is 24.\n");
        // MPI_Abort(MPI_COMM_WORLD, rc);
        exit(0);
    }

    generateSeed(seed + world_rank + 1);
    generateInitialPopulation(&population, populationSize, numberClusters, dataset, row, column, policy.numberEmiImm * world_size, &auxPopulation, &auxSpider);
    calculateWeightPopulation(&population, dataset, row, column, &auxSpider);
    // showPopulation(&population);

    for (int k = 2; k <= numberGenerations; k++) {
        femaleCooperativeOperator(&population, &auxPopulation);
        maleCooperativeOperator(&population, dataset, row, column, &auxPopulation);
        matingOperator(&population, dataset, row, column, &auxPopulation, &auxSpider);
        replacement(&population, &auxPopulation);
        calculateWeightPopulation(&population, dataset, row, column, &auxSpider);

        MPI_Barrier(MPI_COMM_WORLD);
        runMigration(MPI_COMM_WORLD, world_rank, &population, point, lengthPoint, &policy, k);
        MPI_Barrier(MPI_COMM_WORLD);

        // showPopulation(&population);
        // showBestFitness(&population, i);
        // showBestSpider(&population);
    }

    MPI_Barrier(MPI_COMM_WORLD);
    // showAllResults(&population, numberGenerations, dataset, row, column);
    // showMetricBestSpider(&population, world_rank);
    // showBestSpider(&population);

    // Rank 0 receive best metric from others cores
    int best_rank;
    double best_metric_aux;
    if (world_rank == 0) {
        double best_metric = population.spiders[population.indexBest]->fitness;
        best_rank = 0;
        for (int k = 1; k < world_size; k++) {
            MPI_Recv(&best_metric_aux, 1, MPI_DOUBLE, k, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            if (best_metric_aux >= best_metric) {
                best_metric = best_metric_aux;
                best_rank = k;
            }
        }
        t2 = MPI_Wtime(); 

        printf("[%d, %f, %f]\n", best_rank, best_metric, t2 - t1);

        char fileName[256];
        sprintf(fileName, "%s", "output/psso/example_psso.out");
        FILE *fp = fopen(fileName, "a");
        fprintf(fp, "%f,%f\n", best_metric, t2 - t1);
        fclose(fp);

        showBestSpider(&population);
        // Save centroids and labels
        saveClusterBestSpider(&population, dataset, row, column);
    } else {
        best_metric_aux = population.spiders[population.indexBest]->fitness;
        MPI_Send(&best_metric_aux, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
    }
    MPI_Barrier(MPI_COMM_WORLD);

    freeMemoryReadColumn(columns);
    freeMemoryReadDataset(dataset, row);
    freeMemoryArrayDouble(point);
    freeMemoryPopulation(&population, &auxPopulation, &auxSpider);

    MPI_Finalize();
    return 0;
}

// Run:
// mpirun -n 24 --oversubscribe ./main_psso dataset/iris.cols 3 150 dataset/iris.data policy/policy.in 169735477