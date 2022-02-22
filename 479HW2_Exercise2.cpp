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
    int token;

    if (rank != 0) {
        MPI_Recv(&token, 1, MPI_INT, (rank - 1) % size, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process %d received token %d from process %d\n", rank, token, (rank - 1) % size);
    } else {
        // Set the token's value if you are process 0
        token = 7;
    }
    MPI_Send(&token, 1, MPI_INT, (rank + 1) % size, 0, MPI_COMM_WORLD);
    // Now process 0 can receive from the last process.
    if (rank == 0) {
        MPI_Recv(&token, 1, MPI_INT, size - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process %d received token %d from process %d\n", rank, token, size - 1);
        endtime = MPI_Wtime();
        printf("\tExecution time of: %f for process of rank %d\n", (endtime-starttime), rank);
    }
    MPI_Finalize();
    return 0;
}