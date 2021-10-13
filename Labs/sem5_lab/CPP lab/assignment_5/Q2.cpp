// Write MPI program to broadcast message "Hello world" to all the processes.

// Including Header File

#include <mpi.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
using namespace std;

// Main Function
int main(int argc,char *argv[]){

	int id=2,myrank;

	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&myrank);
	printf("Identifier value in starting = %d for process = %d\n",id,myrank);

	if(myrank==1){
		id=12;
	}
	MPI_Bcast(&id,1,MPI_INT,1,MPI_COMM_WORLD);

	printf("Process %d after Broadcasting the message. The ID becomes : %d \n",myrank,id);

	MPI_Finalize();

	return 0;
}

