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
	double **population_generated = NULL;
	
	char *fileNameColumns = argv[1];
	int numberClusters = atoi(argv[2]);
	int row = atoi(argv[3]);
	char *fileNameRows = argv[4];
	char *fileNamePopulation = argv[5];
	int limitCallFitness = atoi(argv[6]);
	int seed = atoi(argv[7]);
	char *fileNameOutput = argv[8];

	int numberGenerations = 100 * 1000000;
	int populationSize = 100 * 24;

	clock_t t1 = clock();

	allocateMemoryReadColumn(&columns, &column, fileNameColumns);
	allocateMemoryReadDataset(&dataset, row, column, columns, fileNameRows);
	allocateMemoryReadPopulation(&population_generated, populationSize, column * numberClusters, fileNamePopulation);

	generateSeed(seed);
	readInitialPopulation(&population, populationSize, numberClusters, dataset, row, column, 0, 
						  &auxPopulation, &auxSpider, population_generated, 0, limitCallFitness);
	calculateWeightPopulation(&population, dataset, row, column, &auxSpider);
	// showPopulation(&population);
	
	char fileName[256];
	sprintf(fileName, "%s", fileNameOutput);
	FILE *fp = fopen(fileName, "a");
	
	float best_metric = 0;
	int count_fitness = 0;

	for(int k = 2; k <= numberGenerations; k++) {
		// get metric and # eval fitness value for generation (convergence)
		/* best_metric = population.spiders[population.indexBest]->fitness;
		count_fitness = population.countFitness;
		printf("[%d,%f,%d]\n", k - 1, best_metric, count_fitness);
		fprintf(fp, "%d,%f,%d\n", k - 1, best_metric, count_fitness); */
		
		femaleCooperativeOperator(&population, &auxPopulation);
		maleCooperativeOperator(&population, dataset, row, column, &auxPopulation);
		matingOperator(&population, dataset, row, column, &auxPopulation, &auxSpider);
		replacement(&population, &auxPopulation);
		calculateWeightPopulation(&population, dataset, row, column, &auxSpider);

		// showPopulation(&population);
		// showBestFitness(&population, k);
		// showBestSpider(&population);

		count_fitness = population.countFitness;
		if (count_fitness >= limitCallFitness) {
			// printf("End core %d: %d\n", 0, count_fitness);
			break;
		}
	}

	// showAllResults(&population, numberGenerations, dataset, row, column);
	// showMetricBestSpider(&population);

	best_metric = population.spiders[population.indexBest]->fitness;
	clock_t t2 = clock();

	printf("[%f,%f]\n", best_metric, ((double)(t2 - t1)) / CLOCKS_PER_SEC);
	fprintf(fp, "%f,%f\n", best_metric, ((double)(t2 - t1)) / CLOCKS_PER_SEC);

	/* char fileName[256];
	sprintf(fileName, "%s", "output/aux_sso.out");
	FILE *fp = fopen(fileName, "a");
	fprintf(fp, "%f,%f\n", best_metric, ((double)(t2 - t1)) / CLOCKS_PER_SEC);
	fclose(fp); */
	fclose(fp);

	freeMemoryReadColumn(columns);
	freeMemoryReadDataset(dataset, row);
	freeMemoryReadDataset(population_generated, populationSize);
	freeMemoryPopulation(&population, &auxPopulation, &auxSpider);

	return 0;
}

// Run:
// $ ./main_sso_exp dataset/iris.cols 3 150 dataset/iris.data output/population/iris_0_0.data 10293 169735477 output/sso/iris_0_100.out
