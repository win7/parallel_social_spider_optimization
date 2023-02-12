/*
============================================================================
Authors:
 	Edwin Alvarez-Mamani and Jose Luis Soncco-Alvarez*
 	*Department of Informatics 
 	Universidad Nacional de San Antonio Abad del Cusco (UNSAAC) - Perú
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <mpi.h>

struct cricket {
	int key;
	float value;
} player[10], temp;


void main() {

	// depends on buffering
	int myrank;
	MPI_Status status;
	int size = 1010;
	float a[size], b[size];
	MPI_Init(&argc, &argv); /* Initialize MPI */
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank); /* Get rank */
	if( myrank == 0 ) {
	/* Send a message, then receive one */
		MPI_Send( a, size, MPI_FLOAT, 1, 17, MPI_COMM_WORLD );
		MPI_Recv( b, size, MPI_FLOAT, 1, 19, MPI_COMM_WORLD, &status );
	}
	else if( myrank == 1 ) {
	/* Send a message, then receive one */
		MPI_Send( a, size, MPI_FLOAT, 0, 19, MPI_COMM_WORLD );
		MPI_Recv( b, size, MPI_FLOAT, 0, 17, MPI_COMM_WORLD, &status );
		printf("%s\n", "end");
	}
	MPI_Finalize();
 	/* Terminate MPI */

	/* char c;         // reserve: 1 byte, store 1 character (-128 to 127)
	int i;          // reserve: 4 bytes, store -2147483648 to 2147483657
	short int s;    // reserve: 2 bytes, store -32768 to 32767
	float f;        // reserve: 4 bytes, store ?? - ?? (? digits)
	double d;       // reserve: 8 bytes, store ?? - ?? (? digits)
	unsigned int u; //reserve: r bytes store 0 to 4294967295

	i = 40000;
	printf("lives at %d %d\n", d, &d);

	f = 10.1;
	printf("lives at %f %d\n", f, &f);

	d = 10.102;
	printf("lives at %c %d\n", d, &d); */

	/* printf("Storage size for int is: %d \n", sizeof(int));
    printf("Storage size for long is: %d \n", sizeof(long));
    printf("Storage size for float is: %d \n", sizeof(float));
    printf("Storage size for double is: %d \n", sizeof(double)); */

    /* int i;

    if (i == 0) {
        printf("Hello1\n");
    }
    i = i + 1;
    printf("Hello2\n");
    printf("%d\n", i);
    printf("Hello3\n"); */

	/* char str[] = "topology=RING";
	int init_size = strlen(str);
	char delim[] = "=";

	char *ptr = strtok(str, delim);
	ptr = strtok(NULL, delim);
	while(ptr != NULL)
	{
		printf("'%s'\n", ptr);
		ptr = strtok(NULL, delim);
	} */

	/* int i, j, n;
	n = 10;
	float value_ [] = {1.33,1.34, 2.5, 1.2, 3.5, 2.3, 1.30, 1.28, 1.55, 2.0};

	for (i = 0; i < n; i++) {
		player[i].key = i;
		player[i].value = value_[i];
	}

	int index;
	float value;
	for (i=1; i < n; i++) {
		value = player[i].value ;
		index = i-1;
		while (index >= 0 && player[index].value  > value) {
			player[index+1].value  = player[index].value;
			player[index+1].key  = player[index].key;
			index--;
		}
		player[index+1].value  = value;
		player[index+1].key  = i;
	}

	for (i = 0; i < n; i++) {
		printf("%d\t%f\n",player[i].key, player[i].value);
	}

	printf("Best: %f\n", player[9].value);
	printf("Worst: %f\n", player[0].value); */


	/* int *columns = NULL;
    allocateMemoryArrayInt(&columns, 10000);
    printf("%d\n", columns[1000]);
    freeMemoryArrayInt(columns); */
}