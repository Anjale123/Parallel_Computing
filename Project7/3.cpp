#include<MPI.h>
#include<stdio.h>
int main2() {

	int np;
	int pid;
	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	MPI_Comm_rank(MPI_COMM_WORLD, &pid);
	MPI_Status sta;
	int arr[6];
	int maximum;
	if (pid == 0) {
	//mul=10;
		arr[0] = 11;
		arr[1] = 21;
		arr[2] = 35;
		arr[3] = 41;
		arr[4] = 55;
		arr[5] = 6;
	}
	int recvarr[2];
	int max = 0;
	MPI_Scatter(&arr, 2, MPI_INT, &recvarr, 2, MPI_INT, 0, MPI_COMM_WORLD);
	printf("\nMy processor id is %d.Received data are ", pid);
	printf(" % d and %d.", recvarr[0], recvarr[1]);
	if (recvarr[0] > recvarr[1])
		max = recvarr[0];
	else
		max = recvarr[1];
	MPI_Reduce(&max, &maximum, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
	if (pid == 0) {
		printf("\nMy processor id is %d.Total received is %d", pid, maximum);
	}
	MPI_Finalize();
	return 0;
}
/*mpiexec -n 5 Project6.exe
My processor id is 1.Received data is 2 and2
The value i sent is 4
The value arr i received is246810-858993460
My processor id is 2.Received data is 2 and3
The value i sent is 6
The value arr i received is246810-858993460
My processor id is 3.Received data is 2 and4
The value i sent is 8
The value arr i received is246810-858993460
My processor id is 0.Received data is 2 and1
The value i sent is 2
The value arr i received is246810-858993460
My processor id is 4.Received data is 2 and5
The value i sent is 10
The value arr i received is246810-858993460*/