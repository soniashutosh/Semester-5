#include<stdio.h>
#include<math.h>
#include<mpi.h>
#include <stdlib.h> 


int main(int argc, char** argv){  
    
    int number_of_elements;
    int *data=NULL;
    int chunk_size,own_chunk_size;
    int *chunk;
    FILE *file=NULL;
    double time_taken;
    MPI_Status status;


    if(argc!=2){
        printf("Desired number of arguments are not thier in argv....\n");
        printf("1 files containing inputs...\n");
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

        // Opening the file
        file=fopen(argv[1],"r");

        // Printing Error message if any
        if(file==NULL){
            printf("Error in opening file\n");
            exit(-1);
        }

        // Reading number of Elements in file ... First Value in file is number of Elements
        printf("Reading number of Elements From file ....\n");
        fscanf(file,"%d",&number_of_elements);
        printf("Number of Elements in the file is %d \n",number_of_elements );

        // Computing chunk size
        chunk_size= (number_of_elements%number_of_process==0) ? number_of_elements/number_of_process : number_of_elements/(number_of_process-1);

        data = (int *)malloc(number_of_process*chunk_size * sizeof(int));
        // Reading the rest elements in which operation is being performed
        printf("Reading the array from the file.......\n");
        for(int i=0;i<number_of_elements;i++){
            fscanf(file,"%d",&data[i]);
        }

        // Printing the array read from file
        printf("Elements in the array is : \n");
        for(int i=0;i<number_of_elements;i++){
            printf("%d  ",data[i]);
        }
        printf("\n");


        fclose(file);
        file=NULL;

    }

    // Blocks all process until reach this point
    MPI_Barrier(MPI_COMM_WORLD);

    int prefix[number_of_elements];

    for(int i=0;i<number_of_process;i++){

        if(i==0){
            prefix[i]=data[i];
            MPI_Send(&prefix[i],1,MPI_INT,i+1,0,MPI_COMM_WORLD);
        }
        else if(i==number_of_process-1){
            int temp;
            MPI_Recv(&temp,1,MPI_INT,i-1,0,MPI_COMM_WORLD,&status);
            prefix[i]=temp+data[i];
        }
        else{
            int temp;
            MPI_Recv(&temp,1,MPI_INT,i-1,0,MPI_COMM_WORLD,&status);
            prefix[i]=temp+data[i];
            MPI_Send(&prefix[i],1,MPI_INT,i+1,0,MPI_COMM_WORLD);
        }
        printf("%d ",prefix[i] );
    }

    for(int i=0;i<number_of_process;i++){
        printf("%d ",prefix[i] );
    }

    MPI_Finalize();
    return 0;
}