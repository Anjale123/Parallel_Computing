#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>

int main() {
	int np;
	int pid;
	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	MPI_Comm_rank(MPI_COMM_WORLD, &pid);
	MPI_Status sta;

	int arr[100];

	if (pid == 0) {
		for (int i = 0; i < 100; i++) {
			arr[i] = rand() % 1000;
		}

		for (int i = 1; i < 10; i++) {
			MPI_Send(&arr[i * 10], 10, MPI_INT, i, 50, MPI_COMM_WORLD);
		}

		printf("My proceesor id is %d .Data is: \n", pid);
		int globalMaximum = 0;
		int globalMinimum = 1000;

		for (int i = 0; i < 10; i++) {
			printf("%d ", arr[i]);

			if (arr[i] > globalMaximum) {
				globalMaximum = arr[i];
			}
			if (arr[i] < globalMinimum) {
				globalMinimum = arr[i];
			}
		}

		printf("\n");
		for (int i = 1; i < 10; i++) {
			int recMax, recMin;
			MPI_Recv(&recMax, 1, MPI_INT, i, 50, MPI_COMM_WORLD, &sta);
			MPI_Recv(&recMin, 1, MPI_INT, i, 50, MPI_COMM_WORLD, &sta);
			printf("From proceesor id %d, Received Max: %d and Min: %d \n ", i, recMax, recMin);

			if (arr[i] > globalMaximum) {
				globalMaximum = recMax;
			}
			if (arr[i] < globalMinimum) {
				globalMinimum = recMin;
			}

		}

		printf("Global Maximum: %d Global Minimum: %d at pid: %d \n \n", globalMaximum, globalMinimum, pid);

	}
	else {
		int recvarr[10];
		MPI_Recv(&recvarr, 10, MPI_INT, 0, 50, MPI_COMM_WORLD, &sta);
		printf("My processor id is %d . Received Data is \n", pid);

		int localMax = 0;
		int localMin = 1000;

		for (int i = 0; i < 10; i++) {
			printf("%d \n", recvarr[i]);

			if (recvarr[i] > localMax) {
				localMax = recvarr[i];
			}
			if (recvarr[i] < localMin) {
				localMin = recvarr[i];
			}
		}

		printf("local Minimum: %d local maximum: %d \n \n", localMin, localMax);

		for (int i = 1; i < 10; i++) {
			if (pid == i) {
				MPI_Send(&localMax, 1, MPI_INT, 0, 50, MPI_COMM_WORLD);
				MPI_Send(&localMin, 1, MPI_INT, 0, 50, MPI_COMM_WORLD);
			}
		}
	}

	MPI_Finalize();
	return 0;
}



