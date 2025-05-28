#include<stdio.h>
#include<mpi.h>

int main() {
	int np;
	int pid;

	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	MPI_Comm_rank(MPI_COMM_WORLD, &pid);
	MPI_Status sta;

	if (pid == 0) {
		int sendmsg = 10;
		for (int i = 0; i < np; i++) {
			MPI_Send(&sendmsg, 1, MPI_INT, 1, 50, MPI_COMM_WORLD);
		}
		printf("\I am the  sender my process id is %d. ", pid);
		int recvmsg;
		MPI_Recv(&recvmsg, 1, MPI_INT, 1, 51, MPI_COMM_WORLD, &sta);
	}

	else if (pid > 0) {
		int recvmsg;
		MPI_Recv(&recvmsg, 1, MPI_INT, 0, 50, MPI_COMM_WORLD, &sta);
		printf("\n I am the receiver, my process id is %d.", pid);
	}

	MPI_Finalize();
	return 0;
}