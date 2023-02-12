#!/bin/bash

# mpirun -n 24 --oversubscribe ./main_psso input/crude_oil.cols 3 56 input/crude_oil.data input/policy.in 169735477
# mpirun -n 24 --oversubscribe ./main_psso input/breast_tissue.cols 6 106 input/breast_tissue.data input/policy.in 169735477
# mpirun -n 24 --oversubscribe ./main_psso input/iris.cols 3 150 input/iris.data input/policy.in 169735477
# mpirun -n 24 --oversubscribe ./main_psso input/wine.cols 3 178 input/wine.data input/policy.in 169735477
# mpirun -n 24 --oversubscribe ./main_psso input/heart.cols 2 270 input/heart.data input/policy.in 169735477
# mpirun -n 24 --oversubscribe ./main_psso input/column_3c.cols 3 310 input/column_3c.data input/policy.in 169735477
# mpirun -n 24 --oversubscribe ./main_psso input/australian.cols 2 690 input/australian.data input/policy.in 169735477
# mpirun -n 24 --oversubscribe ./main_psso input/breast_cancer.cols 2 699 input/breast_cancer.data input/policy.in 169735477
# mpirun -n 24 --oversubscribe ./main_psso input/healthy_older_people.cols 4 724 input/healthy_older_people.data input/policy.in 169735477
# mpirun -n 24 --oversubscribe ./main_psso input/avila.cols 12 10430 input/avila.data input/policy.in 169735477

mpirun -n 24 --oversubscribe ./main_psso input/iris.cols 3 150 input/iris.data generatePopulation/iris.data input/policy.in 0 10293 169735477