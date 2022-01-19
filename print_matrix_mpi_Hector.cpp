#include "mpi.h"
#include <iostream>

void print_lines( double submatrix[], int N, int Nrows);

int main(int argc, char **argv)
{
  int N = 0, np = 0, pid = 0;
  MPI_Status status;
  N = std::atoi(argv[1]);
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &np);
  MPI_Comm_rank(MPI_COMM_WORLD, &pid);
  int Nrows = N/np;
  double submatrix [Nrows*N] = {0.0};
  for (int i=0; i < Nrows; i++)
    submatrix[i*N + pid*Nrows + i] = 1.0;
  
  //MPI_Status status;
  int tag=0;
  //printing
  if (0 == pid) {
      print_lines(submatrix, N, Nrows);
      for (int src = 1; src < np; ++src) {
        MPI_Recv(&submatrix[0], Nrows*N, MPI_DOUBLE, src, tag, MPI_COMM_WORLD, &status);
	print_lines(submatrix, N, Nrows);
      }
    }
    else { 
      int dest = 0;
      MPI_Send(&submatrix[0], Nrows*N, MPI_DOUBLE, dest, tag, MPI_COMM_WORLD);
    }

  MPI_Finalize();
  return 0;
}

void print_lines( double submatrix[], int N, int Nrows){
  for(int row=0; row < Nrows; row++){
    for (int col=0; col<N; col++)
	    std::cout << submatrix[row*N + col] << "\t";
    std::cout<<"\n";
  }
}
