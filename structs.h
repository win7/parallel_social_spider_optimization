/*
============================================================================
Authors:
 	Edwin Alvarez-Mamani and Jose Luis Soncco-Alvarez*
 	*Department of Informatics 
 	Universidad Nacional de San Antonio Abad del Cusco (UNSAAC) - Perú
============================================================================
*/

#ifndef STRUCTS_H_
#define STRUCTS_H_

#define TRUE 1
#define FALSE 0

struct dictionary {
    int                 key;
    double              value;
};
typedef struct dictionary Dictionary;
typedef Dictionary *DictionaryPtr;

struct clusterCenter {
    double 				*point;					// Array N-dimensional
    int 				length;
};
typedef struct clusterCenter ClusterCenter;
typedef ClusterCenter *ClusterCenterPtr;

struct spider {
    int 				type; 					// female = 0, male = 1
    ClusterCenterPtr 	*centers;				// Array N-dimensional centers
	int 				lengthCenters;
	int 				*datasetClusters;		
	int 				lengthDatasetClusters;
    double 				fitness;
    double 				weight;
};
typedef struct spider Spider;
typedef Spider *SpiderPtr;

struct population {
    int 				numberFemales;
	int 				numberMales;
	int 				numClusters;
	int 				pointDimension;			// m dimension
	double 				radiusMating;			// (parameter)
	SpiderPtr 			*spiders;				// Array N-dimensional point
	int 				lengthSpider;
	SpiderPtr 			*offspring;				// ArrayList N-dimensional point
	int 				lengthOffspring;
	double 				medianWeight;
	int 				indexBest;				// index of the best result
	int 				indexWorst;
    DictionaryPtr       *fitness;
    int                 *indexMigration;		// array for save index the individual for emmigration and immigration (in REMOVE)
    int 				countFitness;			// count call function fitness
    int 				limitCountFitness;		// limit call function fitness
};
typedef struct population Population;
typedef Population *PopulationPtr;

struct auxPopulation {
	double             *males;
	ClusterCenterPtr   *spidersWeightsPtr;
	int                *matingGroup;		   // indexes
	double             *matingRoulette;	       // females + 1 male
	SpiderPtr          spiderWeightedMeanPtr;
	ClusterCenterPtr   *clusCentersPtr;
	double             *replacementRoulette;
};
typedef struct auxPopulation AuxPopulation;
typedef AuxPopulation *AuxPopulationPtr;

struct auxSpider {
    double              *distances;
    int                 *numPointsForCluster;
    double              **sum;  // row: populationPtr->numClusters, column: populationPtr->pointDimension
};
typedef struct auxSpider AuxSpider;
typedef AuxSpider *AuxSpiderPtr;

typedef enum {RING, TREE, NETA, NETB, TORUS, GRAPH, SAME, GOODBAD, RAND} Topology;
typedef enum {CLONE, REMOVE} Emigration;
typedef enum {BEST, WORST, RANDOM} ChoiceEmiImm;
struct policy {
    Topology            topology;
    Emigration          emigration;
    ChoiceEmiImm        choiceEmi;
    ChoiceEmiImm        choiceImm;
    int                 numberEmiImm;
    int                 intervalEmiImm;
};
typedef struct policy Policy;
typedef Policy *PolicyPtr;

#endif /* STRUCTS_H_ */