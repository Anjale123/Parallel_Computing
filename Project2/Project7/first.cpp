#include<stdio.h>
#include<mpi.h>

int mainnn() {
	int np;
	int pid;

	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	MPI_Comm_rank(MPI_COMM_WORLD, &pid);

	if (pid == 0) {
		printf("\n Hello");
		printf("\n I am master processor.my process id is %d ", pid);
	}
	else if (pid == 1) {
		printf("\n Hiii");
		printf("\n I am second master processor.my process id is %d ", pid);
	}
	else {
		printf("\n Hello Hii");
		printf("\n I am solver.my process id is %d ", &pid);
	}

	MPI_Finalize();
	return 0;
}