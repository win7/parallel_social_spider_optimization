/*
============================================================================
Authors:
    Edwin Alvarez-Mamani and Jose Luis Soncco-Alvarez*
    *Department of Informatics 
    Universidad Nacional de San Antonio Abad del Cusco (UNSAAC) - Perú
============================================================================
*/

#include "clusterCenter.h"

void allocateMemoryClusterCenter(ClusterCenterPtr *clusterCenterPtr, int lengthPoint){
    *clusterCenterPtr =  (ClusterCenter*)malloc(sizeof(ClusterCenter));
    if (*clusterCenterPtr == NULL){
        printf("No have memory.\n");
        exit(1);
    }
    allocateMemoryArrayDouble(&(*clusterCenterPtr)->point, lengthPoint);
    (*clusterCenterPtr)->length = lengthPoint;
}

void freeMemoryClusterCenter(ClusterCenterPtr clusterCenterPtr){
    freeMemoryArrayDouble(clusterCenterPtr->point);
    free(clusterCenterPtr);
}

void allocateMemoryArrayClusterCenter(ClusterCenterPtr **clusterCenterPtr, int lengthCluster, int lengthPoint){
    *clusterCenterPtr = (ClusterCenterPtr*)malloc(sizeof(ClusterCenter) * lengthCluster);
    if (*clusterCenterPtr == NULL){
        printf("No have memory.\n");
        exit(1);
    }
    for (int i = 0; i < lengthCluster; i++){
        allocateMemoryClusterCenter(&(*clusterCenterPtr)[i], lengthPoint);
    }
}

void freeMemoryArrayClusterCenter(ClusterCenterPtr *clusterCenterPtr, int lengthCluster){
    for (int i = 0; i < lengthCluster; i++){
        freeMemoryClusterCenter(clusterCenterPtr[i]);
    }
    free(clusterCenterPtr);
}

/* Methods */
double calculateDistanceCC(ClusterCenterPtr clusterCenterPtr, double *point, int length){
    int pointDimension = clusterCenterPtr->length;
    double totalSum = 0;
    for(int i = 0; i < pointDimension; i++){
        totalSum += (clusterCenterPtr->point[i] - point[i]) * (clusterCenterPtr->point[i] - point[i]);
    }
    return sqrt(totalSum);
}

double calculateDistanceCC_(int i, int j, double **dataset, int row, int column){
    int pointDimension = column;
    double totalSum = 0.0;
    for(int k = 0; k < pointDimension; k++){
        totalSum += ((dataset[i][k] - dataset[j][k]) * (dataset[i][k] - dataset[j][k]));
    }
    return sqrt(totalSum);
}