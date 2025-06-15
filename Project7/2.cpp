//MPI Reduction operation
#include<MPI.h>
#include<stdio.h>
int main() {

	int np;
	int pid;
	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	MPI_Comm_rank(MPI_COMM_WORLD, &pid);
	MPI_Status sta;
	int arr[6];
	int total;
	if (pid == 0) {
		arr[0] = 1;
		arr[1] = 2;
		arr[2] = 3;
		arr[3] = 4;
		arr[4] = 5;
		arr[5] = 6;

	}
	int recvarr[2];
	MPI_Scatter(&arr, 2, MPI_INT, &recvarr, 2, MPI_INT, 0, MPI_COMM_WORLD);
	printf("\nMyprocessor id is %d.Received data are ", pid);
	printf("%d and %d", recvarr[0] ,recvarr[1]);
	int sum = recvarr[0] + recvarr[1];
	MPI_Reduce(&sum, &total, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	if (pid == 0) {
		printf("\nMy processor id is %d.Total received is %d", pid, total);
	}

	MPI_Finalize();
	return 0;
}
/*mpiexec -n 5 Project6.exe

Myprocessor id is 2.Received data are 5 and 6
Myprocessor id is 0.Received data are 1 and 2
My processor id is 0.Total received is 858993477
Myprocessor id is 4.Received data are -858993460 and -858993460
Myprocessor id is 1.Received data are 3 and 4
Myprocessor id is 3.Received data are -858993460 and -858993460*/