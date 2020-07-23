/*
============================================================================
Authors:
    Edwin Alvarez-Mamani and Jose Luis Soncco-Alvarez*
    *Department of Informatics 
    Universidad Nacional de San Antonio Abad del Cusco (UNSAAC) - Perú
============================================================================
*/

#include "utils.h"

void generateSeed(int seed){
    // time_t t;
    // unsigned int seed = time(&t);
    // unsigned int seed = 1536705665 + world_rank;
    srand(seed);
    // printf("Seed: %d\n", seed);
}

int randomInt(int n){
    return rand() % n;
}

double random_(){
    return rand() / ((double) RAND_MAX);
}

void allocateMemoryArrayInt(int **array, int length){
    *array = (int*)malloc(sizeof(int) * length);
    if (*array == NULL){
        printf("No have memory.\n");
        exit(1);
    } 
    memset(*array, 0, sizeof(int) * length);
    /* for (int i = 0; i < length; i++){
        (*array)[i] = 0;
    } */
}

void freeMemoryArrayInt(int *array){
    free(array);
}

void allocateMemoryArrayDouble(double **array, int length){
    *array = (double*)malloc(sizeof(double) * length);
    if (*array == NULL){
        printf("No have memory.\n");
        exit(1);
    }
    memset(*array, 0, sizeof(double) * length);
    /* for (int i = 0; i < length; i++){
        (*array)[i] = 0;
    } */
}

void freeMemoryArrayDouble(double *array){
    if (array != NULL) {
        free(array);
    }
}

void allocateMemoryMatrixDouble(double ***matrix, int row, int column){
    *matrix = (double**)malloc(sizeof(double*) * row);
    if (*matrix == NULL){
        printf("No have memory.\n");
        exit(1);
    }
    for (int i = 0; i < row; i++){
        allocateMemoryArrayDouble(&(*matrix)[i], column);
    }
}

void freeMemoryMatrixDouble(double **matrix, int row){
    for (int i = 0; i < row; i++){
        freeMemoryArrayDouble(matrix[i]);
    }
    free(matrix);
}

void allocateMemoryReadColumn(int **array, int *column, char *fileName){
    FILE *cfPtr;
    int data;
    int k = 0;
    *array = (int*)malloc(sizeof(int) * 255);

    if ((cfPtr = fopen(fileName, "r")) == NULL) {
        printf("File could not be opened\n");
        exit(1);
    } else {
        while(fscanf(cfPtr, "%d", &data) != EOF ) {
            (*array)[k] = data;
            k++;
        }
        /* while (!feof(cfPtr)) {
            fscanf(cfPtr, "%d", &data);
            (*array)[k] = data;
            k++;
        } */
        fclose( cfPtr );
    }
    *column = k;
}

void freeMemoryReadColumn(int *array){
    free(array);
}

void allocateMemoryReadDataset_(double ***matrix, int row, int column, int *columns){
    char item_read[255];
    char *item;
    int j = 0;
    int k = 0;
    *matrix = (double**)malloc(sizeof(double*) * row);
    if (*matrix == NULL){
        printf("No have memory.\n");
        exit(1);
    }
    for (int i = 0; i < row; i++){
        (*matrix)[i] = (double*)malloc(sizeof(double) * column);
        scanf("%s", item_read);
        item = strtok(item_read, ",");
        j = 0;
        k = 0;
        while (item != NULL) {
            if(k == columns[j]){
                (*matrix)[i][j] = atof(item);
                j++;
            }
            k++;
            if(j == column){
                break;
            }
            item = strtok(NULL, ",");
        }
    }
}

void allocateMemoryReadDataset(double ***matrix, int row, int column, int *columns, char *fileName){
    FILE *cfPtr;
    char item_read[1024];
    char *item;
    int j = 0;
    int k = 0;
    // printf("Read dataset\n");
    *matrix = (double**)malloc(sizeof(double*) * row);
    if ((cfPtr = fopen(fileName, "r")) == NULL) {
        printf("File could not be opened\n");
        exit(1);
    } else {
        if (*matrix == NULL){
            printf("No have memory.\n");
            exit(1);
        }
        for (int i = 0; i < row; i++){
            (*matrix)[i] = (double*)malloc(sizeof(double) * column);
            fscanf(cfPtr, "%s", item_read);
            item = strtok(item_read, ",");
            j = 0;
            k = 0;
            while (item != NULL) {
                if(k == columns[j]){
                    (*matrix)[i][j] = atof(item);
                    // printf("%f ", (*matrix)[i][j]);
                    j++;
                }
                k++;
                if(j == column){
                    break;
                }
                item = strtok(NULL, ",");
            }
            // printf("\n");
        }
        fclose(cfPtr);
    }
}

void freeMemoryReadDataset(double **matrix, int row){
    for (int i = 0; i < row; i++){  
        freeMemoryArrayDouble(matrix[i]);  
    }     
    free(matrix);
}

void allocateMemoryReadPopulation(double ***matrix, int row, int column, char *fileName){
    FILE *cfPtr;
    char item_read[2048];
    char *item;
    int j;
    // printf("Read population\n");
    *matrix = (double**)malloc(sizeof(double*) * row);
    if ((cfPtr = fopen(fileName, "r")) == NULL) {
        printf("File could not be opened\n");
        exit(1);
    } else {
        if (*matrix == NULL){
            printf("No have memory.\n");
            exit(1);
        }
        for (int i = 0; i < row; i++){
            (*matrix)[i] = (double*)malloc(sizeof(double) * column);
            fscanf(cfPtr, "%s", item_read);
            item = strtok(item_read, ",");
            j = 0;
            while (item != NULL) {
                (*matrix)[i][j] = atof(item);
                // printf("%f ", (*matrix)[i][j]);
                item = strtok(NULL, ",");
                j++;

            }
            // printf("\n");
        }
        fclose(cfPtr);
    }
}

void freeMemoryReadPopulation(double **matrix, int row){
    for (int i = 0; i < row; i++){  
        freeMemoryArrayDouble(matrix[i]);  
    }     
    free(matrix);
}

void allocateMemoryDictionary(DictionaryPtr *dictionaryPtr, int key){
    *dictionaryPtr =  (Dictionary*)malloc(sizeof(Dictionary));
    if (*dictionaryPtr == NULL){
        printf("No have memory.\n");
        exit(1);
    }
    
    (*dictionaryPtr)->key = key;
    (*dictionaryPtr)->value = 0;
}

void freeMemoryDictionary(DictionaryPtr dictionaryPtr){
    free(dictionaryPtr);
}

void allocateMemoryArrayDictionary(DictionaryPtr **dictionaryPtr, int lengthDictionary){
    *dictionaryPtr = (DictionaryPtr*)malloc(sizeof(Dictionary) * lengthDictionary);
    if (*dictionaryPtr == NULL){
        printf("No have memory.\n");
        exit(1);
    }
    for (int i = 0; i < lengthDictionary; i++){
        allocateMemoryDictionary(&(*dictionaryPtr)[i], i);
    }
}

void freeMemoryArrayDictionary(DictionaryPtr *dictionaryPtr, int lengthDictionary){
    for (int i = 0; i < lengthDictionary; i++){
        freeMemoryDictionary(dictionaryPtr[i]);
    }
    free(dictionaryPtr);
}

void readPolicy(PolicyPtr policyPtr, char *fileName){
    FILE *cfPtr;
    char item_read[255];
    char *item;

    if ((cfPtr = fopen(fileName, "r")) == NULL) {
        printf("File could not be opened\n");
        exit(1);
    } else {
        fscanf(cfPtr, "%s", item_read);
        item = strtok(item_read, ":");
        item = strtok(NULL, ":");
        if(strcmp(item, "RING") == 0){
            policyPtr->topology = RING;
        }else{
            if(strcmp(item, "TREE") == 0){
                policyPtr->topology = TREE;
            }else{
                if(strcmp(item, "NETA") == 0){
                    policyPtr->topology = NETA;
                } else{
                    if(strcmp(item, "NETB") == 0){
                        policyPtr->topology = NETB;
                    } else{
                        if(strcmp(item, "TORUS") == 0){
                            policyPtr->topology = TORUS;
                        } else {
                            if(strcmp(item, "GRAPH") == 0){
                                policyPtr->topology = GRAPH;
                            } else {
                                if(strcmp(item, "SAME") == 0){
                                    policyPtr->topology = SAME;
                                } else {
                                    if(strcmp(item, "GOODBAD") == 0){
                                        policyPtr->topology = GOODBAD;
                                    } else {
                                        if(strcmp(item, "RAND") == 0){
                                            policyPtr->topology = RAND;
                                        } else {
                                            printf("Topology could not found\n");
                                            exit(1);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        fscanf(cfPtr, "%s", item_read);
        item = strtok(item_read, ":");
        item = strtok(NULL, ":");
        if(strcmp(item, "REMOVE") == 0){
            policyPtr->emigration = REMOVE;
        }else{
            policyPtr->emigration = CLONE;
        }

        fscanf(cfPtr, "%s", item_read);
        item = strtok(item_read, ":");
        item = strtok(NULL, ":");
        if(strcmp(item, "BEST") == 0){
            policyPtr->choiceEmi = BEST;
        }else{
            if(strcmp(item, "WORST") == 0){
                policyPtr->choiceEmi = WORST;
            }else{
                policyPtr->choiceEmi = RANDOM;
            }
        }

        fscanf(cfPtr, "%s", item_read);
        item = strtok(item_read, ":");
        item = strtok(NULL, ":");
        if(strcmp(item, "BEST") == 0){
            policyPtr->choiceImm = BEST;
        }else{
            if(strcmp(item, "WORST") == 0){
                policyPtr->choiceImm = WORST;
            }else{
                policyPtr->choiceImm = RANDOM;
            }
        }

        fscanf(cfPtr, "%s", item_read);
        item = strtok(item_read, ":");
        item = strtok(NULL, ":");
        policyPtr->numberEmiImm = atoi(item);

        fscanf(cfPtr, "%s", item_read);
        item = strtok(item_read, ":");
        item = strtok(NULL, ":");
        policyPtr->intervalEmiImm = atoi(item);

        fclose(cfPtr);
    }
}

void showArrayDoubleSend(PopulationPtr populationPtr, PolicyPtr policyPtr, double *array, int source) {
    printf("Process %d send:\n", source);
    for (int k = 0; k < policyPtr->numberEmiImm; k++){
        printf("%d: [", k);
        for(int i = 0; i < populationPtr->numClusters; i++){
            printf("(");
            for(int j = 0; j < populationPtr->pointDimension; j++){
                printf("%f, ", array[(k * populationPtr->numClusters + i) * populationPtr->pointDimension + j]);
            }
            printf("), ");
        }
        printf("]\n");
    }
}

void showArrayDoubleReceived(PopulationPtr populationPtr, PolicyPtr policyPtr, double *array, int destination, int source, int orderNode) {
    printf("Process %d received from process %d:\n", destination, source);
    for (int k = 0; k < policyPtr->numberEmiImm; k++) {
        printf("%d: [", (orderNode - 1) * policyPtr->numberEmiImm + k);
        for(int i = 0; i < populationPtr->numClusters; i++){
            printf("(");
            for(int j = 0; j < populationPtr->pointDimension; j++){
                printf("%f, ", array[(k * populationPtr->numClusters + i) * populationPtr->pointDimension + j]);
            }
            printf("), ");
        }
        printf("]\n");
    }
}

void showPolicyMigration(PolicyPtr policyPtr) {
    char topology[7][10] = {"RING", "TREE", "NETA", "NETB", "TORUS", "GRAPH", "DINAMIC"};
    char emigration[2][10] = {"CLONE", "REMOVE"};
    char choiceEmiImm[3][10] = {"BEST", "WORST", "RANDOM"};
    printf("Topology:       \t%s\n", topology[policyPtr->topology]);
    printf("Emigration:     \t%s\n", emigration[policyPtr->emigration]);
    printf("Choice Em:      \t%s\n", choiceEmiImm[policyPtr->choiceEmi]);
    printf("Choice Im:      \t%s\n", choiceEmiImm[policyPtr->choiceImm]);
    printf("Number Em/Im:   \t%d\n", policyPtr->numberEmiImm);
    printf("Interval Em/Im: \t%d\n\n", policyPtr->intervalEmiImm);
}

void insertSort(DictionaryPtr *dictionaryPtr, int lengthDictionary) {
    int index;
    int key;
    double value;
    for (int i = 1; i < lengthDictionary; i++) {
        key = dictionaryPtr[i]->key;
        value = dictionaryPtr[i]->value;
        index = i - 1;
        while (index >= 0 && dictionaryPtr[index]->value > value) {
            dictionaryPtr[index + 1]->key = dictionaryPtr[index]->key;
            dictionaryPtr[index + 1]->value = dictionaryPtr[index]->value;
            index--;
        }
        dictionaryPtr[index + 1]->key = key;
        dictionaryPtr[index + 1]->value = value;
    }
}

void bubbleSort(PopulationPtr populationPtr) {
    DictionaryPtr temp;
    for (int i = 1; i < populationPtr->lengthSpider; i++){
        for (int j = 0; j < populationPtr->lengthSpider - i; j++) {
            if (populationPtr->fitness[j]->value > populationPtr->fitness[j + 1]->value) {
                temp = populationPtr->fitness[j];
                populationPtr->fitness[j] = populationPtr->fitness[j + 1];
                populationPtr->fitness[j + 1] = temp;
            }
        }
    }
}

double average(PopulationPtr populationPtr) {
    double sum = 0;
    double value = 0;
    for (int i = 0; i < populationPtr->lengthSpider; i++) {
        value = populationPtr->fitness[i]->value;
        sum += value;
    }
    return sum / populationPtr->lengthSpider;
}

double standardDeviation(PopulationPtr populationPtr) {
    double sum = 0;
    double value = 0;
    double average_ = average(populationPtr);
    for (int i = 0; i < populationPtr->lengthSpider; i++) {
        value = populationPtr->fitness[i]->value;
        sum += pow(value - average_, 2);
    }
    return sqrt(sum / populationPtr->lengthSpider);
}