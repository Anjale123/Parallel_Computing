#include<mpi.h>
#include<stdio.h>
int main1() {
	int np;
	int pid;
	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	MPI_Comm_rank(MPI_COMM_WORLD, &pid);
	MPI_Status sta;

	int matarr[3][3];
	int vectarr[3];
	int answerarr[3];
	if (pid == 0) {
		matarr[0][0] = 1;
		matarr[0][1] = 2;
		matarr[0][2] = 3;
		matarr[1][0] = 2;
		matarr[1][1] = 1;
		matarr[1][2] = 1;
		matarr[2][0] = 4;
		matarr[2][1] = 2;
		matarr[2][2] = 3;
		vectarr[0] = 5;
		vectarr[1] = 6;
		vectarr[2] = 7;
	}

	printf("\nMy pid %d\n", pid);
	int recvarr[3];
	MPI_Scatter(&matarr, 3, MPI_INT, &recvarr, 3, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Bcast(&vectarr, 3, MPI_INT, 0, MPI_COMM_WORLD);
	printf("Received matrix element");
	for (int i = 0; i < 3; i++) {
		printf("%d ", recvarr[i]);
	
	}
	printf("\n");
	printf("Received vector element");
	for (int i = 0; i < 3; i++) {
		printf("%d ", vectarr[i]);
	}

	printf("\n");
	int rowtotal = 0;
	for (int i = 0; i < 3; i++) {
		rowtotal = rowtotal + (recvarr[i] * vectarr[i]);
	}

	MPI_Gather(&rowtotal, 1, MPI_INT, &answerarr, 1, MPI_INT, 0, MPI_COMM_WORLD);

	if (pid == 0) {
		printf("The resultant matrix");
		for (int i = 0; i < 3; i++) {
			printf("\n%d", answerarr[i]);
		}
	}
	MPI_Finalize();
	return 0;
}

/*C:\Users\2020asp38\Desktop\2020ASP38\CSH3254\Project6\x64\Debug>mpiexec -n 5 Project6.exe

My pid 1
Received matrix element2 1 1
Received vector element5 6 7

My pid 2
Received matrix element4 2 3
Received vector element5 6 7

My pid 3
Received matrix element-858993460 -858993460 -858993460
Received vector element5 6 7

My pid 4
Received matrix element-858993460 -858993460 -858993460
Received vector element5 6 7

My pid 0
Received matrix element1 2 3
Received vector element5 6 7
The resultant matrix
38
23
53*/