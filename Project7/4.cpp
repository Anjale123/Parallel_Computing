#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>
int main3() { 

	int np;
	int pid;
	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	MPI_Comm_rank(MPI_COMM_WORLD, &pid);
	//MPI_Status sta;
	int mul;
	int arr[6];
	int recevarr[6];
	if (pid == 0) {
		mul = 2;
		arr[0] = 1;
		arr[1] = 2;
		arr[2] = 3;
		arr[3] = 4;
		arr[4] = 5;
		arr[5] = 6;
	
	}
	MPI_Bcast(&mul, 1, MPI_INT, 0, MPI_COMM_WORLD);
	int recvarray[1];
	MPI_Scatter(&arr, 1, MPI_INT, &recevarr, 1, MPI_INT, 0, MPI_COMM_WORLD);
	printf("My processor id is %d.Received data is %d and", pid, mul);
	printf("%d\n", recevarr[0]);
	int value = mul * recevarr[0];
	printf("The value i sent is %d\n", value);
	MPI_Allgather(&value, 1, MPI_INT, &recevarr, 1, MPI_INT, MPI_COMM_WORLD);
	printf("The value arr i received is");
	for (int i = 0; i < 6; i++) {
		printf("%d", recevarr[i]);
	}
	printf("\n");
	MPI_Finalize();
	return 0;



}

/*>mpiexec -n 5 Project6.exe
My processor id is 1.Received data is 2 and2
The value i sent is 4
The value arr i received is246810-858993460
My processor id is 0.Received data is 2 and1
The value i sent is 2
The value arr i received is246810-858993460
My processor id is 4.Received data is 2 and5
The value i sent is 10
The value arr i received is246810-858993460
My processor id is 3.Received data is 2 and4
The value i sent is 8
The value arr i received is246810-858993460
My processor id is 2.Received data is 2 and3
The value i sent is 6
The value arr i received is246810-858993460*/