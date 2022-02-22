#include <stdio.h>
#include <mpi.h>

int main( int argc, char *argv[] )

{
int rank, size;
float number;
double starttime, endtime, time;

MPI_Init( &argc, &argv );

MPI_Comm_rank( MPI_COMM_WORLD, &rank );

MPI_Comm_size( MPI_COMM_WORLD, &size );

starttime = MPI_Wtime();
MPI_Request ireq;

MPI_Status istatus;
//Block Single
if (rank == 0) {
    number = 1.1;
    MPI_Send(&number, 1, MPI_FLOAT, 1, 0, MPI_COMM_WORLD);
    printf("Process 0 sent number %f to process 1\n", number);
} else if (rank == 1) {
    MPI_Recv(&number, 1, MPI_FLOAT, 0, 0, MPI_COMM_WORLD, &istatus);
    printf("Process 1 received number %f from process 0\n", number);
    endtime = MPI_Wtime();
    printf("\tExecution time of: %f for process of rank %d\n", (endtime-starttime), rank);
}
printf("Process %d has the number = %f\n", rank, number);
MPI_Finalize();
return 0;
}