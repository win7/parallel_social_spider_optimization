/*
============================================================================
Authors:
    Edwin Alvarez-Mamani and Jose Luis Soncco-Alvarez*
    *Department of Informatics 
    Universidad Nacional de San Antonio Abad del Cusco (UNSAAC) - Perú
============================================================================
*/
// OBS: MPI_DOUBLE was change for MPI_FLOAT because:
// Max size buffer for array (double) is 4096 bytes: (size array) * (size double) = 505 * 8 = 4040
// Max size buffer for array (float) is 4096 bytes: (size array) * (size float) = 1010 * 4 = 4040
// Only using MPI_FLOAT for send and recived point, for other case using MPI_DOUBLE

#include "topology.h"

void package(PopulationPtr populationPtr, double *point, PolicyPtr policyPtr, int source, int orderNode){
    int index = 0;
    switch (policyPtr->choiceEmi) { 
        case BEST:
            if (policyPtr->emigration == REMOVE) {
                for (int k = 0; k < policyPtr->numberEmiImm; k++) {
                    index = populationPtr->fitness[(orderNode - 1) * policyPtr->numberEmiImm + k]->key;
                    populationPtr->indexMigration[(orderNode - 1) * policyPtr->numberEmiImm + k] = index;
                    for(int i = 0; i < populationPtr->numClusters; i++){
                        for(int j = 0; j < populationPtr->pointDimension; j++){
                            point[(k * populationPtr->numClusters + i) * populationPtr->pointDimension + j] = populationPtr->spiders[index]->centers[i]->point[j];
                        }
                    }
                }
            } else {    // CLONE
                for (int k = 0; k < policyPtr->numberEmiImm; k++) {
                    index = populationPtr->fitness[k]->key;
                    for(int i = 0; i < populationPtr->numClusters; i++){
                        for(int j = 0; j < populationPtr->pointDimension; j++){
                            point[(k * populationPtr->numClusters + i) * populationPtr->pointDimension + j] = populationPtr->spiders[index]->centers[i]->point[j];
                        }
                    }
                }
            }
        break;
        case WORST:
            if (policyPtr->emigration == REMOVE) {
                for (int k = 0; k < policyPtr->numberEmiImm; k++) {
                    index = populationPtr->fitness[populationPtr->lengthSpider - 1 - ((orderNode - 1) * policyPtr->numberEmiImm + k)]->key;
                    populationPtr->indexMigration[(orderNode - 1) * policyPtr->numberEmiImm + k] = index;
                    for(int i = 0; i < populationPtr->numClusters; i++){
                        for(int j = 0; j < populationPtr->pointDimension; j++){
                            point[(k * populationPtr->numClusters + i) * populationPtr->pointDimension + j] = populationPtr->spiders[index]->centers[i]->point[j];
                        }
                    }
                }
            } else {    // CLONE
                for (int k = 0; k < policyPtr->numberEmiImm; k++) {
                    index = populationPtr->fitness[populationPtr->lengthSpider - 1 - k]->key;
                    for(int i = 0; i < populationPtr->numClusters; i++){
                        for(int j = 0; j < populationPtr->pointDimension; j++){
                            point[(k * populationPtr->numClusters + i) * populationPtr->pointDimension + j] = populationPtr->spiders[index]->centers[i]->point[j];
                        }
                    }
                }
            }
        break;
        case RANDOM:
            if (policyPtr->emigration == REMOVE) {
                for (int k = 0; k < policyPtr->numberEmiImm; k++) {
                    index = randomInt(populationPtr->lengthSpider);
                    populationPtr->indexMigration[(orderNode - 1) * policyPtr->numberEmiImm + k] = index;
                    for(int i = 0; i < populationPtr->numClusters; i++){
                        for(int j = 0; j < populationPtr->pointDimension; j++){
                            point[(k * populationPtr->numClusters + i) * populationPtr->pointDimension + j] = populationPtr->spiders[index]->centers[i]->point[j];
                        }
                    }
                }
            } else {    // CLONE
                for (int k = 0; k < policyPtr->numberEmiImm; k++) {
                    index = randomInt(populationPtr->lengthSpider);
                    for(int i = 0; i < populationPtr->numClusters; i++){
                        for(int j = 0; j < populationPtr->pointDimension; j++){
                            point[(k * populationPtr->numClusters + i) * populationPtr->pointDimension + j] = populationPtr->spiders[index]->centers[i]->point[j];
                        }
                    }
                }
            }
        break;
    }
    // showArrayDoubleSend(populationPtr, policyPtr, point, source);
}

void unpack(PopulationPtr populationPtr, double *point, PolicyPtr policyPtr, int destination, int source, int orderNode){
    int index = 0;
    switch (policyPtr->choiceImm) {
        case BEST:
            if (policyPtr->emigration == REMOVE) {
                for (int k = 0; k < policyPtr->numberEmiImm; k++) {
                    index = populationPtr->indexMigration[(orderNode - 1) * policyPtr->numberEmiImm + k];
                    for(int i = 0; i < populationPtr->numClusters; i++){
                        for(int j = 0; j < populationPtr->pointDimension; j++){
                            populationPtr->spiders[index]->centers[i]->point[j] = point[(k * populationPtr->numClusters + i) * populationPtr->pointDimension + j];
                        }
                    }
                }
            } else {    // REPLACE
                for (int k = 0; k < policyPtr->numberEmiImm; k++) {
                    index = populationPtr->fitness[(orderNode - 1) * policyPtr->numberEmiImm + k]->key;
                    for(int i = 0; i < populationPtr->numClusters; i++){
                        for(int j = 0; j < populationPtr->pointDimension; j++){
                            populationPtr->spiders[index]->centers[i]->point[j] = point[(k * populationPtr->numClusters + i) * populationPtr->pointDimension + j];
                        }
                    }
                }
            }
        break;
        case WORST:
            if (policyPtr->emigration == REMOVE) {
                for (int k = 0; k < policyPtr->numberEmiImm; k++) {
                    index = populationPtr->indexMigration[(orderNode - 1) * policyPtr->numberEmiImm + k];
                    for(int i = 0; i < populationPtr->numClusters; i++){
                        for(int j = 0; j < populationPtr->pointDimension; j++){
                            populationPtr->spiders[index]->centers[i]->point[j] = point[(k * populationPtr->numClusters + i) * populationPtr->pointDimension + j];
                        }
                    }
                }
            } else {    // REPLACE
                for(int k = 0; k < policyPtr->numberEmiImm; k++){
                    index = populationPtr->fitness[populationPtr->lengthSpider - 1 - ((orderNode - 1) * policyPtr->numberEmiImm + k)]->key;
                    for(int i = 0; i < populationPtr->numClusters; i++){
                        for(int j = 0; j < populationPtr->pointDimension; j++){
                            populationPtr->spiders[index]->centers[i]->point[j] = point[(k * populationPtr->numClusters + i) * populationPtr->pointDimension + j];
                        }
                    }
                }
            }
        break;
        case RANDOM:
            if (policyPtr->emigration == REMOVE) {
                for (int k = 0; k < policyPtr->numberEmiImm; k++) {
                    index = populationPtr->indexMigration[(orderNode - 1) * policyPtr->numberEmiImm + k];
                    for(int i = 0; i < populationPtr->numClusters; i++){
                        for(int j = 0; j < populationPtr->pointDimension; j++){
                            populationPtr->spiders[index]->centers[i]->point[j] = point[(k * populationPtr->numClusters + i) * populationPtr->pointDimension + j];
                        }
                    }
                }
            } else {    // REPLACE
                for(int k = 0; k < policyPtr->numberEmiImm; k++){
                    index = randomInt(populationPtr->lengthSpider);
                    for(int i = 0; i < populationPtr->numClusters; i++){
                        for(int j = 0; j < populationPtr->pointDimension; j++){
                            populationPtr->spiders[index]->centers[i]->point[j] = point[(k * populationPtr->numClusters + i) * populationPtr->pointDimension + j];
                        }
                    }
                }
            }
        break;
    }
    // showArrayDoubleReceived(populationPtr, policyPtr, point, destination, source, orderNode);
}

void ringTopology(MPI_Comm communicator, int world_rank, PopulationPtr populationPtr, double *point, int lengthPoint, PolicyPtr policyPtr) {
    MPI_Status status;
    int world_size;
    MPI_Comm_size(communicator, &world_size);

    package(populationPtr, point, policyPtr, world_rank, 1);
    MPI_Send(point, lengthPoint, MPI_FLOAT, (world_rank + 1) % world_size, 0, communicator);
    MPI_Barrier(communicator);
    MPI_Recv(point, lengthPoint, MPI_FLOAT, (world_rank + world_size - 1) % world_size, 0, communicator, &status);
    unpack(populationPtr, point, policyPtr, world_rank, status.MPI_SOURCE, 1);
}

void treeTopology(MPI_Comm communicator, int world_rank, PopulationPtr populationPtr, double *point, int lengthPoint, PolicyPtr policyPtr) {
    MPI_Status status;
    int world_size;
    MPI_Comm_size(communicator, &world_size);

    if(world_rank == 0){
        package(populationPtr, point, policyPtr, world_rank, 1);
        MPI_Send(point, lengthPoint, MPI_FLOAT, (2 * world_rank) + 1, 0, communicator);
        package(populationPtr, point, policyPtr, world_rank, 2);
        MPI_Send(point, lengthPoint, MPI_FLOAT, (2 * world_rank) + 2, 0, communicator);
        MPI_Barrier(communicator);
        MPI_Recv(point, lengthPoint, MPI_FLOAT, (2 * world_rank) + 1, 0, communicator, &status);
        unpack(populationPtr, point, policyPtr, world_rank, status.MPI_SOURCE, 1);
        MPI_Recv(point, lengthPoint, MPI_FLOAT, (2 * world_rank) + 2, 0, communicator, &status);
        unpack(populationPtr, point, policyPtr, world_rank, status.MPI_SOURCE, 2);
    }else {
        if(world_rank >= 1 && world_rank <= 6){
            package(populationPtr, point, policyPtr, world_rank, 1);
            MPI_Send(point, lengthPoint, MPI_FLOAT, (world_rank - 1) / 2, 0, communicator);
            package(populationPtr, point, policyPtr, world_rank, 2);
            MPI_Send(point, lengthPoint, MPI_FLOAT, (2 * world_rank) + 1, 0, communicator);
            package(populationPtr, point, policyPtr, world_rank, 3);
            MPI_Send(point, lengthPoint, MPI_FLOAT, (2 * world_rank) + 2, 0, communicator);
            MPI_Barrier(communicator);
            MPI_Recv(point, lengthPoint, MPI_FLOAT, (world_rank - 1) / 2, 0, communicator, &status);
            unpack(populationPtr, point, policyPtr, world_rank, status.MPI_SOURCE, 1);
            MPI_Recv(point, lengthPoint, MPI_FLOAT, (2 * world_rank) + 1, 0, communicator, &status);
            unpack(populationPtr, point, policyPtr, world_rank, status.MPI_SOURCE, 2);
            MPI_Recv(point, lengthPoint, MPI_FLOAT, (2 * world_rank) + 2, 0, communicator, &status);
            unpack(populationPtr, point, policyPtr, world_rank, status.MPI_SOURCE, 3);
        }else {
            if(world_rank >= 7 && world_rank <= 15){
                package(populationPtr, point, policyPtr, world_rank, 1);
                MPI_Send(point, lengthPoint, MPI_FLOAT, (world_rank - 1) / 2, 0, communicator);
                package(populationPtr, point, policyPtr, world_rank, 2);
                MPI_Send(point, lengthPoint, MPI_FLOAT, world_rank + 8, 0, communicator);
                MPI_Barrier(communicator);
                MPI_Recv(point, lengthPoint, MPI_FLOAT, (world_rank - 1) / 2, 0, communicator, &status);
                unpack(populationPtr, point, policyPtr, world_rank, status.MPI_SOURCE, 1);
                MPI_Recv(point, lengthPoint, MPI_FLOAT, world_rank + 8, 0, communicator, &status);
                unpack(populationPtr, point, policyPtr, world_rank, status.MPI_SOURCE, 2);
            }else {
                package(populationPtr, point, policyPtr, world_rank, 1);
                MPI_Send(point, lengthPoint, MPI_FLOAT, world_rank - 8, 0, communicator);
                MPI_Barrier(communicator);
                MPI_Recv(point, lengthPoint, MPI_FLOAT, world_rank - 8, 0, communicator, &status);
                unpack(populationPtr, point, policyPtr, world_rank, status.MPI_SOURCE, 1);
            }
        }
    }
}

void netATopology(MPI_Comm communicator, int world_rank, PopulationPtr populationPtr, double *point, int lengthPoint, PolicyPtr policyPtr) {
    MPI_Status status;
    int world_size;
    MPI_Comm_size(communicator, &world_size);
    
    if (world_rank == 1 || world_rank == 2) {
        package(populationPtr, point, policyPtr, world_rank, 1);
        MPI_Send(point, lengthPoint, MPI_FLOAT, 
                (world_rank - 1 + 24) % world_size, 0, communicator);
        package(populationPtr, point, policyPtr, world_rank, 2);
        MPI_Send(point, lengthPoint, MPI_FLOAT, 
                (world_rank + 1) % world_size, 0, communicator);
        package(populationPtr, point, policyPtr, world_rank, 3);
        MPI_Send(point, lengthPoint, MPI_FLOAT, 
                (world_rank + 4) % world_size, 0, communicator);
        MPI_Barrier(communicator);
        MPI_Recv(point, lengthPoint, MPI_FLOAT, 
                (world_rank -1 + 24) % world_size, 0, 
                communicator, &status);
        unpack(populationPtr, point, policyPtr, world_rank, 
                status.MPI_SOURCE, 1);
        MPI_Recv(point, lengthPoint, MPI_FLOAT, 
                (world_rank + 1) % world_size, 0, communicator, &status);
        unpack(populationPtr, point, policyPtr, world_rank,
                status.MPI_SOURCE, 2);
        MPI_Recv(point, lengthPoint, MPI_FLOAT, 
                (world_rank + 4) % world_size, 0, communicator, &status);
        unpack(populationPtr, point, policyPtr, world_rank, 
                status.MPI_SOURCE, 3);
    } else {
        if (world_rank == 21 || world_rank == 22) {
            package(populationPtr, point, policyPtr, world_rank, 1);
            MPI_Send(point, lengthPoint, MPI_FLOAT, 
                    (world_rank - 4 + 24) % world_size, 0, communicator);
            package(populationPtr, point, policyPtr, world_rank, 2);
            MPI_Send(point, lengthPoint, MPI_FLOAT, 
                    (world_rank -1 + 24) % world_size, 0, communicator);
            package(populationPtr, point, policyPtr, world_rank, 3);
            MPI_Send(point, lengthPoint, MPI_FLOAT, 
                    (world_rank + 1) % world_size, 0, communicator);
            MPI_Barrier(communicator);
            MPI_Recv(point, lengthPoint, MPI_FLOAT, 
                    (world_rank -4 + 24) % world_size, 0, 
                    communicator, &status);
            unpack(populationPtr, point, policyPtr, 
                    world_rank, status.MPI_SOURCE, 1);
            MPI_Recv(point, lengthPoint, MPI_FLOAT, 
                    (world_rank - 1 + 24) % world_size, 0, 
                    communicator, &status);
            unpack(populationPtr, point, policyPtr, world_rank, 
                    status.MPI_SOURCE, 2);
            MPI_Recv(point, lengthPoint, MPI_FLOAT, 
                    (world_rank + 1) % world_size, 0, communicator, &status);
            unpack(populationPtr, point, policyPtr, world_rank, 
                    status.MPI_SOURCE, 3);
        } else {
            if (world_rank % 4 == 0) {
                package(populationPtr, point, policyPtr, world_rank, 1);
                MPI_Send(point, lengthPoint, MPI_FLOAT, 
                        (world_rank - 4 + 24) % world_size, 0, communicator);
                package(populationPtr, point, policyPtr, world_rank, 2);
                MPI_Send(point, lengthPoint, MPI_FLOAT, 
                        (world_rank + 1) % world_size, 0, communicator);
                package(populationPtr, point, policyPtr, world_rank, 3);
                MPI_Send(point, lengthPoint, MPI_FLOAT, 
                        (world_rank + 4) % world_size, 0, communicator);
                MPI_Barrier(communicator);
                MPI_Recv(point, lengthPoint, MPI_FLOAT, 
                        (world_rank - 4 + 24) % world_size, 0, 
                        communicator, &status);
                unpack(populationPtr, point, policyPtr, world_rank, 
                        status.MPI_SOURCE, 1);
                MPI_Recv(point, lengthPoint, MPI_FLOAT, 
                        (world_rank + 1) % world_size, 0, communicator, 
                        &status);
                unpack(populationPtr, point, policyPtr, world_rank, 
                        status.MPI_SOURCE, 2);
                MPI_Recv(point, lengthPoint, MPI_FLOAT, 
                        (world_rank + 4) % world_size, 0, communicator, 
                        &status);
                unpack(populationPtr, point, policyPtr, world_rank, 
                        status.MPI_SOURCE, 3);
            } else {
                if ((world_rank + 1) % 4 == 0) {
                    package(populationPtr, point, policyPtr, world_rank, 1);
                    MPI_Send(point, lengthPoint, MPI_FLOAT, 
                            (world_rank - 4 + 24) % world_size, 0, 
                            communicator);
                    package(populationPtr, point, policyPtr, world_rank, 2);
                    MPI_Send(point, lengthPoint, MPI_FLOAT, 
                            (world_rank - 1 + 24) % world_size, 0, 
                            communicator);
                    package(populationPtr, point, policyPtr, world_rank, 3);
                    MPI_Send(point, lengthPoint, MPI_FLOAT, 
                            (world_rank  + 4) % world_size, 0, communicator);
                    MPI_Barrier(communicator);
                    MPI_Recv(point, lengthPoint, MPI_FLOAT, 
                            (world_rank - 4 + 24) % world_size, 0, 
                            communicator, &status);
                    unpack(populationPtr, point, policyPtr, world_rank, 
                            status.MPI_SOURCE, 1);
                    MPI_Recv(point, lengthPoint, MPI_FLOAT, 
                            (world_rank - 1 + 24) % world_size, 0, 
                            communicator, &status);
                    unpack(populationPtr, point, policyPtr, world_rank, 
                            status.MPI_SOURCE, 2);
                    MPI_Recv(point, lengthPoint, MPI_FLOAT, 
                            (world_rank + 4) % world_size, 0, communicator, 
                            &status);
                    unpack(populationPtr, point, policyPtr, world_rank, 
                            status.MPI_SOURCE, 3);
                } else {
                    package(populationPtr, point, policyPtr, world_rank, 1);
                    MPI_Send(point, lengthPoint, MPI_FLOAT, 
                            (world_rank - 4 + 24) % world_size, 0, 
                            communicator);
                    package(populationPtr, point, policyPtr, world_rank, 2);
                    MPI_Send(point, lengthPoint, MPI_FLOAT, 
                            (world_rank - 1 + 24) % world_size, 0, 
                            communicator);
                    package(populationPtr, point, policyPtr, world_rank, 3);
                    MPI_Send(point, lengthPoint, MPI_FLOAT, 
                            (world_rank + 1) % world_size, 0, communicator);
                    package(populationPtr, point, policyPtr, world_rank, 4);
                    MPI_Send(point, lengthPoint, MPI_FLOAT, 
                            (world_rank + 4) % world_size, 0, communicator);
                    MPI_Barrier(communicator);
                    MPI_Recv(point, lengthPoint, MPI_FLOAT, 
                            (world_rank - 4 + 24) % world_size, 0, 
                            communicator, &status);
                    unpack(populationPtr, point, policyPtr, world_rank, 
                            status.MPI_SOURCE, 1);
                    MPI_Recv(point, lengthPoint, MPI_FLOAT, 
                            (world_rank - 1 + 24) % world_size, 0, 
                            communicator, &status);
                    unpack(populationPtr, point, policyPtr, world_rank, 
                            status.MPI_SOURCE, 2);
                    MPI_Recv(point, lengthPoint, MPI_FLOAT, 
                            (world_rank + 1) % world_size, 0, communicator, 
                            &status);
                    unpack(populationPtr, point, policyPtr, world_rank, 
                            status.MPI_SOURCE, 3);
                    MPI_Recv(point, lengthPoint, MPI_FLOAT, 
                            (world_rank + 4) % world_size, 0, communicator, 
                            &status);
                    unpack(populationPtr, point, policyPtr, world_rank, 
                            status.MPI_SOURCE, 4);
                }
            }
        }
    }
}

void netBTopology(MPI_Comm communicator, int world_rank, PopulationPtr populationPtr, double *point, int lengthPoint, PolicyPtr policyPtr) {
    MPI_Status status;
    int world_size;
    MPI_Comm_size(communicator, &world_size);
    
    if (world_rank == 1 || world_rank == 2) {
        package(populationPtr, point, policyPtr, world_rank, 1);
        MPI_Send(point, lengthPoint, MPI_FLOAT, 
                (world_rank - 1 + 24) % world_size, 0, communicator);
        package(populationPtr, point, policyPtr, world_rank, 2);
        MPI_Send(point, lengthPoint, MPI_FLOAT, 
                (world_rank + 1) % world_size, 0, communicator);
        package(populationPtr, point, policyPtr, world_rank, 3);
        MPI_Send(point, lengthPoint, MPI_FLOAT, 
                (world_rank + 4) % world_size, 0, communicator);
        MPI_Barrier(communicator);
        MPI_Recv(point, lengthPoint, MPI_FLOAT, 
                (world_rank -1 + 24) % world_size, 0, 
                communicator, &status);
        unpack(populationPtr, point, policyPtr, world_rank, 
                status.MPI_SOURCE, 1);
        MPI_Recv(point, lengthPoint, MPI_FLOAT, 
                (world_rank + 1) % world_size, 0, 
                communicator, &status);
        unpack(populationPtr, point, policyPtr, world_rank, 
                status.MPI_SOURCE, 2);
        MPI_Recv(point, lengthPoint, MPI_FLOAT, 
                (world_rank + 4) % world_size, 0,
                communicator, &status);
        unpack(populationPtr, point, policyPtr, world_rank, 
                status.MPI_SOURCE, 3);
    } else {
        if (world_rank == 21 || world_rank == 22) {
            package(populationPtr, point, policyPtr, world_rank, 1);
            MPI_Send(point, lengthPoint, MPI_FLOAT, 
                    (world_rank - 4 + 24) % world_size, 0, communicator);
            package(populationPtr, point, policyPtr, world_rank, 2);
            MPI_Send(point, lengthPoint, MPI_FLOAT, 
                    (world_rank -1 + 24) % world_size, 0, communicator);
            package(populationPtr, point, policyPtr, world_rank, 3);
            MPI_Send(point, lengthPoint, MPI_FLOAT, 
                    (world_rank + 1) % world_size, 0, communicator);
            MPI_Barrier(communicator);
            MPI_Recv(point, lengthPoint, MPI_FLOAT, 
                    (world_rank - 4 + 24) % world_size, 0, 
                    communicator, &status);
            unpack(populationPtr, point, policyPtr, world_rank, 
                    status.MPI_SOURCE, 1);
            MPI_Recv(point, lengthPoint, MPI_FLOAT, 
                    (world_rank - 1 + 24) % world_size, 0, 
                    communicator, &status);
            unpack(populationPtr, point, policyPtr, world_rank, 
                    status.MPI_SOURCE, 2);
            MPI_Recv(point, lengthPoint, MPI_FLOAT, 
                    (world_rank + 1) % world_size, 0, 
                    communicator, &status);
            unpack(populationPtr, point, policyPtr, world_rank, 
                    status.MPI_SOURCE, 3);
        } else {
            if (world_rank % 6 == 0 || world_rank % 4 == 0) {
                package(populationPtr, point, policyPtr, world_rank, 1);
                MPI_Send(point, lengthPoint, MPI_FLOAT, 
                        (world_rank - 4 + 24) % world_size, 0, communicator);
                package(populationPtr, point, policyPtr, world_rank, 2);
                MPI_Send(point, lengthPoint, MPI_FLOAT, 
                        (world_rank + 1) % world_size, 0, communicator);
                package(populationPtr, point, policyPtr, world_rank, 3);
                MPI_Send(point, lengthPoint, MPI_FLOAT, 
                        (world_rank + 4) % world_size, 0, communicator);
                MPI_Barrier(communicator);
                MPI_Recv(point, lengthPoint, MPI_FLOAT, 
                        (world_rank - 4 + 24) % world_size, 0, 
                        communicator, &status);
                unpack(populationPtr, point, policyPtr, world_rank, 
                        status.MPI_SOURCE, 1);
                MPI_Recv(point, lengthPoint, MPI_FLOAT, 
                        (world_rank + 1) % world_size, 0, communicator,
                        &status);
                unpack(populationPtr, point, policyPtr, world_rank, 
                        status.MPI_SOURCE, 2);
                MPI_Recv(point, lengthPoint, MPI_FLOAT, 
                        (world_rank + 4) % world_size, 0, communicator, 
                        &status);
                unpack(populationPtr, point, policyPtr, world_rank, 
                        status.MPI_SOURCE, 3);
            } else {
                if (world_rank == 9 || world_rank == 10 || 
                    world_rank == 13 || world_rank == 14) {
                    package(populationPtr, point, policyPtr, world_rank, 1);
                    MPI_Send(point, lengthPoint, MPI_FLOAT, 
                            (world_rank - 4 + 24) % world_size, 0, 
                            communicator);
                    package(populationPtr, point, policyPtr, world_rank, 2);
                    MPI_Send(point, lengthPoint, MPI_FLOAT, 
                            (world_rank - 1 + 24) % world_size, 0, 
                            communicator);
                    package(populationPtr, point, policyPtr, world_rank, 3);
                    MPI_Send(point, lengthPoint, MPI_FLOAT, 
                            (world_rank + 1) % world_size, 0, communicator);
                    package(populationPtr, point, policyPtr, world_rank, 4);
                    MPI_Send(point, lengthPoint, MPI_FLOAT, 
                            (world_rank + 4) % world_size, 0, communicator);
                    MPI_Barrier(communicator);
                    MPI_Recv(point, lengthPoint, MPI_FLOAT, 
                            (world_rank - 4 + 24) % world_size, 0, 
                            communicator, &status);
                    unpack(populationPtr, point, policyPtr, world_rank, 
                            status.MPI_SOURCE, 1);
                    MPI_Recv(point, lengthPoint, MPI_FLOAT, 
                            (world_rank - 1 + 24) % world_size, 0, 
                            communicator, &status);
                    unpack(populationPtr, point, policyPtr, world_rank, 
                            status.MPI_SOURCE, 2);
                    MPI_Recv(point, lengthPoint, MPI_FLOAT, 
                            (world_rank + 1) % world_size, 0, communicator, 
                            &status);
                    unpack(populationPtr, point, policyPtr, world_rank, 
                            status.MPI_SOURCE, 3);
                    MPI_Recv(point, lengthPoint, MPI_FLOAT, 
                            (world_rank + 4) % world_size, 0, communicator, 
                            &status);
                    unpack(populationPtr, point, policyPtr, world_rank, 
                            status.MPI_SOURCE, 4);
                } else {
                    package(populationPtr, point, policyPtr, world_rank, 1);
                    MPI_Send(point, lengthPoint, MPI_FLOAT, 
                            (world_rank - 4 + 24) % world_size, 0, 
                            communicator);
                    package(populationPtr, point, policyPtr, world_rank, 2);
                    MPI_Send(point, lengthPoint, MPI_FLOAT, 
                            (world_rank - 1 + 24) % world_size, 0, 
                            communicator);
                    package(populationPtr, point, policyPtr, world_rank, 3);
                    MPI_Send(point, lengthPoint, MPI_FLOAT, 
                            (world_rank  + 4) % world_size, 0, communicator);
                    MPI_Barrier(communicator);
                    MPI_Recv(point, lengthPoint, MPI_FLOAT, 
                            (world_rank -4 + 24) % world_size, 0, 
                            communicator, &status);
                    unpack(populationPtr, point, policyPtr, world_rank, 
                            status.MPI_SOURCE, 1);
                    MPI_Recv(point, lengthPoint, MPI_FLOAT, 
                            (world_rank - 1 + 24) % world_size, 0, 
                            communicator, &status);
                    unpack(populationPtr, point, policyPtr, world_rank, 
                            status.MPI_SOURCE, 2);
                    MPI_Recv(point, lengthPoint, MPI_FLOAT, 
                            (world_rank + 4) % world_size, 0, communicator,
                            &status);
                    unpack(populationPtr, point, policyPtr, world_rank, 
                            status.MPI_SOURCE, 3);
                }
            }
        }
    }
}

void torusTopology(MPI_Comm communicator, int world_rank, PopulationPtr populationPtr, double *point, int lengthPoint, PolicyPtr policyPtr) {
    MPI_Status status;
    int world_size;
    MPI_Comm_size(communicator, &world_size);
    if (world_rank % 4 == 0){
        package(populationPtr, point, policyPtr, world_rank, 1);
        MPI_Send(point, lengthPoint, MPI_FLOAT, (world_rank - 4 + 24) % 24, 0, communicator);
        package(populationPtr, point, policyPtr, world_rank, 2);
        MPI_Send(point, lengthPoint, MPI_FLOAT, (world_rank + 1) % 24, 0, communicator);
        package(populationPtr, point, policyPtr, world_rank, 3);
        MPI_Send(point, lengthPoint, MPI_FLOAT, (world_rank + 3) % 24, 0, communicator);
        package(populationPtr, point, policyPtr, world_rank, 4);
        MPI_Send(point, lengthPoint, MPI_FLOAT, (world_rank + 4) % 24, 0, communicator);
        MPI_Barrier(communicator);
        MPI_Recv(point, lengthPoint, MPI_FLOAT, (world_rank - 4 + 24) % 24, 0, communicator, &status);
        unpack(populationPtr, point, policyPtr, world_rank, status.MPI_SOURCE, 1);
        MPI_Recv(point, lengthPoint, MPI_FLOAT, (world_rank + 1) % 24, 0, communicator, &status);
        unpack(populationPtr, point, policyPtr, world_rank, status.MPI_SOURCE, 2);
        MPI_Recv(point, lengthPoint, MPI_FLOAT, (world_rank + 3) % 24, 0, communicator, &status);
        unpack(populationPtr, point, policyPtr, world_rank, status.MPI_SOURCE, 3);
        MPI_Recv(point, lengthPoint, MPI_FLOAT, (world_rank + 4) % 24, 0, communicator, &status);
        unpack(populationPtr, point, policyPtr, world_rank, status.MPI_SOURCE, 4);
    } else {
        if (world_rank % 4 == 3){
            package(populationPtr, point, policyPtr, world_rank, 1);
            MPI_Send(point, lengthPoint, MPI_FLOAT, (world_rank - 4 + 24) % 24, 0, communicator);
            package(populationPtr, point, policyPtr, world_rank, 2);
            MPI_Send(point, lengthPoint, MPI_FLOAT, (world_rank - 3 + 24) % 24, 0, communicator);
            package(populationPtr, point, policyPtr, world_rank, 3);
            MPI_Send(point, lengthPoint, MPI_FLOAT, (world_rank - 1 + 24) % 24, 0, communicator);
            package(populationPtr, point, policyPtr, world_rank, 4);
            MPI_Send(point, lengthPoint, MPI_FLOAT, (world_rank + 4) % 24, 0, communicator);
            MPI_Barrier(communicator);
            MPI_Recv(point, lengthPoint, MPI_FLOAT, (world_rank - 4 + 24) % 24, 0, communicator, &status);
            unpack(populationPtr, point, policyPtr, world_rank, status.MPI_SOURCE, 1);
            MPI_Recv(point, lengthPoint, MPI_FLOAT, (world_rank - 3 + 24) % 24, 0, communicator, &status);
            unpack(populationPtr, point, policyPtr, world_rank, status.MPI_SOURCE, 2);
            MPI_Recv(point, lengthPoint, MPI_FLOAT, (world_rank - 1 + 24) % 24, 0, communicator, &status);
            unpack(populationPtr, point, policyPtr, world_rank, status.MPI_SOURCE, 3);
            MPI_Recv(point, lengthPoint, MPI_FLOAT, (world_rank + 4) % 24, 0, communicator, &status);
            unpack(populationPtr, point, policyPtr, world_rank, status.MPI_SOURCE, 4);
        } else{
            package(populationPtr, point, policyPtr, world_rank, 1);
            MPI_Send(point, lengthPoint, MPI_FLOAT, (world_rank - 4 + 24) % 24, 0, communicator);
            package(populationPtr, point, policyPtr, world_rank, 2);
            MPI_Send(point, lengthPoint, MPI_FLOAT, (world_rank - 1 + 24) % 24, 0, communicator);
            package(populationPtr, point, policyPtr, world_rank, 3);
            MPI_Send(point, lengthPoint, MPI_FLOAT, (world_rank + 1) % 24, 0, communicator);
            package(populationPtr, point, policyPtr, world_rank, 4);
            MPI_Send(point, lengthPoint, MPI_FLOAT, (world_rank + 4) % 24, 0, communicator);
            MPI_Barrier(communicator);
            MPI_Recv(point, lengthPoint, MPI_FLOAT, (world_rank - 4 + 24) % 24, 0, communicator, &status);
            unpack(populationPtr, point, policyPtr, world_rank, status.MPI_SOURCE, 1);
            MPI_Recv(point, lengthPoint, MPI_FLOAT, (world_rank - 1 + 24) % 24, 0, communicator, &status);
            unpack(populationPtr, point, policyPtr, world_rank, status.MPI_SOURCE, 2);
            MPI_Recv(point, lengthPoint, MPI_FLOAT, (world_rank + 1) % 24, 0, communicator, &status);
            unpack(populationPtr, point, policyPtr, world_rank, status.MPI_SOURCE, 3);
            MPI_Recv(point, lengthPoint, MPI_FLOAT, (world_rank + 4) % 24, 0, communicator, &status);
            unpack(populationPtr, point, policyPtr, world_rank, status.MPI_SOURCE, 4);
        }
    }
}

void graphTopology(MPI_Comm communicator, int world_rank, PopulationPtr populationPtr, double *point, int lengthPoint, PolicyPtr policyPtr) {
    MPI_Status status;
    int world_size;
    MPI_Comm_size(communicator, &world_size);
    int orderNode = 1;  // ayuda a ver que porcion del arreglo de fitness (ordenado) se empaquetara para enviar, segun en numberEmiImm
    for (int i = 0; i < world_size; i++) {
        if (i != world_rank) {
            package(populationPtr, point, policyPtr, world_rank, orderNode);
            MPI_Send(point, lengthPoint, MPI_FLOAT, i, 0, communicator);
            orderNode++;
        }
    }
    MPI_Barrier(communicator);
    orderNode = 1;
    for (int i = 0; i < world_size; i++) {
        if (i != world_rank) {
            MPI_Recv(point, lengthPoint, MPI_FLOAT, i, 0, communicator, &status);
            unpack(populationPtr, point, policyPtr, world_rank, status.MPI_SOURCE, orderNode);
            orderNode++;
        }
    }
}

void dinamicTopology(MPI_Comm communicator, int world_rank, PopulationPtr populationPtr, double *point, int lengthPoint, PolicyPtr policyPtr) {
    MPI_Status status;
    int world_size;
    MPI_Comm_size(communicator, &world_size);

    // Calculate ranking
    double average_;
    double standardDeviation_;

    double *data = NULL;
    allocateMemoryArrayDouble(&data, world_size);

    // GOOD = 0, MEDIUM = 1, BAD = 2 (for RAND)
    int qualification;
    int qualification1;
    int qualification2;
    
    if (world_rank == 0) {
        DictionaryPtr *averageList;
        DictionaryPtr *standardDeviationList;
        DictionaryPtr *ranking;
        
        allocateMemoryArrayDictionary(&averageList, world_size);
        allocateMemoryArrayDictionary(&standardDeviationList, world_size);
        allocateMemoryArrayDictionary(&ranking, world_size);        

        average_ = average(populationPtr);
        standardDeviation_ = standardDeviation(populationPtr);
        averageList[world_rank]->key = world_rank;
        averageList[world_rank]->value = average_;
        standardDeviationList[world_rank]->key = world_rank;
        standardDeviationList[world_rank]->value = standardDeviation_;
        
        // received avarage and standart deviation from other cores
        for (int k = 1; k < world_size; k++) {
            MPI_Recv(data, 2, MPI_DOUBLE, k, 0, communicator, &status);
            averageList[k]->key = k;
            averageList[k]->value = data[0];
            standardDeviationList[k]->key = k;
            standardDeviationList[k]->value = data[1];
        }

        insertSort(averageList, world_size);
        insertSort(standardDeviationList, world_size);

        // generate array for ranking 
        for (int k = 0; k < world_size; k++) {
            int key = averageList[k]->key;
            ranking[key]->key = key;
            ranking[key]->value += k + 1;
            key = standardDeviationList[k]->key;
            ranking[key]->key = key;
            ranking[key]->value += world_size - k;
        }
        insertSort(ranking, world_size);

        // load ranking array to data array to send
        for (int k = 0; k < world_size; k++) {
            // printf("%d %d %f\n", k, averageList[k]->key, averageList[k]->value);
            // printf("%d %d %f\n", k, standardDeviationList[k]->key, standardDeviationList[k]->value);
            // printf("%d %d %f\n", k, ranking[k]->key, ranking[k]->value);
            data[k] = ranking[k]->key;
            // printf("%f\n", data[k]);
        }
        // printf("\n");
        // re orden element for good, medium and bad usind random index on data array (ranking)
        int index_rand;
        float temp_data;
        for (int i = 0; i < world_size / 8; i++) {
            for (int j = 0; j < world_size / 3; j++) {
                temp_data = data[i * 8 + j];
                index_rand = randomInt(8) + i * 8;
                data[i * 8 + j] = data[index_rand];
                data[index_rand] = temp_data;   
            }
        }

        /* for (int k = 0; k < world_size; k++) {
            printf("%f\n", data[k]);
        }
        printf("---\n"); */

        // send data array (ranking) to other cores
        for (int i = 1; i < world_size; i++) {
            MPI_Send(data, world_size, MPI_DOUBLE, i, 0, MPI_COMM_WORLD);
        }

        // send random for RAND model (GOOD, MEDIUM and RAND) in dinamic topology
        qualification = randomInt(3);
        for (int i = 1; i < world_size; i++) {
            MPI_Send(&qualification, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
        }

        freeMemoryArrayDictionary(averageList, world_size);
        freeMemoryArrayDictionary(standardDeviationList, world_size);
        freeMemoryArrayDictionary(ranking, world_size);
    } else {
        average_ = average(populationPtr);
        standardDeviation_ = standardDeviation(populationPtr);
        data[0] = average_;
        data[1] = standardDeviation_;
        MPI_Send(data, 2, MPI_DOUBLE, 0, 0, communicator);

        // received data array (ranking)
        MPI_Recv(data, world_size, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        // received  random for RAND model in dinamic topology
        MPI_Recv(&qualification, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
    MPI_Barrier(communicator);

    // search element into data array
    int indexRank = 0;
    for (int k = 0; k < world_size; k++) {
        if (world_rank == data[k]) {
            indexRank = k;
            break;
        }
    }

    switch (policyPtr->topology) {
        case SAME:
            if (indexRank % 2 == 0) {
                package(populationPtr, point, policyPtr, world_rank, 1);
                MPI_Send(point, lengthPoint, MPI_FLOAT, data[indexRank + 1], 0, communicator);
                MPI_Barrier(communicator);
                MPI_Recv(point, lengthPoint, MPI_FLOAT, data[indexRank + 1], 0, communicator, &status);
                unpack(populationPtr, point, policyPtr, world_rank, status.MPI_SOURCE, 1);
            } else {
                package(populationPtr, point, policyPtr, world_rank, 1);
                MPI_Send(point, lengthPoint, MPI_FLOAT, data[indexRank - 1], 0, communicator);
                MPI_Barrier(communicator);
                MPI_Recv(point, lengthPoint, MPI_FLOAT, data[indexRank - 1], 0, communicator, &status);
                unpack(populationPtr, point, policyPtr, world_rank, status.MPI_SOURCE, 1);
            }
        break;
        case GOODBAD:
            if (indexRank >= 0 && indexRank < 8) {  // GOOD
                package(populationPtr, point, policyPtr, world_rank, 1);
                MPI_Send(point, lengthPoint, MPI_FLOAT, data[indexRank + 16], 0, communicator);
                MPI_Barrier(communicator);
                MPI_Recv(point, lengthPoint, MPI_FLOAT, data[indexRank + 16], 0, communicator, &status);
                unpack(populationPtr, point, policyPtr, world_rank, status.MPI_SOURCE, 1);
            } else {    // BAD
                if (indexRank >= 16 && indexRank < 24) {
                    package(populationPtr, point, policyPtr, world_rank, 1);
                    MPI_Send(point, lengthPoint, MPI_FLOAT, data[indexRank - 16], 0, communicator);
                    MPI_Barrier(communicator);
                    MPI_Recv(point, lengthPoint, MPI_FLOAT, data[indexRank - 16], 0, communicator, &status);
                    unpack(populationPtr, point, policyPtr, world_rank, status.MPI_SOURCE, 1);
                } else {    // MEDIUM
                    if (indexRank % 2 == 0) {
                        package(populationPtr, point, policyPtr, world_rank, 1);
                        MPI_Send(point, lengthPoint, MPI_FLOAT, data[indexRank + 1], 0, communicator);
                        MPI_Barrier(communicator);
                        MPI_Recv(point, lengthPoint, MPI_FLOAT, data[indexRank + 1], 0, communicator, &status);
                        unpack(populationPtr, point, policyPtr, world_rank, status.MPI_SOURCE, 1);
                    } else {
                        package(populationPtr, point, policyPtr, world_rank, 1);
                        MPI_Send(point, lengthPoint, MPI_FLOAT, data[indexRank - 1], 0, communicator);
                        MPI_Barrier(communicator);
                        MPI_Recv(point, lengthPoint, MPI_FLOAT, data[indexRank - 1], 0, communicator, &status);
                        unpack(populationPtr, point, policyPtr, world_rank, status.MPI_SOURCE, 1);
                    }
                }
            }
        break;
        case RAND:
            // GOOD = 0, MEDIUM = 1, BAD = 2
            if (qualification == 0) {
                qualification1 = 1; // MEDIUM       
                qualification2 = 2; // BAD
            } else {
                if (qualification == 1) {
                    qualification1 = 0; // GOOD
                    qualification2 = 2; // BAD
                } else {
                    qualification1 = 0; // GOOD
                    qualification2 = 1; // MEDIUM
                }
            }
            if (indexRank >= qualification1 * 8 && indexRank < (qualification1 + 1) * 8) {  // model 1
                package(populationPtr, point, policyPtr, world_rank, 1);
                MPI_Send(point, lengthPoint, MPI_FLOAT, data[indexRank + ((qualification2 - qualification1) * 8)], 0, communicator);
                MPI_Barrier(communicator);
                MPI_Recv(point, lengthPoint, MPI_FLOAT, data[indexRank + ((qualification2 - qualification1) * 8)], 0, communicator, &status);
                unpack(populationPtr, point, policyPtr, world_rank, status.MPI_SOURCE, 1);
            } else {
                if (indexRank >= qualification2 * 8 && indexRank < (qualification2 + 1) * 8) {  // model 2
                    package(populationPtr, point, policyPtr, world_rank, 1);
                    MPI_Send(point, lengthPoint, MPI_FLOAT, data[indexRank - ((qualification2 - qualification1) * 8)], 0, communicator);
                    MPI_Barrier(communicator);
                    MPI_Recv(point, lengthPoint, MPI_FLOAT, data[indexRank - ((qualification2 - qualification1) * 8)], 0, communicator, &status);
                    unpack(populationPtr, point, policyPtr, world_rank, status.MPI_SOURCE, 1);
                } else {    // model 3
                    if (indexRank % 2 == 0) {
                        package(populationPtr, point, policyPtr, world_rank, 1);
                        MPI_Send(point, lengthPoint, MPI_FLOAT, data[indexRank + 1], 0, communicator);
                        MPI_Barrier(communicator);
                        MPI_Recv(point, lengthPoint, MPI_FLOAT, data[indexRank + 1], 0, communicator, &status);
                        unpack(populationPtr, point, policyPtr, world_rank, status.MPI_SOURCE, 1);
                    } else {
                        package(populationPtr, point, policyPtr, world_rank, 1);
                        MPI_Send(point, lengthPoint, MPI_FLOAT, data[indexRank - 1], 0, communicator);
                        MPI_Barrier(communicator);
                        MPI_Recv(point, lengthPoint, MPI_FLOAT, data[indexRank - 1], 0, communicator, &status);
                        unpack(populationPtr, point, policyPtr, world_rank, status.MPI_SOURCE, 1);
                    }
                }
            }
        break;
        default:
        break;
    }
    freeMemoryArrayDouble(data);
}

void runMigration(MPI_Comm communicator, int world_rank, PopulationPtr populationPtr, double *point, int lengthPoint, PolicyPtr policyPtr, int numberGeneration) {
    if(numberGeneration % policyPtr->intervalEmiImm == 0){
        switch (policyPtr->topology) {
            case RING:
                ringTopology(communicator, world_rank, populationPtr, point, lengthPoint, policyPtr);
            break;
            case TREE:
                treeTopology(communicator, world_rank, populationPtr, point, lengthPoint, policyPtr);
            break;
            case NETA:
                netATopology(communicator, world_rank, populationPtr, point, lengthPoint, policyPtr);
            break;
            case NETB:
                netBTopology(communicator, world_rank, populationPtr, point, lengthPoint, policyPtr);
            break;
            case TORUS:
                torusTopology(communicator, world_rank, populationPtr, point, lengthPoint, policyPtr);
            break;
            case GRAPH:
                graphTopology(communicator, world_rank, populationPtr, point, lengthPoint, policyPtr);
            break;
            case SAME:
            case GOODBAD:
            case RAND:
                dinamicTopology(communicator, world_rank, populationPtr, point, lengthPoint, policyPtr);
            break;
        }
    }
}