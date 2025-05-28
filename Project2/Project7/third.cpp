#include<stdio.h>
#include<mpi.h>

int mainn(){
	int np;
	int pid;

	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	MPI_Comm_rank(MPI_COMM_WORLD, &pid);
	MPI_Status sta;

	if (pid == 0) {
		int sendmsg = 5;
		MPI_Send(&sendmsg, 1, MPI_INT, 1, 50, MPI_COMM_WORLD);
		printf("\n I am the sender. my process id is %d and the send msg is %d ", pid, sendmsg);

		int recvmsg;
		MPI_Recv(&recvmsg, 1, MPI_INT, 1, 51, MPI_COMM_WORLD, &sta);
	}

	if (pid == 1) {
		int recvmsg;
		MPI_Recv(&recvmsg, 1, MPI_INT, 0, 50, MPI_COMM_WORLD, &sta);
		printf("\n I am the receiver. my process id is %d and received msg is %d ", pid, recvmsg);

		int smsg = 1;
		MPI_Send(&smsg, 1, MPI_INT, 0, 51, MPI_COMM_WORLD);
	}

	MPI_Finalize();
	return 0;
}