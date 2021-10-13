%%cu

// Including Header files
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
using namespace std;

// Declaration
int size_of_vector=10000;

// CUDA kernel.... 
// Addition of vector
__global__ void vector_Add(int *vector_a,int *vector_b,int *vector_c,int vector_size){

	// Get our Id
	int id = blockIdx.x*blockDim.x+threadIdx.x;

	if(id < vector_size){
		vector_c[id]= vector_a[id]+vector_b[id];
	}

}

void memory_allocating_error(){
	printf("Error in Allocating memory for vectors\n");
	printf("Aborting\n");
}

int main(int argc,char *argv[]){

	// declaration of host input vectors
	int *host_vector_a,*host_vector_b;

	// Declaration of device input vectors
	int *device_vector_a,*device_vector_b;

	// declaration of host output vector
	int *host_vector_result;

	// Declaraton of device output vector
	int *device_vector_result;


	// Allocating memory for each vector in host

	host_vector_a= (int*)malloc(size_of_vector*sizeof(int));
	// printing error if any in creation of vector
	if(host_vector_a==NULL){
		memory_allocating_error();
	}

	host_vector_b= (int*)malloc(size_of_vector*sizeof(int));
	// printing error if any in creation of vector
	if(host_vector_a==NULL){
		memory_allocating_error();
	}

	host_vector_result= (int*)malloc(size_of_vector*sizeof(int));
	// printing error if any in creation of vector
	if(host_vector_a==NULL){
		memory_allocating_error();
	}


	// Allocating memory for each vector in device
	cudaMalloc(&device_vector_a,size_of_vector*sizeof(int));
	cudaMalloc(&device_vector_b,size_of_vector*sizeof(int));
	cudaMalloc(&device_vector_result,size_of_vector*sizeof(int));

	// Initialization 
	for(int i=0;i<size_of_vector;i++){
		// host vector a by random positive value between 0 and 5
		host_vector_a[i]=floor(rand()%5);
		// host vector b by random negative value between 0 and 5
		host_vector_b[i]=-1*floor(rand()%10);

	}

	// Copying host vector to device vector
	cudaMemcpy(device_vector_a,host_vector_a,size_of_vector*sizeof(int),cudaMemcpyHostToDevice);
	cudaMemcpy(device_vector_b,host_vector_b,size_of_vector*sizeof(int),cudaMemcpyHostToDevice);


	int number_of_threads,number_of_blocks;

	// Initializing number of threads per block
	number_of_threads= 1000;

	// Initializing number of blocks
	number_of_blocks=size_of_vector/number_of_threads;

	// Executing kernel...
	vector_Add<<<number_of_blocks,number_of_threads>>> (device_vector_a,device_vector_b,device_vector_result,size_of_vector);

	// Copying device result array back to the host result array
	cudaMemcpy(host_vector_result,device_vector_result,size_of_vector*sizeof(int),cudaMemcpyDeviceToHost);

	// Decalaration of total sum variable
	int total_sum=0;

	for(int i=0;i<size_of_vector;i++){
		total_sum+=host_vector_result[i];
	}

	printf("Final result of both the arrays is : %d\n",total_sum);


	// Releasing device memory
	cudaFree(device_vector_a);
	cudaFree(device_vector_b);
	cudaFree(device_vector_result);

	// Releasing host memory
	free(host_vector_a);
	free(host_vector_b);
	free(host_vector_result);

	return 0;

}

