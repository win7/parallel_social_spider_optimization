/*
============================================================================
Authors:
 	Edwin Alvarez-Mamani and Jose Luis Soncco-Alvarez*
 	*Department of Informatics 
 	Universidad Nacional de San Antonio Abad del Cusco (UNSAAC) - Perú
============================================================================
*/

#ifndef TOPOLOGY_H_
#define TOPOLOGY_H_

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


void package(PopulationPtr populationPtr, double *point, PolicyPtr policyPtr, int source, int orderNode);
void unpack(PopulationPtr populationPtr, double *point, PolicyPtr policyPtr, int destination, int source, int orderNode);
void ringTopology(MPI_Comm communicator, int world_rank, PopulationPtr populationPtr, double *point, int lengthPoint, PolicyPtr policyPtr);
void treeTopology(MPI_Comm communicator, int world_rank, PopulationPtr populationPtr, double *point, int lengthPoint, PolicyPtr policyPtr);
void netATopology(MPI_Comm communicator, int world_rank, PopulationPtr populationPtr, double *point, int lengthPoint, PolicyPtr policyPtr);
void netBTopology(MPI_Comm communicator, int world_rank, PopulationPtr populationPtr, double *point, int lengthPoint, PolicyPtr policyPtr);
void torusTopology(MPI_Comm communicator, int world_rank, PopulationPtr populationPtr, double *point, int lengthPoint, PolicyPtr policyPtr);
void graphTopology(MPI_Comm communicator, int world_rank, PopulationPtr populationPtr, double *point, int lengthPoint, PolicyPtr policyPtr);
void dinamicTopology(MPI_Comm communicator, int world_rank, PopulationPtr populationPtr, double *point, int lengthPoint, PolicyPtr policyPtr);
void runMigration(MPI_Comm communicator, int world_rank, PopulationPtr populationPtr, double *point, int lengthPoint, PolicyPtr policyPtr, int numberGeneration);

#endif /* TOPOLOGY_H_ */