/*
============================================================================
Authors:
 	Edwin Alvarez-Mamani and Jose Luis Soncco-Alvarez*
 	*Department of Informatics 
 	Universidad Nacional de San Antonio Abad del Cusco (UNSAAC) - Perú
============================================================================
*/

#ifndef POPULATION_H_
#define POPULATION_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "structs.h"
#include "utils.h"
#include "clusterCenter.h"
#include "spider.h"

void freeMemoryPopulation(PopulationPtr populationPtr, AuxPopulationPtr auxPopulationPtr, AuxSpiderPtr auxSpiderPtr);

/* Methods */
double maximumDistance(double **dataset, int row, int column);
void generateInitialPopulation(PopulationPtr populationPtr, int populationSize, int numberClusters, double **dataset,
                                int row, int column, int numberMigration, AuxPopulationPtr auxPopulationPtr, AuxSpiderPtr auxSpiderPtr);
void readInitialPopulation(PopulationPtr populationPtr, int populationSize, int numberClusters, double **dataset, int row, int column, int numberMigration,
						   AuxPopulationPtr auxPopulationPtr, AuxSpiderPtr auxSpiderPtr, double **population, int initialIndexPopulation, int limitCountFitness);
void generatePopulation(int populationSize, int numberClusters, double **dataset, int row, int column);
void evaluateFitnessPopulation(PopulationPtr populationPtr, double **dataset, int row, int column, AuxSpiderPtr auxSpiderPtr);
void calculateBestWorstPopulation(PopulationPtr populationPtr);
void calculateWeightPopulation(PopulationPtr populationPtr, double **dataset, int row, int column, AuxSpiderPtr auxSpiderPtr);
int nearestWithHigherWeightTo(PopulationPtr populationPtr, int i);
void femaleCooperativeOperator(PopulationPtr populationPtr, AuxPopulationPtr auxPopulationPtr);
void calculateMedianWeightOfMales(PopulationPtr populationPtr, AuxPopulationPtr auxPopulationPtr);
int nearestFemaleTo(PopulationPtr populationPtr, int i);
void calculateMaleSpiderWeightedMean(PopulationPtr populationPtr, SpiderPtr spi, AuxPopulationPtr auxPopulationPtr);
void createMatingRoulette(PopulationPtr populationPtr, double *matingRoulette, int lengthMatingRoulette, int  *matingGroup, int lengthMatingGroup);
void matingOperator(PopulationPtr populationPtr, double **dataset, int row, int column, AuxPopulationPtr auxPopulationPtr, AuxSpiderPtr auxSpiderPtr);
void createReplacementRoulette(PopulationPtr populationPtr, double *replacementRoulette, int length);
void maleCooperativeOperator(PopulationPtr populationPtr, double **dataset, int row, int column, AuxPopulationPtr auxPopulationPtr);
void replacement(PopulationPtr populationPtr, AuxPopulationPtr auxPopulationPtr);
void savePopulation(PopulationPtr populationPtr);
void showBestFitness(PopulationPtr populationPtr, int numberGeneration);
void showPopulation(PopulationPtr populationPtr);
void showParameters(PopulationPtr populationPtr, int numberGenerations, int numberDataset);
void showBestSpider(PopulationPtr populationPtr);
void showClusterBestSpider(PopulationPtr populationPtr, double **dataset, int row, int column);
void showMetricBestSpider(PopulationPtr populationPtr, int world_rank);
void showAllResults(PopulationPtr populationPtr, int numberGenerations, double **dataset, int row, int column);
void freeMemoryAuxilarPopulation(PopulationPtr populationPtr, AuxPopulationPtr auxPopulationPtr);
void freeMemoryAuxilarSpider(PopulationPtr populationPtr, AuxSpiderPtr auxSpiderPtr);

#endif /* POPULATION_H_ */