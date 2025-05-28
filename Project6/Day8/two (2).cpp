//find the summation of 64 values from 1 to 64 using 8 processes

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
	int num[64];
	int Total = 0;


	if (pid == 0) {
		for (int i = 0; i < 64; i++) {
			num[i] = i + 1;

		}
	}
	int sum = 0;
	int Recvarr[8];
	MPI_Scatter(&num, 8, MPI_INT, &Recvarr,8,MPI_INT,0 ,MPI_COMM_WORLD);
	printf("My processor id id %d. Received data is ", pid);

	for (int i = 0; i < 8; i++) {
		printf(" %d ", Recvarr[i]);
		sum = sum + Recvarr[i];
	}
	printf("Local sum is %d \n ", sum);

	if (pid != 0) {
		MPI_Send(&sum, 1, MPI_INT, 0, 50, MPI_COMM_WORLD);
	}

	if (pid == 0) {
		for (int j = 1; j < np; j++) {
			int Recv_msg;
			MPI_Recv(&Recv_msg, 1, MPI_INT, j, 50, MPI_COMM_WORLD, &sta);
			Total = Total + Recv_msg;
		}
		printf("Global sum is %d \n", (Total + sum));
	}

	MPI_Finalize();
	return 0;

}
/*
C:\Users\2020asp67\Desktop\CSH3254\Day8\x64\Debug>mpiexec -n 8  Day8.exe
My processor id id 7. Received data is  57  58  59  60  61  62  63  64 Local sum is 484
 My processor id id 2. Received data is  17  18  19  20  21  22  23  24 Local sum is 164
 My processor id id 4. Received data is  33  34  35  36  37  38  39  40 Local sum is 292
 My processor id id 6. Received data is  49  50  51  52  53  54  55  56 Local sum is 420
 My processor id id 1. Received data is  9  10  11  12  13  14  15  16 Local sum is 100
 My processor id id 5. Received data is  41  42  43  44  45  46  47  48 Local sum is 356
 My processor id id 0. Received data is  1  2  3  4  5  6  7  8 Local sum is 36
 Global sum is 2080
My processor id id 3. Received data is  25  26  27  28  29  30  31  32 Local sum is 228
*/