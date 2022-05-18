#include <stdio.h> 
#include <mpi.h> 
int main(int argc, char *argv[]) 
{ 
 int my_rank, size; 
 int snd_buf, rcv_buf; 
 int right, left; 
 int sum, i; 
 MPI_Status status; 
 MPI_Request request; 
 MPI_Init(&argc, &argv); 
 MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); 
 MPI_Comm_size(MPI_COMM_WORLD, &size); 
 right = (my_rank + 1) % size; 
 left = (my_rank - 1 + size) % size;
 sum = 0; 
 snd_buf = my_rank; 
 for (i = 0; i < size; i++) 
 { 
 MPI_Isend(&snd_buf, 1, MPI_INT, right, 0, MPI_COMM_WORLD, &request) ; 
 MPI_Recv(&rcv_buf, 1, MPI_INT, left, 0, MPI_COMM_WORLD, &status);  MPI_Wait(&request, &status); 
 snd_buf = rcv_buf; 
 sum += rcv_buf; 
 } 
 printf("Process %i:\tSum = %i\n", my_rank, sum); 
 MPI_Finalize(); 
 return 0; 
} 
