/*
============================================================================
Authors:
    Edwin Alvarez-Mamani and Jose Luis Soncco-Alvarez*
    *Department of Informatics 
    Universidad Nacional de San Antonio Abad del Cusco (UNSAAC) - Perú
============================================================================
*/

#include "population.h"

void freeMemoryPopulation(PopulationPtr populationPtr, AuxPopulationPtr auxPopulationPtr, AuxSpiderPtr auxSpiderPtr){
    freeMemoryArraySpider(populationPtr->spiders, populationPtr->lengthSpider);
    freeMemoryArraySpider(populationPtr->offspring, populationPtr->numberMales);
    freeMemoryArrayDictionary(populationPtr->fitness, populationPtr->lengthSpider);
    freeMemoryArrayInt(populationPtr->indexMigration);
    freeMemoryAuxilarPopulation(populationPtr, auxPopulationPtr);
    freeMemoryAuxilarSpider(populationPtr, auxSpiderPtr);
}

/* Methods */
double maximumDistance(double **dataset, int row, int column){
    double maximumDistance = 0;
    double distance = 0;
    for(int i = 0; i < row - 1; i++){
        for(int j = i + 1; j < row; j++){
            distance = calculateDistanceCC_(i, j, dataset, row, column);
            if (distance > maximumDistance){
                maximumDistance = distance;
            }
        }
    }
    return maximumDistance;
}

/** Generate initial population: males and females, and calculate radius **/
void generateInitialPopulation(PopulationPtr populationPtr, int populationSize, int numberClusters, double **dataset, int row, int column, 
    int numberMigration, AuxPopulationPtr auxPopulationPtr, AuxSpiderPtr auxSpiderPtr){
    populationPtr->numberFemales = floor((0.9 - random_() * 0.25) * populationSize);
    populationPtr->numberMales = populationSize - populationPtr->numberFemales;
    populationPtr->numClusters = numberClusters;
    populationPtr->pointDimension = column;
    populationPtr->radiusMating = 0;
    populationPtr->lengthSpider = populationSize;
    populationPtr->lengthOffspring = populationPtr->numberMales;    // 0;
    populationPtr->medianWeight = 0;
    populationPtr->indexBest = 0;
    populationPtr->indexWorst = 0;
    populationPtr->countFitness = 0;
    int pos = -1;   // invalid position
    double d = 0;

    // allocate memory for dictionary fitness
    allocateMemoryArrayDictionary(&populationPtr->fitness, populationSize);

    // allocate memory for indexMigration
    allocateMemoryArrayInt(&populationPtr->indexMigration, numberMigration);

    // allocate memory for offspring
    allocateMemoryArraySpider(&populationPtr->offspring, populationPtr->numberMales, 0, populationPtr->numClusters,
        populationPtr->pointDimension, dataset, row, column);

    // allocate memory for spider
    allocateMemoryArraySpider(&populationPtr->spiders, populationPtr->lengthSpider, 0, populationPtr->numClusters,
        populationPtr->pointDimension, dataset, row, column);

    // generate FEMALES by choosing points randomly from dataset
    for(int i = 0; i < populationPtr->numberFemales; i++){
        populationPtr->spiders[i]->type = 0;
        for(int j = 0; j < populationPtr->numClusters; j++){
            // random_ integer in range [0 , dataset.length - 1]
            pos = randomInt(row);
            for(int k = 0; k < populationPtr->pointDimension; k++){
                populationPtr->spiders[i]->centers[j]->point[k] = dataset[pos][k];
                // printf("%f ", populationPtr->spiders[i]->centers[j]->point[k]);
            }
        }
        // printf("\n");
    }

    // generate MALES by choosing points randomly from dataset
    for(int i = populationPtr->numberFemales; i < populationPtr->lengthSpider; i++){
        populationPtr->spiders[i]->type = 1;
        for(int j = 0; j < populationPtr->numClusters; j++){
            // random_ integer in range [0 , dataset.length - 1]
            pos = randomInt(row);
            for(int k = 0; k < populationPtr->pointDimension; k++){
                populationPtr->spiders[i]->centers[j]->point[k] = dataset[pos][k];
                // printf("%f ", populationPtr->spiders[i]->centers[j]->point[k]);
            }
        }
        // printf("\n");
    }
    
    // calculate the radius of mating
    d = maximumDistance(dataset, row, column);
    populationPtr->radiusMating = d / 2;

    // allocate memory for auxSpiderPtr var
    allocateMemoryArrayDouble(&auxSpiderPtr->distances, populationPtr->numClusters);
    allocateMemoryArrayInt(&auxSpiderPtr->numPointsForCluster, populationPtr->numClusters);
    allocateMemoryMatrixDouble(&auxSpiderPtr->sum, populationPtr->numClusters, populationPtr->pointDimension);

    // allocate memory for auxPopulationPtr var
    allocateMemoryArrayDouble(&auxPopulationPtr->males, populationPtr->numberMales);
    allocateMemoryArrayClusterCenter(&auxPopulationPtr->spidersWeightsPtr, populationPtr->numClusters, populationPtr->pointDimension);
    allocateMemoryArrayInt(&auxPopulationPtr->matingGroup, populationPtr->numberFemales + 1);           // before numberMales
    allocateMemoryArrayDouble(&auxPopulationPtr->matingRoulette, populationPtr->numberFemales + 1);     // before numberMales
    allocateMemorySpider(&auxPopulationPtr->spiderWeightedMeanPtr, 1, populationPtr->numClusters, populationPtr->pointDimension, dataset, row, column);
    allocateMemoryArrayClusterCenter(&auxPopulationPtr->clusCentersPtr, populationPtr->numClusters, populationPtr->pointDimension);
    allocateMemoryArrayDouble(&auxPopulationPtr->replacementRoulette, populationPtr->lengthSpider);
}

void readInitialPopulation(PopulationPtr populationPtr, int populationSize, int numberClusters, double **dataset, int row, int column, 
    int numberMigration, AuxPopulationPtr auxPopulationPtr, AuxSpiderPtr auxSpiderPtr, double **population, int initialIndexPopulation, int limitCountFitness){
    populationPtr->numberFemales = floor((0.9 - random_() * 0.25) * populationSize);
    populationPtr->numberMales = populationSize - populationPtr->numberFemales;
    populationPtr->numClusters = numberClusters;
    populationPtr->pointDimension = column;
    populationPtr->radiusMating = 0;
    populationPtr->lengthSpider = populationSize;
    populationPtr->lengthOffspring = populationPtr->numberMales;    // 0;
    populationPtr->medianWeight = 0;
    populationPtr->indexBest = 0;
    populationPtr->indexWorst = 0;
    populationPtr->countFitness = 0;
    populationPtr->limitCountFitness = limitCountFitness;
    /// int pos = -1;   // invalid position
    double d = 0;

    // allocate memory for dictionary fitness
    allocateMemoryArrayDictionary(&populationPtr->fitness, populationSize);

    // allocate memory for indexMigration
    allocateMemoryArrayInt(&populationPtr->indexMigration, numberMigration);

    // allocate memory for offspring
    allocateMemoryArraySpider(&populationPtr->offspring, populationPtr->numberMales, 0, populationPtr->numClusters,
        populationPtr->pointDimension, dataset, row, column);

    // allocate memory for spider
    allocateMemoryArraySpider(&populationPtr->spiders, populationPtr->lengthSpider, 0, populationPtr->numClusters,
        populationPtr->pointDimension, dataset, row, column);

    // generate FEMALES by choosing points randomly from dataset
    for(int i = 0; i < populationPtr->numberFemales; i++){
        populationPtr->spiders[i]->type = 0;
        for(int j = 0; j < populationPtr->numClusters; j++){
            // random_ integer in range [0 , dataset.length - 1]
            /// pos = randomInt(row);
            for(int k = 0; k < populationPtr->pointDimension; k++){
                /// populationPtr->spiders[i]->centers[j]->point[k] = dataset[pos][k];
                populationPtr->spiders[i]->centers[j]->point[k] = population[i + initialIndexPopulation][j * populationPtr->pointDimension + k];
                // printf("%f ", populationPtr->spiders[i]->centers[j]->point[k]);
            }
        }
        // printf("\n");
    }

    // generate MALES by choosing points randomly from dataset
    for(int i = populationPtr->numberFemales; i < populationPtr->lengthSpider; i++){
        populationPtr->spiders[i]->type = 1;
        for(int j = 0; j < populationPtr->numClusters; j++){
            // random_ integer in range [0 , dataset.length - 1]
            /// pos = randomInt(row);
            for(int k = 0; k < populationPtr->pointDimension; k++){
                /// populationPtr->spiders[i]->centers[j]->point[k] = dataset[pos][k];
                populationPtr->spiders[i]->centers[j]->point[k] = population[i + initialIndexPopulation][j * populationPtr->pointDimension + k];
                // printf("%f ", populationPtr->spiders[i]->centers[j]->point[k]);
            }
        }
        // printf("\n");
    }
    
    // calculate the radius of mating
    d = maximumDistance(dataset, row, column);
    populationPtr->radiusMating = d / 2;

    // allocate memory for auxSpiderPtr var
    allocateMemoryArrayDouble(&auxSpiderPtr->distances, populationPtr->numClusters);
    allocateMemoryArrayInt(&auxSpiderPtr->numPointsForCluster, populationPtr->numClusters);
    allocateMemoryMatrixDouble(&auxSpiderPtr->sum, populationPtr->numClusters, populationPtr->pointDimension);

    // allocate memory for auxPopulationPtr var
    allocateMemoryArrayDouble(&auxPopulationPtr->males, populationPtr->numberMales);
    allocateMemoryArrayClusterCenter(&auxPopulationPtr->spidersWeightsPtr, populationPtr->numClusters, populationPtr->pointDimension);
    allocateMemoryArrayInt(&auxPopulationPtr->matingGroup, populationPtr->numberFemales + 1);           // before numberMales
    allocateMemoryArrayDouble(&auxPopulationPtr->matingRoulette, populationPtr->numberFemales + 1);     // before numberMales
    allocateMemorySpider(&auxPopulationPtr->spiderWeightedMeanPtr, 1, populationPtr->numClusters, populationPtr->pointDimension, dataset, row, column);
    allocateMemoryArrayClusterCenter(&auxPopulationPtr->clusCentersPtr, populationPtr->numClusters, populationPtr->pointDimension);
    allocateMemoryArrayDouble(&auxPopulationPtr->replacementRoulette, populationPtr->lengthSpider);
}

void generatePopulation(int populationSize, int numberClusters, double **dataset, int row, int column){
    // int numberFemales;
    // int numberMales = populationSize - numberFemales;
    int numClusters = numberClusters;
    int pointDimension = column;
    int lengthSpider = populationSize;

    int pos = 0;

    /* char fileName[256];
    sprintf(fileName, "%s", fileNameOut);
    FILE *fp = fopen(fileName, "w"); */
    for(int i = 0; i < lengthSpider; i++){
        for(int j = 0; j < numClusters; j++){
            // random_ integer in range [0 , dataset.length - 1]
            pos = randomInt(row);
            //printf("%d %d\n", row, pos);
            for(int k = 0; k < pointDimension; k++){
                if (j * k == (numClusters - 1) * (pointDimension - 1)) {
                    // fprintf(fp, "%f", dataset[pos][k]);
                    printf("%f", dataset[pos][k]);
                } else {
                    // fprintf(fp, "%f,", dataset[pos][k]);
                    printf("%f,", dataset[pos][k]);
                }
            }
        }
        // fprintf(fp, "%s", "\n");
        printf("\n");
    }

    // generate population for experiments
    /* for (int x = 0; x < 24; x++) {
        numberFemales = floor((0.9 - random_() * 0.25) * populationSize);
        // generate FEMALES by choosing points randomly from dataset
        for(int i = 0; i < numberFemales; i++){
            for(int j = 0; j < numClusters; j++){
                // random_ integer in range [0 , dataset.length - 1]
                pos = randomInt(row);
                for(int k = 0; k < pointDimension; k++){
                    // populationPtr->spiders[i]->centers[j]->point[k] = dataset[pos][k];
                    if (j * k == (numClusters - 1) * (pointDimension - 1)) {
                        fprintf(fp, "%f", dataset[pos][k]);
                    } else {
                        fprintf(fp, "%f,", dataset[pos][k]);
                    }
                }
            }
            fprintf(fp, "%s", "\n");
        }

        // generate MALES by choosing points randomly from dataset
        for(int i = numberFemales; i < lengthSpider; i++){
            // populationPtr->spiders[i]->type = 1;
            for(int j = 0; j < numClusters; j++){
                // random_ integer in range [0 , dataset.length - 1]
                pos = randomInt(row);
                for(int k = 0; k < pointDimension; k++){
                    // populationPtr->spiders[i]->centers[j]->point[k] = dataset[pos][k];
                    if (j * k == (numClusters - 1) * (pointDimension - 1)) {
                        fprintf(fp, "%f", dataset[pos][k]);
                    } else {
                        fprintf(fp, "%f,", dataset[pos][k]);
                    }
                }
            }
            fprintf(fp, "%s", "\n");
        }
    } */
    // fclose(fp);
}

void evaluateFitnessPopulation(PopulationPtr populationPtr, double **dataset, int row, int column, AuxSpiderPtr auxSpiderPtr){
    for(int i = 0; i < populationPtr->lengthSpider; i++){
        // keeping the best spider the same
        if (i == populationPtr->indexBest){
            continue;
        }
        evaluateFitness(populationPtr, populationPtr->spiders[i], dataset, row, column, auxSpiderPtr);
    }
}

void calculateBestWorstPopulation(PopulationPtr populationPtr){
    double minFitness = populationPtr->spiders[0]->fitness;
    double maxFitness = populationPtr->spiders[0]->fitness;

    for(int i = 0; i < populationPtr->lengthSpider; i++){
        populationPtr->fitness[i]->key = i;
        populationPtr->fitness[i]->value = populationPtr->spiders[i]->fitness;

        if (populationPtr->spiders[i]->fitness < minFitness){
            minFitness = populationPtr->spiders[i]->fitness;
            populationPtr->indexBest = i;
        }
        
        if (populationPtr->spiders[i]->fitness > maxFitness){
            maxFitness = populationPtr->spiders[i]->fitness;
            populationPtr->indexWorst = i;
        }
    }
    
    // Insert sort by fitness
    insertSort(populationPtr->fitness, populationPtr->lengthSpider);
}

/** Calculate the weight of every spider in the population **/
void calculateWeightPopulation(PopulationPtr populationPtr, double **dataset, int row, int column, AuxSpiderPtr auxSpiderPtr){
    // Evaluate the fitness of the population
    evaluateFitnessPopulation(populationPtr, dataset, row, column, auxSpiderPtr);
    // Calculate the best and the worst individual of pop.
    calculateBestWorstPopulation(populationPtr);
    // Calculate weight of population
    double w = 0;
    for(int i = 0; i < populationPtr->lengthSpider; i++){
        w = (populationPtr->spiders[populationPtr->indexWorst]->fitness - populationPtr->spiders[i]->fitness) 
        / (populationPtr->spiders[populationPtr->indexWorst]->fitness - populationPtr->spiders[populationPtr->indexBest]->fitness);
        
        populationPtr->spiders[i]->weight = w;
    }
}

/** Return the index of the nearest individual with higher weight compared to individual with index i **/
int nearestWithHigherWeightTo(PopulationPtr populationPtr, int i){
    int index = 0;
    double nearestDistance = calculateDistanceS(populationPtr->spiders[index], populationPtr->spiders[i]);
    
    for(int k = 0; k < populationPtr->lengthSpider; k++){
        if (populationPtr->spiders[k]->weight > populationPtr->spiders[i]->weight){
            double newDistance = calculateDistanceS(populationPtr->spiders[k], populationPtr->spiders[i]);
            if (newDistance < nearestDistance){
                nearestDistance = newDistance;
                index = k;
            }
        }
    }
    return index;
}

/** Apply the female cooperative operator **/
void femaleCooperativeOperator(PopulationPtr populationPtr, AuxPopulationPtr auxPopulationPtr){
    double thresholdPF = 0.5;   // Test with other values
    double w = 0, d = 0, d2 = 0;
    double vibci = 0;
    double vibbi = 0;
    double rm = 0, alpha = 0, beta = 0, delta = 0, rand = 0;
    int index = 0;
    double cons = 0, signal = 0;
    
    for(int i = 0; i < populationPtr->numberFemales; i++){
        // keeping the best spider the same
        if (i == populationPtr->indexBest){
            continue;
        }
        // Calculate Vibci: Vib. of ind. nearest with higher weight compared to i
        index = nearestWithHigherWeightTo(populationPtr, i);
        w = populationPtr->spiders[index]->weight;
        d = calculateDistanceS(populationPtr->spiders[i], populationPtr->spiders[index]);
        d2 = pow(d, 2);
        vibci = w / pow(M_E, d2);
        
        // Calculate Vibbi: vibration of individual with best fitness
        w = populationPtr->spiders[populationPtr->indexBest]->weight; 
        d = calculateDistanceS(populationPtr->spiders[i], populationPtr->spiders[populationPtr->indexBest]);
        d2 = pow(d, 2);
        vibbi = w / pow(M_E, d2);
        
        rm = random_();
        alpha = random_();
        beta = random_();
        delta = random_();
        rand = random_();

        // Define if the movement is: attraction or repulsion
        if (rm < thresholdPF){
            signal = 1;     // --> 1=sum
        }
        else{
            signal = -1;    // --> -1=subtraction
        }

        // Sum expression with alpha
        diffSpiders(populationPtr->spiders[index], populationPtr->spiders[i], auxPopulationPtr->clusCentersPtr, populationPtr->numClusters);
        cons = alpha * vibci;
        mulClusterCentersByConstant(auxPopulationPtr->clusCentersPtr, populationPtr->numClusters, cons);
        sumSpider(populationPtr->spiders[i], auxPopulationPtr->clusCentersPtr, populationPtr->numClusters, signal);
        
        // Sum expression with beta
        diffSpiders(populationPtr->spiders[populationPtr->indexBest], populationPtr->spiders[i], auxPopulationPtr->clusCentersPtr, populationPtr->numClusters);
        cons = beta * vibbi;
        mulClusterCentersByConstant(auxPopulationPtr->clusCentersPtr, populationPtr->numClusters, cons);
        sumSpider(populationPtr->spiders[i], auxPopulationPtr->clusCentersPtr, populationPtr->numClusters, signal); 

        // Sum expression with delta
        for(int j = 0; j < populationPtr->numClusters; j++){
            for(int k = 0; k < populationPtr->pointDimension; k++){
                auxPopulationPtr->clusCentersPtr[j]->point[k] = delta * (rand - 0.5);
            }
        }
        sumSpider(populationPtr->spiders[i], auxPopulationPtr->clusCentersPtr, populationPtr->numClusters, signal);
    }
}

/* calculate median weight of males using variant of quicksort */
void calculateMedianWeightOfMales(PopulationPtr populationPtr, AuxPopulationPtr auxPopulationPtr){
    int k = 0;
    int medianPos = 0;
    int begin, end, p, r, i = 0;
    double pivot = 0;
    double tmp = 0;

    // Copy the weight of males into males array
    for(int i = populationPtr->numberFemales; i < populationPtr->lengthSpider; i++){
        auxPopulationPtr->males[k] = populationPtr->spiders[i]->weight;
        k++;
    }
    // Calculate the median position
    medianPos = (0 + populationPtr->numberMales - 1) / 2;
    // Calculate the median value   
    begin = 0;
    end = populationPtr->numberMales - 1;
    
    while(TRUE){
        p = begin;
        r = end;
        pivot = auxPopulationPtr->males[r];
        i = p - 1;
        for(int j = p; j < r; j++){
            if (auxPopulationPtr->males[j] < pivot){
                i++;
                // swap males[i] and males[j]
                tmp = auxPopulationPtr->males[i];
                auxPopulationPtr->males[i] = auxPopulationPtr->males[j];
                auxPopulationPtr->males[j] = tmp;
            }
        }
        // swap males[i+1] and males[r]
        tmp = auxPopulationPtr->males[i + 1];
        auxPopulationPtr->males[i + 1] = auxPopulationPtr->males[r];
        auxPopulationPtr->males[r] = tmp;
        
        if (i + 1 == medianPos){
            break;
        }
        else{
            if (medianPos > i + 1){
                // search right
                begin = i + 2;
            }
            else{
                // search left
                end = i;
            }           
        }
    }
    populationPtr->medianWeight = auxPopulationPtr->males[medianPos];
}

int nearestFemaleTo(PopulationPtr populationPtr, int i){
    int index = 0;
    double nearestDistance = calculateDistanceS(populationPtr->spiders[index], populationPtr->spiders[i]);
    double newDistance = 0;
    for(int k = 0; k < populationPtr->numberFemales; k++){  // females
        newDistance = calculateDistanceS(populationPtr->spiders[k], populationPtr->spiders[i]);
        if (newDistance < nearestDistance){
            nearestDistance = newDistance;
            index = k;
        }
    }
    return index;
}

void calculateMaleSpiderWeightedMean(PopulationPtr populationPtr, SpiderPtr spi, AuxPopulationPtr auxPopulationPtr){
    // calculate total weight of males
    double totalWeight = 0;
    for(int i = populationPtr->numberFemales; i < populationPtr->lengthSpider; i++){
        totalWeight += populationPtr->spiders[i]->weight;
    }
    
    // calculate spiders multiplied by their weights
    for(int i = 0; i < populationPtr->numClusters; i++){
        for(int j = 0; j < populationPtr->pointDimension; j++){
            auxPopulationPtr->spidersWeightsPtr[i]->point[j] = 0;
        }
    }

    for(int i = populationPtr->numberFemales; i < populationPtr->lengthSpider; i++){
        for(int j = 0; j < populationPtr->numClusters; j++){
            for(int k = 0; k < populationPtr->pointDimension; k++){
                auxPopulationPtr->spidersWeightsPtr[j]->point[k] += populationPtr->spiders[i]->centers[j]->point[k] * populationPtr->spiders[i]->weight;
            }
        }
    }
    
    // calculate the weighted mean
    for(int j = 0; j < populationPtr->numClusters; j++){
        for(int k = 0; k < populationPtr->pointDimension; k++){
            spi->centers[j]->point[k] = auxPopulationPtr->spidersWeightsPtr[j]->point[k] / totalWeight;
        }
    }
}

/** Create Mating Roulette for a male spider **/
void createMatingRoulette(PopulationPtr populationPtr, double *matingRoulette, int lengthMatingRoulette, int  *matingGroup, int lengthMatingGroup){
    // Sum fitness of mating spiders
    double total =  0;
    for(int i = 0; i < lengthMatingGroup; i++){
        total += populationPtr->spiders[matingGroup[i]]->fitness;
    }
    // Calculate values of the roulette
    matingRoulette[0] = populationPtr->spiders[matingGroup[0]]->fitness / total;
    for(int i = 1; i < lengthMatingGroup; i++){
        matingRoulette[i] = matingRoulette[i - 1] + populationPtr->spiders[matingGroup[i]]->fitness / total;
    }
}

/** Apply the mating operator **/
void matingOperator(PopulationPtr populationPtr, double **dataset, int row, int column, AuxPopulationPtr auxPopulationPtr, AuxSpiderPtr auxSpiderPtr){
    int indexOffspring = 0;
    int indexGroup = 0;
    double rand = -1;
    double distance = 0;

    // Begin mating
    for(int i = populationPtr->numberFemales; i < populationPtr->lengthSpider; i++){    // males
        if (populationPtr->spiders[i]->weight > populationPtr->medianWeight){   // male is dominant 
            indexGroup = 0;
            // Calculate females in the radius of male "i"
            auxPopulationPtr->matingGroup[indexGroup] = i;  // add male index as first element
            indexGroup++;
            for(int j = 0; j < populationPtr->numberFemales; j++){  // females
                distance = calculateDistanceS(populationPtr->spiders[i], populationPtr->spiders[j]);
                if (distance < populationPtr->radiusMating){
                    auxPopulationPtr->matingGroup[indexGroup] = j;  // add female index
                    indexGroup++;
                }
            }
            if (indexGroup > 1){    // do mating
                // Create mating roulette
                createMatingRoulette(populationPtr, auxPopulationPtr->matingRoulette, indexGroup, auxPopulationPtr->matingGroup, indexGroup);
                // Create the new spider using mating roulette
                for(int j = 0; j < populationPtr->numClusters; j++){
                    rand = random_();   // 0.0 <= rand < 1.0
                    // Go through the mating roulette
                    for(int k = 0; k < indexGroup; k++){
                        if (rand < auxPopulationPtr->matingRoulette[k]){
                            // Copy cluster "j"
                            for(int h = 0; h < populationPtr->pointDimension; h++){
                                populationPtr->offspring[indexOffspring]->centers[j]->point[h] = 
                                populationPtr->spiders[auxPopulationPtr->matingGroup[k]]->centers[j]->point[h];
                            }
                            break;
                        }
                    }
                }
                // Calculate fitness of new spider and put into offspring
                evaluateFitness(populationPtr, populationPtr->offspring[indexOffspring], dataset, row, column, auxSpiderPtr);
                indexOffspring++;
                populationPtr->lengthOffspring = indexOffspring;
            }
        }
    }   // end-mating
}

// using a factor
void createReplacementRoulette(PopulationPtr populationPtr, double *replacementRoulette, int length){
    // Sum fitness of all spiders
    double factor = 1;  
    double total = 0;
    for(int i = 0; i < populationPtr->lengthSpider; i++){
        if (populationPtr->spiders[i]->weight > populationPtr->medianWeight){
            total += populationPtr->spiders[i]->fitness;
        }
        else{
            total += populationPtr->spiders[i]->fitness * factor;
        }
    }
    
    // calculate values of the roulette
    replacementRoulette[0] = populationPtr->spiders[0]->fitness / total;
    for(int i = 1; i < populationPtr->lengthSpider; i++){
        if (populationPtr->spiders[i]->weight > populationPtr->medianWeight){
            replacementRoulette[i] = replacementRoulette[i - 1] + populationPtr->spiders[i]->fitness / total;
        }
        else{
            replacementRoulette[i] = replacementRoulette[i - 1] + (populationPtr->spiders[i]->fitness * factor) / total;
        }
    }
}

/** Apply the male cooperative operator **/
void maleCooperativeOperator(PopulationPtr populationPtr, double **dataset, int row, int column, AuxPopulationPtr auxPopulationPtr){
    double w = 0, d = 0, d2 = 0;
    double vibfi = 0;
    double alpha = 0, delta = 0, rand = 0, cons = 0;
    int index = 0;

    // Calculate the median weight of male population
    calculateMedianWeightOfMales(populationPtr, auxPopulationPtr); 
    // Calculate the male spider with weighted mean
    for(int i = 0; i < populationPtr->numClusters; i++){
        for(int j = 0; j < populationPtr->pointDimension; j++){
            auxPopulationPtr->clusCentersPtr[i]->point[j] = 0;
        }
    }
    
    calculateMaleSpiderWeightedMean(populationPtr, auxPopulationPtr->spiderWeightedMeanPtr, auxPopulationPtr);
    
    for(int i = populationPtr->numberFemales; i < populationPtr->lengthSpider; i++){    // males
        // keeping the best spider the same
        if (i == populationPtr->indexBest){
            continue;
        }
        
        // calculate vibfi: vibration of nearest female
        index = nearestFemaleTo(populationPtr, i);
        w = populationPtr->spiders[index]->weight;
        d = calculateDistanceS(populationPtr->spiders[i], populationPtr->spiders[index]);
        d2 = pow(d, 2);
        vibfi = w / pow(M_E, d2);
        
        // Define if movement is attraction to females or to the mean
        alpha = random_();
        delta = random_();
        rand = random_();
        if (populationPtr->spiders[i]->weight > populationPtr->medianWeight){   // male is dominant(D)
            // Sum expression with alpha
            diffSpiders(populationPtr->spiders[index], populationPtr->spiders[i], auxPopulationPtr->clusCentersPtr, populationPtr->numClusters);
            cons = alpha * vibfi;
            mulClusterCentersByConstant(auxPopulationPtr->clusCentersPtr, populationPtr->numClusters, cons);
            sumSpider(populationPtr->spiders[i], auxPopulationPtr->clusCentersPtr, populationPtr->numClusters, 1);  // sum = 1
            
            // Sum expression with delta
            for(int j = 0; j < populationPtr->numClusters; j++){
                for(int k = 0; k < populationPtr->pointDimension; k++){
                    auxPopulationPtr->clusCentersPtr[j]->point[k] = delta * (rand - 0.5);
                }
            }
            sumSpider(populationPtr->spiders[i], auxPopulationPtr->clusCentersPtr, populationPtr->numClusters, 1);  // sum = 1
        }
        else{   
            // male is not dominant(ND)
            // Sum expression with alpha
            diffSpiders(auxPopulationPtr->spiderWeightedMeanPtr, populationPtr->spiders[i], auxPopulationPtr->clusCentersPtr, populationPtr->numClusters);
            mulClusterCentersByConstant(auxPopulationPtr->clusCentersPtr, populationPtr->numClusters, alpha);
            sumSpider(populationPtr->spiders[i], auxPopulationPtr->clusCentersPtr, populationPtr->numClusters, 1);  // sum = 1
        }
    }
}

/** Replace offspring into spiders **/
void replacement(PopulationPtr populationPtr, AuxPopulationPtr auxPopulationPtr){
    double rand = 0;
    // Create replacement roulette for all spiders, giving more prob. to worst spi.
    createReplacementRoulette(populationPtr, auxPopulationPtr->replacementRoulette, populationPtr->lengthSpider);
    // Replace worst spider by offspring by comparing its fitness
    for(int i = 0; i < populationPtr->lengthOffspring; i++){
        rand = random_();   // 0.0 <= rand < 1.0
        // Go through the replacement roulette
        for(int j = 0; j < populationPtr->lengthSpider; j++){
            if (rand < auxPopulationPtr->replacementRoulette[j]){
                // replace spider "j" if it is worst than offspring "i"
                if (populationPtr->offspring[i]->fitness < populationPtr->spiders[j]->fitness){
                    for(int k = 0; k < populationPtr->numClusters; k++){
                        for(int h = 0; h < populationPtr->pointDimension; h++){
                            populationPtr->spiders[j]->centers[k]->point[h] = populationPtr->offspring[i]->centers[k]->point[h];
                        }
                    }
                    populationPtr->spiders[j]->fitness = populationPtr->offspring[i]->fitness;
                    populationPtr->spiders[j]->weight = 0;
                    for(int k = 0; k < populationPtr->offspring[i]->lengthDatasetClusters; k++){
                        populationPtr->spiders[j]->datasetClusters[k] = populationPtr->offspring[i]->datasetClusters[k];
                    }
                }
                break;
            }
        }
    }
}

void savePopulation(PopulationPtr populationPtr){
    for(int i = 0; i < populationPtr->lengthSpider; i++){
        for(int j = 0; j < populationPtr->numClusters; j++){
            for(int k = 0; k < populationPtr->pointDimension; k++){
                if (j * k == (populationPtr->numClusters - 1) * (populationPtr->pointDimension - 1)) {
                    printf("%f", populationPtr->spiders[i]->centers[j]->point[k]);
                } else {
                    printf("%f,", populationPtr->spiders[i]->centers[j]->point[k]);
                }
            }
        }
        printf("\n");
    }
}

/** Show best fitness **/
void showBestFitness(PopulationPtr populationPtr, int numberGeneration){
    printf("Generation: %d, Best Fitness [%d]: %f, Worst Fitness [%d]: %f \n",
        numberGeneration,
        populationPtr->indexBest,
        populationPtr->spiders[populationPtr->indexBest]->fitness, 
        populationPtr->indexWorst,
        populationPtr->spiders[populationPtr->indexWorst]->fitness);
}

/** Show Population **/
void showPopulation(PopulationPtr populationPtr){
    printf("\nPOPULATION\n");
    for(int i = 0; i < populationPtr->lengthSpider; i++){
        printf("%d: [", i);
        for(int j = 0; j < populationPtr->numClusters; j++){
            printf("(");
            for(int k = 0; k < populationPtr->pointDimension; k++){
                printf("%f;", populationPtr->spiders[i]->centers[j]->point[k]);
            }
            printf("),");
        }
        printf("\n");
        // printf("] Fitness: %f \n", populationPtr->spiders[i]->fitness);
    }
    printf("\n");
}

/** Show some parameters **/
void showParameters(PopulationPtr populationPtr, int numberGenerations, int numberDataset){
    printf("\n");
    printf("------------------------------\n");
    printf("---- S. Spider Algorithm -----\n");
    printf("------------------------------\n");
    printf("Number of Dataset:      \t%d\n", numberDataset);
    printf("Number of Generations:  \t%d\n", numberGenerations);
    printf("Population Size:        \t%d\n", populationPtr->lengthSpider);
    printf("Number of females:      \t%d\n", populationPtr->numberFemales);
    printf("Number of males:        \t%d\n", populationPtr->numberMales);
}

void showBestSpider(PopulationPtr populationPtr){
    printf("\nBest Spider: \n");
    printf("[");
    for(int j = 0; j < populationPtr->numClusters; j++){
        printf("(");
        for(int k = 0; k < populationPtr->pointDimension; k++){
            printf("%f;", populationPtr->spiders[populationPtr->indexBest]->centers[j]->point[k]);
        }
        printf("),");
    }
    printf("] \n");
    printf("Index best:  \t%d,  \tFitness: \t%f \n", populationPtr->indexBest, populationPtr->spiders[populationPtr->indexBest]->fitness);
    printf("Index worst: \t%d,  \tFitness: \t%f \n", populationPtr->indexWorst, populationPtr->spiders[populationPtr->indexWorst]->fitness);
    // printf("Index best:  \t%d,   \tFitness: \t%f \n", populationPtr->fitness[0]->key, populationPtr->fitness[0]->value);
    // printf("Index worst: \t%d,   \tFitness: \t%f \n", populationPtr->fitness[populationPtr->lengthSpider - 1]->key, populationPtr->fitness[populationPtr->lengthSpider - 1]->value);
    /* for (int i = 0; i < populationPtr->lengthSpider; i++) {
        printf("%d\t%d\t%f\n", i, populationPtr->fitness[i]->key, populationPtr->fitness[i]->value);
    } */
}

void showClusterBestSpider(PopulationPtr populationPtr, double **dataset, int row, int column){
    printf("----------------------------\n");
    printf("Cluster Generated by Best Spider: \n");
    for(int i = 0; i < populationPtr->numClusters; i++){
        printf("Cluster %d: ", i);
        for(int j = 0; j < populationPtr->spiders[populationPtr->indexBest]->lengthDatasetClusters; j++){
            if (i == populationPtr->spiders[populationPtr->indexBest]->datasetClusters[j]){
                printf("%d, ", j);
            }
        }
        printf("\nCenter %d: (", i);
        for(int j = 0; j < populationPtr->pointDimension; j++){
            printf("%f; ", populationPtr->spiders[populationPtr->indexBest]->centers[i]->point[j]);
        }
        printf(") \n\n");
    }
}

void saveClusterBestSpider(PopulationPtr populationPtr, double **dataset, int row, int column){
    char file_centroids[256];
    sprintf(file_centroids, "%s", "p_sso/centroids.csv");
    FILE *fp_centroids = fopen(file_centroids, "w");

    char file_labels[256];
    sprintf(file_labels, "%s", "p_sso/labels.csv");
    FILE *fp_labels = fopen(file_labels, "w");

    int labels [row];
    // double centers [populationPtr->numClusters][populationPtr->pointDimension];
    int i, j, k = 0;
    for(i = 0; i < populationPtr->numClusters; i++){
        for(j = 0; j < populationPtr->spiders[populationPtr->indexBest]->lengthDatasetClusters; j++){
            if (i == populationPtr->spiders[populationPtr->indexBest]->datasetClusters[j]){
                labels[j] = i;
            }
        }
        for(j = 0; j < populationPtr->pointDimension - 1; j++){
            // centers[i][j] = populationPtr->spiders[populationPtr->indexBest]->centers[i]->point[j];
            fprintf(fp_centroids, "%f,", populationPtr->spiders[populationPtr->indexBest]->centers[i]->point[j]);
        }
        // centers[i][j] = populationPtr->spiders[populationPtr->indexBest]->centers[i]->point[j];
        fprintf(fp_centroids, "%f\n", populationPtr->spiders[populationPtr->indexBest]->centers[i]->point[j]);
    }
    
    for (k = 0; k < row; k++) {
        // printf("%d, ", labels[k]);
        fprintf(fp_labels, "%d\n", labels[k]);
    }
    /* printf("\n");
    for(i = 0; i < populationPtr->numClusters; i++){
        for(j = 0; j < populationPtr->pointDimension; j++){
            printf("%f; ", centers[i][j]);
        }
        printf("\n");
    } */
    fclose(fp_centroids);
    fclose(fp_labels);
}

void showMetricBestSpider(PopulationPtr populationPtr, int world_rank){
    printf("Core [%d], Best metric [%d]: %f\n", world_rank, populationPtr->indexBest, populationPtr->spiders[populationPtr->indexBest]->fitness);
}

void showAllResults(PopulationPtr populationPtr, int numberGenerations, double **dataset, int row, int column){
    showParameters(populationPtr, numberGenerations, row);
    showBestSpider(populationPtr);        
    showClusterBestSpider(populationPtr, dataset, row, column); 
}

void freeMemoryAuxilarPopulation(PopulationPtr populationPtr, AuxPopulationPtr auxPopulationPtr){
    freeMemoryArrayClusterCenter(auxPopulationPtr->clusCentersPtr, populationPtr->numClusters);
    freeMemoryArrayDouble(auxPopulationPtr->males);
    freeMemoryArrayClusterCenter(auxPopulationPtr->spidersWeightsPtr, populationPtr->numClusters);
    freeMemoryArrayInt(auxPopulationPtr->matingGroup);
    freeMemoryArrayDouble(auxPopulationPtr->matingRoulette);
    freeMemorySpider(auxPopulationPtr->spiderWeightedMeanPtr);
    freeMemoryArrayDouble(auxPopulationPtr->replacementRoulette);
}

void freeMemoryAuxilarSpider(PopulationPtr populationPtr, AuxSpiderPtr auxSpiderPtr){
    freeMemoryArrayDouble(auxSpiderPtr->distances);
    freeMemoryArrayInt(auxSpiderPtr->numPointsForCluster);
    freeMemoryMatrixDouble(auxSpiderPtr->sum, populationPtr->numClusters);
}