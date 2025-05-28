#include<stdio.h>
#include<mpi.h>

int mainnn() {
	int np;
	int pid;

	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	MPI_Comm_rank(MPI_COMM_WORLD, &pid);
	MPI_Status sta;

	if (pid == 0) {
		int a = 10;
		int b = 20;
		int Recv_a[3];

		for (int i = 1; i <=3; i++) {
			MPI_Send(&a, 1, MPI_INT, i, 50, MPI_COMM_WORLD);
			MPI_Send(&b, 1, MPI_INT, i, 51, MPI_COMM_WORLD);
		}

		for (int i = 1; i <=3; i++) {
			MPI_Recv(&Recv_a, 3, MPI_INT, i, 52, MPI_COMM_WORLD, &sta);
		}

	}

	else if (pid == 1) {
		int recv_a;
		int recv_b;

		MPI_Recv(&recv_a, 1, MPI_INT, 0, 50, MPI_COMM_WORLD, &sta);
		MPI_Recv(&recv_b, 1, MPI_INT, 0, 51, MPI_COMM_WORLD, &sta);

		int summation = recv_a + recv_b;
		MPI_Send(&summation, 1, MPI_INT, 0, 52, MPI_COMM_WORLD);
		printf("\n The process id is %d and summaation is: %d", pid,  summation);
	}

	else if (pid == 2) {
		int recv_a;
		int recv_b;

		MPI_Recv(&recv_a, 1, MPI_INT, 0, 50, MPI_COMM_WORLD, &sta);
		MPI_Recv(&recv_b, 1, MPI_INT, 0, 51, MPI_COMM_WORLD, &sta);

		int sub = recv_a - recv_b;
		MPI_Send(&sub, 1, MPI_INT, 0, 52, MPI_COMM_WORLD);
		printf("\n The process id is %d and summaation is: %d", pid, sub);
	}

	else if (pid == 3) {
		int recv_a;
		int recv_b;

		MPI_Recv(&recv_a, 1, MPI_INT, 0, 50, MPI_COMM_WORLD, &sta);
		MPI_Recv(&recv_b, 1, MPI_INT, 0, 51, MPI_COMM_WORLD, &sta);

		int div = recv_a / recv_b;
		MPI_Send(&div, 1, MPI_INT, 0, 52, MPI_COMM_WORLD);
		printf("\n The process id is %d and summaation is: %d", pid, div);
	}

	MPI_Finalize();
	return 0;
}