#include<stdio.h>
#include<mpi.h>

int main2() {
	int np;
	int pid;
	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	MPI_Comm_rank(MPI_COMM_WORLD, &pid);
	MPI_Status sta;

	if (pid == 0) {
		int sendmsg = 5;
		MPI_Send(&sendmsg, 1, MPI_INT, 1, 50, MPI_COMM_WORLD);
		printf("\n I am the sender.my process id is %d and send msg is %d. ", pid, sendmsg);
	}

	if (pid == 1) {
		int recvmsg;
		MPI_Recv(&recvmsg, 1, MPI_INT, 0, 50, MPI_COMM_WORLD, &sta);
		printf("\n I am the sender.my process id is %d and send msg is %d. ", pid, recvmsg);
	}

	MPI_Finalize();
	return 0;
}