/*
============================================================================
Authors:
 	Edwin Alvarez-Mamani and Jose Luis Soncco-Alvarez*
 	*Department of Informatics 
 	Universidad Nacional de San Antonio Abad del Cusco (UNSAAC) - Perú
============================================================================
*/

#include "spider.h"

void allocateMemorySpider(SpiderPtr *spiderPtr, int type, int lengthCluster, int lengthPoint,
						   double **dataset, int row, int column){
	*spiderPtr =  (Spider*)malloc(sizeof(Spider));
	if (*spiderPtr == NULL){
    	printf("No have memory.\n");
        exit(1);
    }
    
	(*spiderPtr)->type = type;
	allocateMemoryArrayClusterCenter(&(*spiderPtr)->centers, lengthCluster, lengthPoint);
	(*spiderPtr)->lengthCenters = lengthCluster;
	allocateMemoryArrayInt(&(*spiderPtr)->datasetClusters, row);
	(*spiderPtr)->lengthDatasetClusters = row;
	(*spiderPtr)->fitness = INT_MAX;
	(*spiderPtr)->weight = 0;
}

void freeMemorySpider(SpiderPtr spiderPtr){
	freeMemoryArrayClusterCenter(spiderPtr->centers, spiderPtr->lengthCenters);
	freeMemoryArrayInt(spiderPtr->datasetClusters);
	free(spiderPtr);
}

void allocateMemoryArraySpider(SpiderPtr **spiderPtr, int lengthSpider, int type, int lengthCluster,
							    int lengthPoint, double **dataset, int row, int column){
	*spiderPtr = (SpiderPtr*)malloc(sizeof(Spider) * lengthSpider);
    if (*spiderPtr == NULL){
    	printf("No have memory.\n");
        exit(1);
    }
   	for (int i = 0; i < lengthSpider; i++){
   		allocateMemorySpider(&(*spiderPtr)[i], type, lengthCluster, lengthPoint, dataset, row, column);
    }
}

void freeMemoryArraySpider(SpiderPtr *spiderPtr, int lengthSpider){
	for (int i = 0; i < lengthSpider; i++){
    	freeMemorySpider(spiderPtr[i]);
    }
	free(spiderPtr);
}

/* Methods */
double calculateMetric(SpiderPtr spiderPtr, double **dataset, int row, int column){
	double distance = 0;
	int index = 0;
	for(int i = 0; i < row; i++){
		index = spiderPtr->datasetClusters[i];
		distance += calculateDistanceCC(spiderPtr->centers[index], dataset[i], column);
	}
	return distance;
}

/** Calculate the dist. between "current" spider and spider "spi" **/
double calculateDistanceS(SpiderPtr spiderPtr, SpiderPtr spi){
	double totalDistance = 0;
	for(int i = 0; i < spiderPtr->lengthCenters; i++){
		totalDistance += calculateDistanceCC(spiderPtr->centers[i], spi->centers[i]->point, spi->centers[i]->length);
	}
	return totalDistance;
}

void buildClusters(SpiderPtr spiderPtr, double **dataset, int row, int column, AuxSpiderPtr auxSpiderPtr){
	int numClusters = spiderPtr->lengthCenters;
	double min = 0;
	int clusterIndex = 0;
	// build the dataset clusters
	for(int i = 0; i < row; i++){
		for(int j = 0; j < numClusters; j++){
			// euclidean distance from a dataset point "i" to each cluster center
			auxSpiderPtr->distances[j] = calculateDistanceCC(spiderPtr->centers[j], dataset[i], column);
		}
		// determine minimum distance
		min = auxSpiderPtr->distances[0];
		clusterIndex = 0;
		for(int j = 1; j < numClusters; j++){
			if (auxSpiderPtr->distances[j] < min){
				min = auxSpiderPtr->distances[j];
				clusterIndex = j;
			}
		}
		// assign cluster index of the minimum distance
		// to the dataset point "i" 
		spiderPtr->datasetClusters[i] = clusterIndex;
	}
}

void computeNewClusterCenters(SpiderPtr spiderPtr, double **dataset, int row, int column, AuxSpiderPtr auxSpiderPtr){
	// calculate total sum for each cluster
	int numClusters = spiderPtr->lengthCenters;
	int pointDimension = column;
	int pos = 0;
	int index = 0;
	double newValue = 0;

	for (int i = 0; i < numClusters; i++){
        auxSpiderPtr->numPointsForCluster[i] = 0;
    }
	
	for (int i = 0; i < numClusters; i++){
		for (int j = 0; j < pointDimension; j++){
			auxSpiderPtr->sum[i][j] = 0;
		}
    }

	for(int i = 0; i < row; i++){
		index = spiderPtr->datasetClusters[i];
		for(int j = 0; j < pointDimension; j++){
			auxSpiderPtr->sum[index][j] += dataset[i][j];
		}
		auxSpiderPtr->numPointsForCluster[index]++;
	}
	// replace mean points as new cluster centers
	for(int i = 0; i < numClusters; i++){
		for(int j = 0; j < pointDimension; j++){
			if (auxSpiderPtr->numPointsForCluster[i] == 0){
				// when all points of cluster have the same value
				// choose new value from random_ point at dataset
				pos = randomInt(row);
				newValue = dataset[pos][j];
			}
			else{
				// calculate mean point
				newValue = auxSpiderPtr->sum[i][j] / auxSpiderPtr->numPointsForCluster[i];
			}
			spiderPtr->centers[i]->point[j] = newValue;
		}
	}
}

void evaluateFitness(PopulationPtr populationPtr, SpiderPtr spiderPtr, double **dataset, int row, int column, AuxSpiderPtr auxSpiderPtr){
	// build clusters according to its centers
	buildClusters(spiderPtr, dataset, row, column, auxSpiderPtr);
	// compute new cluster centers
	computeNewClusterCenters(spiderPtr, dataset, row, column, auxSpiderPtr);
	// calculate clustering metric
	spiderPtr->fitness = calculateMetric(spiderPtr, dataset, row, column);

	populationPtr->countFitness += 1;

	/* if (populationPtr->countFitness >= populationPtr->limitCountFitness) {
		// printf("end call evaluateFitness %d \n", populationPtr->countFitness);
		return false ;
	} else {
		// build clusters according to its centers
		buildClusters(spiderPtr, dataset, row, column, auxSpiderPtr);
		// compute new cluster centers
		computeNewClusterCenters(spiderPtr, dataset, row, column, auxSpiderPtr);
		// calculate clustering metric
		spiderPtr->fitness = calculateMetric(spiderPtr, dataset, row, column);

		populationPtr->countFitness += 1;
		return true;
	} */
}

/** Difference of the cluster centers of two spiders **/
void diffSpiders(SpiderPtr spi1, SpiderPtr spi2, ClusterCenterPtr *c, int length){
	for (int i = 0; i < spi1->lengthCenters; i++){
		for (int j = 0; j < spi1->centers[0]->length; j++){
			c[i]->point[j] = spi1->centers[i]->point[j] - spi2->centers[i]->point[j];
		}
	}
}

/** Multiply cluster centers by a constant **/
void sumSpider(SpiderPtr spiderPtr, ClusterCenterPtr *c, int length, double signal){
	for (int i = 0; i < spiderPtr->lengthCenters; i++){
		for (int j = 0; j < spiderPtr->centers[0]->length; j++){
			spiderPtr->centers[i]->point[j] += signal * c[i]->point[j]; 				 
		}
	}
}

/** Multiply cluster centers by a constant **/
void mulClusterCentersByConstant(ClusterCenterPtr *c, int length, double cons){
	for(int i = 0; i < length; i++){
		for(int j = 0; j < c[0]->length; j++){
			c[i]->point[j] *= cons;
		}
	}
}

void showSpider(SpiderPtr spiderPtr){
	printf("%s", "[");
	for(int i = 0; i < spiderPtr->lengthCenters; i++){
		printf("%s", "(");
		for(int j = 0; j < spiderPtr->centers[0]->length; j++){
			printf("%f; ", spiderPtr->centers[i]->point[j]);
		}
		printf("%s", "),");
	}
	printf("] Fitness: %f \n", spiderPtr->fitness);
}