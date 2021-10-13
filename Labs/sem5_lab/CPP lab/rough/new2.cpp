#include<stdio.h>
#include<mpi.h>

#define BUFFER_SIZE 200

int main(int argc, char *argv[])
{
    int  MyRank, Numprocs, Destination, Source, iproc;
    int  Destination_tag, Source_tag;
    int  Root = 0, len_name ;
    char proc_name[100], proc_name_root[100];
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &MyRank);
    MPI_Comm_size(MPI_COMM_WORLD, &Numprocs);

    if(MyRank != 0)
    {
        char send[BUFFER_SIZE];
        sprintf(send, "Hello World");
        Destination = Root;
        Destination_tag = 0;
        MPI_Get_processor_name(proc_name, &len_name);

        printf("\n Process with Rank %d [Node : %s] Sending MESSAGE \"%s\" to Process with Rank %d \n\n", MyRank, proc_name, send, Root);

        MPI_Send(send, BUFFER_SIZE, MPI_CHAR, Destination, Destination_tag, MPI_COMM_WORLD);
    }

    else
    {
        char recv[BUFFER_SIZE];

        for(iproc = 1; iproc<Numprocs; iproc++)
        {
            Source = iproc;
            Source_tag = 0;
            MPI_Get_processor_name(proc_name_root, &len_name);

            MPI_Recv(recv, BUFFER_SIZE, MPI_CHAR, Source, Source_tag, MPI_COMM_WORLD, &status);

            printf("\n Process with Rank %d [Node : %s] Received MESSAGE \"%s\" from Process with Rank %d\n\n", Root, proc_name_root, recv, iproc);
        }
    }

    MPI_Finalize();
}





