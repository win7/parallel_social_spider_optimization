# Parallel Social Spider Otimization (P-SSO)


## Introduction

This directory contains the source code of the Social Spider Optimization (SSO) and Parallel Social Spider Optimization (P-SSO) algorithms for the Clustering Problem. The source code was tested under MANJARO/UBUNTU LINUX platforms.

The authors of the implementations are: Edwin Alvarez-Mamani and Jose Luis Soncco-Alvarez

The last two authors are from the Department of Informatics at Universidad Nacional de San Antonio Abad del Cusco.

## Installation

To run the SS or P-SSO algorithms you need to install the following:
- gcc
- openmpi
- valgrind (optional)

## Source Code

- main_sso.c 		: 	This file contains the main function for SSO.
- main_psso.c 		: 	This file contains the main function for P-SSO.
- clusterCenter.c   :  	This file contains functions to interact with the ClusterCenter data structure.
- population.c      :   This file contains the functions of the SSO algorithm for the clustering problem  that interact with the ClusterCenter and Spider structures.
- spider.c     		: 	This file contains functions to interact with the Spider data structure.
- structs.h        	:	This file contains the definition of clusterCenter, spider, population and auxPopulation structures.
- topology.c        :   This file contains the migrations functions for P-SSO.
- utils.c 	        :   This file contains some auxiliary functions.

## Usage

### Dataset

The algorithms (SSO or P-SSO) takes as input two dataset one taken from UCI machine learning (e.g iris.data) and the other dataset that represents the number of columns (e.g. iris.cols) that will be taken from the main dataset to perform the experiments.

### Run SSO

1. Compile: 
    ```
    make ALGO=sso clean all
    ```

2. Run:

    The parameter options are described below:

    - columnsFile	:	dataset that represents the number of columns
    - k				:	number of clusters
    - n 			:	dataset size of "dataFile"
    - dataFile		:	dataset from UCI machine learning
    - seed			:	seed for rand

    Example: For the some dataset the command is the following: `./main_sso columnsFile k n dataFile seed`
    ```
    ./main_sso input/iris.cols 3 150 input/iris.data 169735477
    ```
    More examples:

    ```
    ./main_sso input/crude_oil.cols 3 56 input/crude_oil.data 169735477
    ```
    ```
    ./main_sso input/breast_tissue.cols 6 106 input/breast_tissue.data 169735477
    ```
    ```
    ./main_sso input/wine.cols 3 178 input/wine.data 169735477
    ```
    ```
    ./main_sso input/heart.cols 2 270 input/heart.data 169735477
    ```
    ```
    ./main_sso input/column_2c.cols 2 310 input/column_2c.data 169735477
    ```
    ```
    ./main_sso input/column_3c.cols 3 310 input/column_3c.data 169735477
    ```
    ```
    ./main_sso input/australian.cols 2 690 input/australian.data 169735477
    ```
    ```
    ./main_sso input/breast_cancer_wisconsin.cols 2 699 input/breast_cancer_wisconsin.data 169735477
    ```
    ```
    ./main_sso input/healthy_older_people.cols 4 724 input/healthy_older_people.data 169735477
    ```
    ```
    ./main_sso input/yeast.cols 10 1484 input/avila.data 169735477
    ```
    ```
    ./main_sso input/avila.cols 12 10430 input/avila.data 169735477
    ```

3. Result: 

    In the `output` folder, there are the centroids and the labels.

### Run P-SSO

1. Compile: 
    ```
    make ALGO=p-sso clean all
    ```

2. Edit migration policies

    Migration policies for population exchange

    | Parameters  | Values |
    | ------------- | ------------- |
    | Migration topology (`topology`)  | unidirectional ring (`RING`), tree (`TREE`), net-A (`NETA`), net-B (`NETB`), torus (`TORUS`) , complete graph (`GRAPH`), between similar (`SAME`), between good and bad (`GOODBAD`), between random (`RAND`)  |
    | Type of migrant individual (`choiceEmi`)  | `BEST`, `WORST`, `RANDOM`  |
    | Type of immigrant individual (`choiceImm`)  | `BEST`, `WORST`, `RANDOM`  |
    | Emigration policy (`emigration`)  | `CLONE`, `REMOVE`  |
    | Number of emigrants/immigrants ('numberEmiImm')  | `1`, `2`, `3`, `4`, `5`  |
    | Migration interval (`intervalEmiImm`)   | `1`, `2`, `4`, `6`, `8`, `10`  |


    We recommend using the following parameters (edit it in `policy/policy.in`):

    - topology:NETA
    - emigration:CLONE
    - choiceEmi:BEST
    - choiceImm:RANDOM
    - numberEmiImm:2
    - intervalEmiImm:1

3. Run:

    The parameter options are described below:

    - columnsFile	:	dataset that represents the number of columns
    - k				:	number of clusters
    - n 			:	dataset size of "dataFile"
    - dataFile		:	dataset from UCI machine learning
    - policy        :   migration policies for population exchange
    - seed			:	seed for rand

    Example: For the some dataset the command is the following: `mpirun -n 24 --oversubscribe ./main_psso columnsFile k n dataFile policy seed`
    ```
    mpirun -n 24 --oversubscribe ./main_psso input/iris.cols 3 150 input/iris.data policy/policy.in 169735477
    ```
    More examples:

    ```
    mpirun -n 24 --oversubscribe ./main_psso input/crude_oil.cols 3 56 input/crude_oil.data policy/policy.in 169735477
    ```
    ```
    mpirun -n 24 --oversubscribe ./main_psso input/breast_tissue.cols 6 106 input/breast_tissue.data policy/policy.in 169735477
    ```
    ```
    mpirun -n 24 --oversubscribe ./main_psso input/wine.cols 3 178 input/wine.data policy/policy.in 169735477
    ```
    ```
    mpirun -n 24 --oversubscribe ./main_psso input/heart.cols 2 270 input/heart.data policy/policy.in 169735477
    ```
    ```
    mpirun -n 24 --oversubscribe ./main_psso input/column_2c.cols 2 310 input/column_2c.data policy/policy.in 169735477
    ```
    ```
    mpirun -n 24 --oversubscribe ./main_psso input/column_3c.cols 3 310 input/column_3c.data policy/policy.in 169735477
    ```
    ```
    mpirun -n 24 --oversubscribe ./main_psso input/australian.cols 2 690 input/australian.data policy/policy.in 169735477
    ```
    ```
    mpirun -n 24 --oversubscribe ./main_psso input/breast_cancer_wisconsin.cols 2 699 input/breast_cancer_wisconsin.data policy/policy.in 169735477
    ```
    ```
    mpirun -n 24 --oversubscribe ./main_psso input/healthy_older_people.cols 4 724 input/healthy_older_people.data policy/policy.in 169735477
    ```
    ```
    mpirun -n 24 --oversubscribe ./main_psso input/yeast.cols 10 1484 input/avila.data policy/policy.in 169735477
    ```
    ```
    mpirun -n 24 --oversubscribe ./main_psso input/avila.cols 12 10430 input/avila.data policy/policy.in 169735477
    ```

3. Result: 

    In the `output` folder, there are the centroids and the labels.

## Bug Reporting

If you find any problem in our programs please contact us to: 
win7.eam@gmail.com

## Citing

If you find P-SSO useful for your research, please consider citing the following paper:

```
@inproceedings{alvarez2021parallel,
  title={Parallel social spider optimization algorithms with island model for the clustering problem},
  author={Alvarez-Mamani, Edwin and Enciso-Rodas, Lauro and Ayala-Rinc{\'o}n, Mauricio and Soncco-{\'A}lvarez, Jos{\'e} L},
  booktitle={Information Management and Big Data: 7th Annual International Conference, SIMBig 2020, Lima, Peru, October 1--3, 2020, Proceedings},
  pages={122--138},
  year={2021},
  organization={Springer}
}
```
