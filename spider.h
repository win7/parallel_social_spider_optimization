/*
============================================================================
Authors:
 	Edwin Alvarez-Mamani and Jose Luis Soncco-Alvarez*
 	*Department of Informatics 
 	Universidad Nacional de San Antonio Abad del Cusco (UNSAAC) - Perú
============================================================================
*/

#ifndef SPIDER_H_
#define SPIDER_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <stdbool.h> 
#include "structs.h"
#include "utils.h"
#include "clusterCenter.h"

void allocateMemorySpider(SpiderPtr *spiderPtr, int type, int lengthCluster, int lengthPoint,
						   double **dataset, int row, int column);
void freeMemorySpider(SpiderPtr spiderPtr);
void allocateMemoryArraySpider(SpiderPtr **spiderPtr, int lengthSpider, int type, int lengthCluster,
					   	 		int lengthPoint, double **dataset, int row, int column);
void freeMemoryArraySpider(SpiderPtr *spiderPtr, int lengthSpider);

/* Methods */
double calculateMetric(SpiderPtr spiderPtr, double **dataset, int row, int column);
double calculateDistanceS(SpiderPtr spiderPtr, SpiderPtr spi);
void buildClusters(SpiderPtr spiderPtr, double **dataset, int row, int column, AuxSpiderPtr auxSpiderPtr);
void computeNewClusterCenters(SpiderPtr spiderPtr, double **dataset, int row, int column, AuxSpiderPtr auxSpiderPtr);
void evaluateFitness(PopulationPtr populationPtr, SpiderPtr spiderPtr, double **dataset, int row, int column, AuxSpiderPtr auxSpiderPtr);
void diffSpiders(SpiderPtr spi1, SpiderPtr spi2, ClusterCenterPtr *c, int length);
void sumSpider(SpiderPtr spiderPtr, ClusterCenterPtr *c, int length, double signal);
void mulClusterCentersByConstant(ClusterCenterPtr *c, int length, double cons);
void showSpider(SpiderPtr spiderPtr);

#endif /* SPIDER_H_ */