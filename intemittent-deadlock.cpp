#include <iostream>
#include <mpi.h>

int main(int argc, char* argv[])
{
	int num_procs, rank; 
	int* send_buff = new int[1000000];
	int* recv_buff = new int[1000000];

	MPI_Init(&argc, &argv);

	MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	for (int i = 0; i < 100000; i++)
	{
		send_buff[i] = i;
	}

	MPI_Status status;

	if (rank == 0)
	{
		for (int i = 0; i < 1000000; i++)
		{
			std::cout << "Sent message was size of: " << i << std::endl;

			MPI_Send(send_buff, i, MPI_INT, 1, 30, MPI_COMM_WORLD);
			MPI_Recv(recv_buff, i, MPI_INT, MPI_ANY_SOURCE, 30, MPI_COMM_WORLD, &status);
		}
	}

	delete[] send_buff;
	delete[] recv_buff;

	MPI_Finalize();

	return 0;
}
