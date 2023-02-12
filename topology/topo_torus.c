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
		token = world_rank;
		if (world_rank % 4 == 0){
			MPI_Send(&token, 1, MPI_INT, (world_rank - 4 + 24) % 24, 0, MPI_COMM_WORLD);
			MPI_Send(&token, 1, MPI_INT, (world_rank + 1) % 24, 0, MPI_COMM_WORLD);
			MPI_Send(&token, 1, MPI_INT, (world_rank + 3) % 24, 0, MPI_COMM_WORLD);
			MPI_Send(&token, 1, MPI_INT, (world_rank + 4) % 24, 0, MPI_COMM_WORLD);
			// MPI_Barrier(MPI_COMM_WORLD);
			MPI_Recv(&token, 1, MPI_INT, (world_rank - 4 + 24) % 24, 0, MPI_COMM_WORLD, &status);
			printf("Process %d received token %d from process %d\n", world_rank, token, status.MPI_SOURCE);
			MPI_Recv(&token, 1, MPI_INT, (world_rank + 1) % 24, 0, MPI_COMM_WORLD, &status);
			printf("Process %d received token %d from process %d\n", world_rank, token, status.MPI_SOURCE);
			MPI_Recv(&token, 1, MPI_INT, (world_rank + 3) % 24, 0, MPI_COMM_WORLD, &status);
			printf("Process %d received token %d from process %d\n", world_rank, token, status.MPI_SOURCE);
			MPI_Recv(&token, 1, MPI_INT, (world_rank + 4) % 24, 0, MPI_COMM_WORLD, &status);
			printf("Process %d received token %d from process %d\n", world_rank, token, status.MPI_SOURCE);
		} else {
			if (world_rank % 4 == 3){
				MPI_Send(&token, 1, MPI_INT, (world_rank - 4 + 24) % 24, 0, MPI_COMM_WORLD);
				MPI_Send(&token, 1, MPI_INT, (world_rank - 3 + 24) % 24, 0, MPI_COMM_WORLD);
				MPI_Send(&token, 1, MPI_INT, (world_rank - 1 + 24) % 24, 0, MPI_COMM_WORLD);
				MPI_Send(&token, 1, MPI_INT, (world_rank + 4) % 24, 0, MPI_COMM_WORLD);
				// MPI_Barrier(MPI_COMM_WORLD);
				MPI_Recv(&token, 1, MPI_INT, (world_rank - 4 + 24) % 24, 0, MPI_COMM_WORLD, &status);
				printf("Process %d received token %d from process %d\n", world_rank, token, status.MPI_SOURCE);
				MPI_Recv(&token, 1, MPI_INT, (world_rank - 3 + 24) % 24, 0, MPI_COMM_WORLD, &status);
				printf("Process %d received token %d from process %d\n", world_rank, token, status.MPI_SOURCE);
				MPI_Recv(&token, 1, MPI_INT, (world_rank - 1 + 24) % 24, 0, MPI_COMM_WORLD, &status);
				printf("Process %d received token %d from process %d\n", world_rank, token, status.MPI_SOURCE);
				MPI_Recv(&token, 1, MPI_INT, (world_rank + 4) % 24, 0, MPI_COMM_WORLD, &status);
				printf("Process %d received token %d from process %d\n", world_rank, token, status.MPI_SOURCE);
			} else{
				MPI_Send(&token, 1, MPI_INT, (world_rank - 4 + 24) % 24, 0, MPI_COMM_WORLD);
				MPI_Send(&token, 1, MPI_INT, (world_rank - 1 + 24) % 24, 0, MPI_COMM_WORLD);
				MPI_Send(&token, 1, MPI_INT, (world_rank + 1) % 24, 0, MPI_COMM_WORLD);
				MPI_Send(&token, 1, MPI_INT, (world_rank + 4) % 24, 0, MPI_COMM_WORLD);
				// MPI_Barrier(MPI_COMM_WORLD);
				MPI_Recv(&token, 1, MPI_INT, (world_rank - 4 + 24) % 24, 0, MPI_COMM_WORLD, &status);
				printf("Process %d received token %d from process %d\n", world_rank, token, status.MPI_SOURCE);
				MPI_Recv(&token, 1, MPI_INT, (world_rank - 1 + 24) % 24, 0, MPI_COMM_WORLD, &status);
				printf("Process %d received token %d from process %d\n", world_rank, token, status.MPI_SOURCE);
				MPI_Recv(&token, 1, MPI_INT, (world_rank + 1) % 24, 0, MPI_COMM_WORLD, &status);
				printf("Process %d received token %d from process %d\n", world_rank, token, status.MPI_SOURCE);
				MPI_Recv(&token, 1, MPI_INT, (world_rank + 4) % 24, 0, MPI_COMM_WORLD, &status);
				printf("Process %d received token %d from process %d\n", world_rank, token, status.MPI_SOURCE);
			}
		}
	}
	MPI_Finalize();
	return 0;
}