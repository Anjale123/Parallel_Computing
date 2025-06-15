#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>
int main()
{
	int np;
	int pid;
	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	MPI_Comm_rank(MPI_COMM_WORLD, &pid);
	char arr1[64];
	int Total = 0;
	if (pid == 0)
	{
		arr1[0] = 'W';arr1[1] = 'W';arr1[2] = 'W';arr1[3] = 'W';arr1[4] = 'B';arr1[5] = 'B';arr1[6] = 'B';arr1[7] = 'W';
		arr1[8] = 'W';arr1[9] = 'B';arr1[10] = 'B';arr1[11] = 'B';arr1[12] = 'W';arr1[13] = 'W';arr1[14] = 'B';arr1[15] = 'B';
		arr1[16] = 'W';arr1[17] = 'B';arr1[18] = 'B';arr1[19] = 'W';arr1[20] = 'B';arr1[21] = 'B';arr1[22] = 'W';arr1[23] = 'W';
		arr1[24] = 'W';arr1[25] = 'W';arr1[26] = 'W';arr1[27] = 'B';arr1[28] = 'B';arr1[29] = 'B';arr1[30] = 'B';arr1[31] = 'W';
		arr1[32] = 'W';arr1[33] = 'W';arr1[34] = 'B';arr1[35] = 'B';arr1[36] = 'W';arr1[37] = 'B';arr1[38] = 'B';arr1[39] = 'W';
		arr1[40] = 'W';arr1[41] = 'B';arr1[42] = 'B';arr1[43] = 'B';arr1[44] = 'B';arr1[45] = 'W';arr1[46] = 'W';arr1[47] = 'W';
		arr1[48] = 'W';arr1[49] = 'W';arr1[50] = 'W';arr1[51] = 'W';arr1[52] = 'B';arr1[53] = 'B';arr1[54] = 'B';arr1[55] = 'W';
		arr1[56] = 'W';arr1[57] = 'W';arr1[58] = 'B';arr1[59] = 'B';arr1[60] = 'B';arr1[61] = 'B';arr1[62] = 'W';arr1[63] = 'W';

	}


	char recvarr[8];
	MPI_Scatter(&arr1, 8, MPI_CHAR, &recvarr, 8, MPI_CHAR, 0, MPI_COMM_WORLD);
	printf("My processor id is %d.Received Data is:", pid);
	for (int i = 0;i < 8;i++)
	{
		printf("%c", recvarr[i]);
	}
	printf("\n");
	int balckcounter = 0;
	int whitecounter = 0;
	char encodedstring[16] = { ' ' };
	int j = 0;
	for (int i = 0;i < 8;i++)
	{

		if (recvarr[i] == 'W')
		{
			if (balckcounter > 0)
			{
				char c1 = '0' + balckcounter;
				encodedstring[j] = c1;
				j++;
				encodedstring[j] = 'B';
				j++;
				balckcounter = 0;
			}
			whitecounter++;
		}
		else
		{
			if (whitecounter > 0)
			{
				char c1 = '0' + whitecounter;
				encodedstring[j] = c1;
				j++;
				encodedstring[j] = 'W';
				j++;
				whitecounter = 0;
				//encodedstring=encodedstring+"hi2";
			}
			balckcounter++;
		}

	}
	if (balckcounter > 0)
	{
		char c1 = '0' + balckcounter;
		encodedstring[j] = c1;
		j++;
		encodedstring[j] = 'B';
		j++;
	}
	if (whitecounter > 0)
	{
		char c1 = '0' + whitecounter;
		//printf("character is %c",c1);
		encodedstring[j] = c1;
		j++;
		encodedstring[j] = 'W';
		j++;
	}

	printf("At pid:%d Encoded String:", pid);

	for (int i = 0;i < 16;i++)
	{
		if (encodedstring[i] != ' ')
		{
			printf("%c", encodedstring[i]);
		}
	}
	printf("\n");

	char encoded[8][16];
	MPI_Gather(&encodedstring, 16, MPI_CHAR, &encoded, 16,MPI_CHAR, 0, MPI_COMM_WORLD);


	if (pid == 0)
	{
		for (int j = 0;j < 8;j++)
		{
			printf("\nFrom pid:%d Encoded String:", j);
			for (int i = 0;i < 16;i++)
			{
				if (encoded[j][i] != ' ')
				{
					printf("%c", encoded[j][i]);
				}
			}
			printf("\n");
		}
	}
	MPI_Finalize();
	return 0;
}
/*
My processor id is 2.Received Data is:WBBBWWBB
At pid:2 Encoded String:1W3B2W2B
My processor id is 4.Received Data is:WWWBBBBW
At pid:4 Encoded String:3W4B1W
My processor id is 7.Received Data is:WWWWBBBW
At pid:7 Encoded String:4W3B1W
My processor id is 6.Received Data is:WBBBBWWW
At pid:6 Encoded String:1W4B3W

From pid:1 Encoded String:4W3B1W

From pid:2 Encoded String:1W3B2W2B

From pid:3 Encoded String:1W2B1W2B2W

From pid:4 Encoded String:3W4B1W

From pid:5 Encoded String:2W2B1W2B1W

From pid:6 Encoded String:1W4B3W

From pid:7 Encoded String:4W3B1W

From pid:8 Encoded String:2W4B2W
My processor id is 1.Received Data is:WWWWBBBW
At pid:1 Encoded String:4W3B1W
My processor id is 8.Received Data is:WWBBBBWW
At pid:8 Encoded String:2W4B2W
My processor id is 5.Received Data is:WWBBWBBW
At pid:5 Encoded String:2W2B1W2B1W
My processor id is 3.Received Data is:WBBWBBWW
At pid:3 Encoded String:1W2B1W2B2W



*/