/*
============================================================================
Authors:
 	Edwin Alvarez-Mamani and Jose Luis Soncco-Alvarez*
 	*Department of Informatics 
 	Universidad Nacional de San Antonio Abad del Cusco (UNSAAC) - Perú
============================================================================
*/

#ifndef CLUSTERCENTER_H_
#define CLUSTERCENTER_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "structs.h"
#include "utils.h"

void allocateMemoryClusterCenter(ClusterCenterPtr *clusterCenterPtr, int lengthPoint);
void freeMemoryClusterCenter(ClusterCenterPtr clusterCenterPtr);
void allocateMemoryArrayClusterCenter(ClusterCenterPtr **clusterCenterPtr, int lengthCluster, int lengthPoint);
void freeMemoryArrayClusterCenter(ClusterCenterPtr *clusterCenterPtr, int lengthCluster);

/* Methods */
double calculateDistanceCC(ClusterCenterPtr clusterCenterPtr, double *point, int length);
double calculateDistanceCC_(int i, int j, double **dataset, int row, int column);

#endif /* CLUSTERCENTER_H_ */