#include<stdio.h>
#include<mpi.h>
int main() {
	int pid;
	int np;
	
	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	MPI_Comm_rank(MPI_COMM_WORLD, &pid);

	printf ("\n Number of processors connected with the communicator is %d. ", &np);
	printf ("\n Hello world... from process with the id %d. ", &pid);

	MPI_Finalize();
	return 0;

}