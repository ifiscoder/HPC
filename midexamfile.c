#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    MPI_Init(NULL, NULL);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int token =8;
    if (rank < size/2)
    {
        MPI_Recv(&token, 1, MPI_INT, rank -1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("\nProcess %d received sum = %d ", rank, token);
        token += 1;
    }
    else if (rank ==  size/2 )
    {
        token = 0;
    }
    if (rank > size/2)
    {
        MPI_Recv(&token, 1, MPI_INT, rank -1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("\nProcess %d received sum = %d ", rank, token);
        token += 1;
    }
    MPI_Send(&token, 1, MPI_INT, (rank + 1) % size, 0, MPI_COMM_WORLD);
    MPI_Finalize();
}
