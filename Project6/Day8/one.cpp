#include<mpi.h>
#include<stdio.h>
int main() {
	int np;
	int pid;
	int Total_sum = 0;

	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	MPI_Comm_rank(MPI_COMM_WORLD, &pid);
	MPI_Status sta;

	int N = 64;
	int num_elements = ((N) / np);
	int start, end;

	if (pid < np - 1) {
		start = (pid * num_elements) + 1;
		end = (start + num_elements) - 1;

	}

	else {
		start = pid * num_elements;
		end = N;
	}

	int local_sum = 0;
	for (int i = start; i <= end; i++) {
		local_sum += 1;
	}

	printf("My pid is %d and the local sum %d \n", pid, local_sum);

	if (pid != 0) {
		MPI_Send(&local_sum, 1, MPI_INT, 0, 50, MPI_COMM_WORLD);
	}

	if (pid == 0) {
		for (int j = 1; j < np; j++) {
			int Recv_msg;
			MPI_Recv(&Recv_msg, 1, MPI_INT, j, 50, MPI_COMM_WORLD,&sta); 
			Total_sum += Recv_msg;
		} 
		printf("Global sum is %d \n", (Total_sum + local_sum));
	}

	MPI_Finalize();
	return 0;
}

/*
C:\Users\DELL\Desktop\Parallel_Computer\Day8\x64\Debug>mpiexec -n 7 Day8.exe
My pid is 1 and the local sum 9
My pid is 2 and the local sum 9
My pid is 6 and the local sum 11
My pid is 3 and the local sum 9
My pid is 4 and the local sum 9
My pid is 5 and the local sum 9
My pid is 0 and the local sum 9
Global sum is 65

C:\Users\DELL\Desktop\Parallel_Computer\Day8\x64\Debug>mpiexec -n 5 Day8.exe
My pid is 3 and the local sum 12
My pid is 2 and the local sum 12
My pid is 4 and the local sum 17
My pid is 1 and the local sum 12
My pid is 0 and the local sum 12
Global sum is 65
*/