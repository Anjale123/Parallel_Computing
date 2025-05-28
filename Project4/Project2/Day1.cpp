#include<mpi.h>
#include<stdio.h>
int main() {
	int np;
	int pid;
	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	MPI_Comm_rank(MPI_COMM_WORLD, &pid);
	MPI_Status sta;

	if (pid == 0) {
		char Send_msg = 'C';
		MPI_Send(&Send_msg, 5, MPI_CHAR, 1, 50, MPI_COMM_WORLD);
		printf("My process id is %d and I am the sender.\n", pid);
	}

	if (pid == 1) {
		char Recv_msg;
		MPI_Recv(&Recv_msg, 5, MPI_CHAR, 0, 50, MPI_COMM_WORLD,&sta);
		printf("My process id is %d and I am the Receiver.I received %c. \n", pid,Recv_msg);
	}
	
	MPI_Finalize();
	return 0;


}