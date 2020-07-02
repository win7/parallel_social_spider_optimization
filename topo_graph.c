/*
============================================================================
Authors:
 	Edwin Alvarez-Mamani and Jose Luis Soncco-Alvarez*
 	*Department of Informatics 
 	Universidad Nacional de San Antonio Abad del Cusco (UNSAAC) - Perú
============================================================================
*/

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
	MPI_Status status;
	int world_rank;
	int world_size;
	int token;
	// Initialize the MPI environment
	MPI_Init(NULL, NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);

	for (int k = 0; k < 1; k++){
		for (int i = 0; i < world_size; i++) {
			if (i != world_rank) {
				token = world_rank;
				MPI_Send(&token, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
			}
		}
		MPI_Barrier(MPI_COMM_WORLD);
		for (int i = 0; i < world_size; i++) {
			if (i != world_rank) {
				MPI_Recv(&token, 1, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
				printf("Process %d received token %d from process %d\n", world_rank, token, status.MPI_SOURCE);
			}
		}
	}
	MPI_Finalize();
	return 0;
}

// Compile:	mpicc topo_graph.c 
// Run:		mpirun -n 24 --oversubscribe ./a.out

/* for (int i = 0; i < world_size; i++) {
	if (i != world_rank) {
		token = world_rank;
		MPI_Send(&token, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
		MPI_Barrier(MPI_COMM_WORLD);
		MPI_Recv(&token, 1, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
		printf("Process %d received token %d from process %d\n", world_rank, token, status.MPI_SOURCE);
	}
} */