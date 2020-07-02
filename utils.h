/*
============================================================================
Authors:
 	Edwin Alvarez-Mamani, Harley Vera-Olivera* and Jose Luis Soncco-Alvarez*
 	*Department of Informatics 
 	Universidad Nacional de San Antonio Abad del Cusco (UNSAAC) - Perú
============================================================================
*/

#ifndef UTILS_H_
#define UTILS_H_

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include "structs.h"
#include "clusterCenter.h"
#include "spider.h"
#include "population.h"

void generateSeed(int seed);
int randomInt(int n);
double random_();
void allocateMemoryArrayInt(int **array, int length);
void freeMemoryArrayInt(int *array);
void allocateMemoryArrayDouble(double **array, int length);
void freeMemoryArrayDouble(double *array);
void allocateMemoryMatrixDouble(double ***matrix, int row, int column);
void freeMemoryMatrixDouble(double **matrix, int row);
void allocateMemoryReadColumn(int **array, int *column, char *fileName);
void freeMemoryReadColumn(int *array);
void allocateMemoryReadDataset_(double ***matrix, int row, int column, int *columns);
void allocateMemoryReadDataset(double ***matrix, int row, int column, int *columns, char *fileName);
void freeMemoryReadDataset(double **matrix, int row);
void allocateMemoryReadPopulation(double ***matrix, int row, int column, char *fileName);
void freeMemoryReadPopulation(double **matrix, int row);
void allocateMemoryDictionary(DictionaryPtr *dictionaryPtr, int key);
void freeMemoryDictionary(DictionaryPtr dictionaryPtr);
void allocateMemoryArrayDictionary(DictionaryPtr **dictionaryPtr, int lengthDictionary);
void freeMemoryArrayDictionary(DictionaryPtr *dictionaryPtr, int lengthDictionary);
void readPolicy(PolicyPtr policyPtr, char *fileName);

void showArrayDoubleSend(PopulationPtr populationPtr, PolicyPtr policyPtr, double *array, int source);
void showArrayDoubleReceived(PopulationPtr populationPtr, PolicyPtr policyPtr, double *array, int destination, int source, int orderNode);
void showPolicyMigration(PolicyPtr policyPtr);

void insertSort(DictionaryPtr *dictionaryPtr, int lengthDictionary);
void bubbleSort(PopulationPtr populationPtr);
double average(PopulationPtr populationPtr);
double standardDeviation(PopulationPtr populationPtr);

#endif /* UTILS_H_ */