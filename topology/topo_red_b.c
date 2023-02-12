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
		switch (world_rank) { 
			case 9: 
			case 10:
			case 13:
			case 14:
				MPI_Send(&token, 1, MPI_INT, (world_rank - 4 + 24) % world_size, 0, MPI_COMM_WORLD);
				MPI_Send(&token, 1, MPI_INT, (world_rank - 1 + 24) % world_size, 0, MPI_COMM_WORLD);
				MPI_Send(&token, 1, MPI_INT, (world_rank + 1) % world_size, 0, MPI_COMM_WORLD);
				MPI_Send(&token, 1, MPI_INT, (world_rank + 4) % world_size, 0, MPI_COMM_WORLD);
				// MPI_Barrier(MPI_COMM_WORLD);
				MPI_Recv(&token, 1, MPI_INT, (world_rank - 4 + 24) % world_size, 0, MPI_COMM_WORLD, &status);
				printf("Process %d received token %d from process %d\n", world_rank, token, status.MPI_SOURCE);
				MPI_Recv(&token, 1, MPI_INT, (world_rank - 1 + 24) % world_size, 0, MPI_COMM_WORLD, &status);
				printf("Process %d received token %d from process %d\n", world_rank, token, status.MPI_SOURCE);
				MPI_Recv(&token, 1, MPI_INT, (world_rank + 1) % world_size, 0, MPI_COMM_WORLD, &status);
				printf("Process %d received token %d from process %d\n", world_rank, token, status.MPI_SOURCE);
				MPI_Recv(&token, 1, MPI_INT, (world_rank + 4) % world_size, 0, MPI_COMM_WORLD, &status);
				printf("Process %d received token %d from process %d\n", world_rank, token, status.MPI_SOURCE);
			break; 
			case 0:
			case 4:
			case 6:
			case 8:
			case 12:
			case 16:
			case 18:
			case 20:
				MPI_Send(&token, 1, MPI_INT, (world_rank - 4 + 24) % world_size, 0, MPI_COMM_WORLD);
				MPI_Send(&token, 1, MPI_INT, (world_rank + 1) % world_size, 0, MPI_COMM_WORLD);
				MPI_Send(&token, 1, MPI_INT, (world_rank + 4) % world_size, 0, MPI_COMM_WORLD);
				// MPI_Barrier(MPI_COMM_WORLD);
				MPI_Recv(&token, 1, MPI_INT, (world_rank - 4 + 24) % world_size, 0, MPI_COMM_WORLD, &status);
				printf("Process %d received token %d from process %d\n", world_rank, token, status.MPI_SOURCE);
				MPI_Recv(&token, 1, MPI_INT, (world_rank + 1) % world_size, 0, MPI_COMM_WORLD, &status);
				printf("Process %d received token %d from process %d\n", world_rank, token, status.MPI_SOURCE);
				MPI_Recv(&token, 1, MPI_INT, (world_rank + 4) % world_size, 0, MPI_COMM_WORLD, &status);
				printf("Process %d received token %d from process %d\n", world_rank, token, status.MPI_SOURCE);
			break; 
			case 3:
			case 5:
			case 7:
			case 11:
			case 15:
			case 17:
			case 19:
			case 23:
				MPI_Send(&token, 1, MPI_INT, (world_rank - 4 + 24) % world_size, 0, MPI_COMM_WORLD);
				MPI_Send(&token, 1, MPI_INT, (world_rank - 1 + 24) % world_size, 0, MPI_COMM_WORLD);
				MPI_Send(&token, 1, MPI_INT, (world_rank + 4) % world_size, 0, MPI_COMM_WORLD);
				// MPI_Barrier(MPI_COMM_WORLD);
				MPI_Recv(&token, 1, MPI_INT, (world_rank - 4 + 24) % world_size, 0, MPI_COMM_WORLD, &status);
				printf("Process %d received token %d from process %d\n", world_rank, token, status.MPI_SOURCE);
				MPI_Recv(&token, 1, MPI_INT, (world_rank - 1 + 24) % world_size, 0, MPI_COMM_WORLD, &status);
				printf("Process %d received token %d from process %d\n", world_rank, token, status.MPI_SOURCE);
				MPI_Recv(&token, 1, MPI_INT, (world_rank + 4) % world_size, 0, MPI_COMM_WORLD, &status);
				printf("Process %d received token %d from process %d\n", world_rank, token, status.MPI_SOURCE);
			break;
			case 1:
			case 2:
				MPI_Send(&token, 1, MPI_INT, (world_rank - 1 + 24) % world_size, 0, MPI_COMM_WORLD);
				MPI_Send(&token, 1, MPI_INT, (world_rank + 1) % world_size, 0, MPI_COMM_WORLD);
				MPI_Send(&token, 1, MPI_INT, (world_rank + 4) % world_size, 0, MPI_COMM_WORLD);
				// MPI_Barrier(MPI_COMM_WORLD);
				MPI_Recv(&token, 1, MPI_INT, (world_rank - 1 + 24) % world_size, 0, MPI_COMM_WORLD, &status);
				printf("Process %d received token %d from process %d\n", world_rank, token, status.MPI_SOURCE);
				MPI_Recv(&token, 1, MPI_INT, (world_rank + 1) % world_size, 0, MPI_COMM_WORLD, &status);
				printf("Process %d received token %d from process %d\n", world_rank, token, status.MPI_SOURCE);
				MPI_Recv(&token, 1, MPI_INT, (world_rank + 4) % world_size, 0, MPI_COMM_WORLD, &status);
				printf("Process %d received token %d from process %d\n", world_rank, token, status.MPI_SOURCE);
			break;
			case 21:
			case 22:
				MPI_Send(&token, 1, MPI_INT, (world_rank - 4 + 24) % world_size, 0, MPI_COMM_WORLD);
				MPI_Send(&token, 1, MPI_INT, (world_rank - 1 + 24) % world_size, 0, MPI_COMM_WORLD);
				MPI_Send(&token, 1, MPI_INT, (world_rank + 1) % world_size, 0, MPI_COMM_WORLD);
				// MPI_Barrier(MPI_COMM_WORLD);
				MPI_Recv(&token, 1, MPI_INT, (world_rank - 4 + 24) % world_size, 0, MPI_COMM_WORLD, &status);
				printf("Process %d received token %d from process %d\n", world_rank, token, status.MPI_SOURCE);
				MPI_Recv(&token, 1, MPI_INT, (world_rank - 1 + 24) % world_size, 0, MPI_COMM_WORLD, &status);
				printf("Process %d received token %d from process %d\n", world_rank, token, status.MPI_SOURCE);
				MPI_Recv(&token, 1, MPI_INT, (world_rank + 1) % world_size, 0, MPI_COMM_WORLD, &status);
				printf("Process %d received token %d from process %d\n", world_rank, token, status.MPI_SOURCE);
			break;
			default:
				printf("world_rank no found..."); 
			break; 
		}
	}
	MPI_Finalize();
	return 0;
}