#include <stdio.h>
#include <mpi.h>

#define TAG 100
#define NITEMS 100

int main(int argc, char** argv)
{

  int rank, recv_rank, nproc, left, right, iitems, sum;
  int values[NITEMS], values_recv[NITEMS];
  MPI_Datatype contig_type;

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &nproc);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  //Set up periodic domain
  left = rank - 1;
  if (left < 0) left = nproc - 1;
  right = rank + 1;
  if (right > nproc - 1) right = 0;

  for (iitems = 0; iitems < NITEMS; ++iitems){
    values[iitems] = rank;
  }

  MPI_Type_contiguous(, , &contig_type);
  MPI_Type_commit(&contig_type);

  if (rank == 0) printf("MPI_Type_contiguous used as send and recieve types\n");

  MPI_Sendrecv(values, , , right, TAG, values_recv, ,
      , left, TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

  MPI_Type_free(&contig_type);

  sum = 0;
  for (iitems = 0; iitems < NITEMS; ++iitems){
    sum += values_recv[iitems];
  }

  printf("Rank %3d got message from rank %3d with total of %5d\n", rank,
      left, sum);

  MPI_Finalize();

}
