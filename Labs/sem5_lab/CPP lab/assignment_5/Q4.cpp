// Write MPI program to find sum of n integers on a Parallel Computing System and use MPI collective blocking communication library calls.

// Including header file

#include <mpi.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <time.h>
using namespace std;

// Main Funciton starting....
int main(int argc, char *argv[])
{ 
    int number_of_elements;
    int *data=NULL;
    int chunk_size,own_chunk_size;
    int *chunk;
    double time_taken;
    MPI_Status status;
    int result=0;

    if(argc!=2){
        printf("Desired number of arguments are not thier in argv....\n");
        printf("1 number required...\n");
        exit(-1);
    }

    int number_of_process,rank_of_process;
    int rc=MPI_Init(&argc,&argv);

    if(rc!=MPI_SUCCESS){
        printf("Error in creating MPI program.\n Terminating......\n");
        MPI_Abort(MPI_COMM_WORLD,rc);
    }

    MPI_Comm_size(MPI_COMM_WORLD,&number_of_process);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank_of_process);

    if(rank_of_process==0){

        // number of elements
    	number_of_elements=atoi(argv[1]);
        // Computing chunk size
        chunk_size= (number_of_elements%number_of_process==0) ? number_of_elements/number_of_process : number_of_elements/(number_of_process-1);

        data = (int *)malloc(number_of_process*chunk_size * sizeof(int));

        for(int i=0;i<number_of_elements;i++){
            data[i]=i+1;
        }

        // Padding data with zero
        for(int i=number_of_elements;i<number_of_process*chunk_size;i++){
            data[i]=0;
        }

    }

    // Blocks all process until reach this point
    MPI_Barrier(MPI_COMM_WORLD);

    // Starts Timer
    time_taken -= MPI_Wtime();

    // BroadCast the Size to all the process from root process
    MPI_Bcast(&number_of_elements,1,MPI_INT,0,MPI_COMM_WORLD);

    // Computing chunk size
    chunk_size= (number_of_elements%number_of_process==0) ? number_of_elements/number_of_process : number_of_elements/(number_of_process-1);

    // Calculating total size of chunk according to bits
    chunk=(int *)malloc(chunk_size * sizeof(int));

    // Scatter the chuck size data to all process
    MPI_Scatter(data,chunk_size,MPI_INT,chunk,chunk_size,MPI_INT,0,MPI_COMM_WORLD);
    free(data);
    data=NULL;

    // Compute size of own chunk and then sort them using quick sort

    own_chunk_size = (number_of_elements >= chunk_size*(rank_of_process+1)) ? chunk_size : (number_of_elements - chunk_size*rank_of_process);

    // Calculating the result of each process
    for(int i=0;i<own_chunk_size;i++){
    	result+=chunk[i];
    }

    if(rank_of_process==0){
    	// Receiving their sum and the add it to main result
    	for(int i=1;i<number_of_process;i++){
    		int temp;
    		MPI_Recv(&temp,1,MPI_INT,i,0,MPI_COMM_WORLD,&status);
    		result+=temp;
    	}
    }
    else{
    	// Sending of sum of this part to desired process
    	MPI_Send(&result,1,MPI_INT,0,0,MPI_COMM_WORLD);
    }


    // Stop the timer
    time_taken+=MPI_Wtime();

    // Opening the other file as taken form input and writing it to the file and giving it as the output
    if(rank_of_process==0){
    	printf("Sum of first n natural numbers is: %d\n",result);
        printf("Number of elements %d operated on %d procs: %f secs\n", number_of_elements, number_of_process, time_taken);
    }

    MPI_Finalize();

    return 0;
}   

