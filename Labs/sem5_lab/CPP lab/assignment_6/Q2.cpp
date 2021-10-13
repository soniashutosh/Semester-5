%%cu

// Including Header files
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
using namespace std;

#define tile_width 2

int width=6;


// Non sharable matrix multiplication
__global__ void square_matrix_multiply(int *matrix_a ,int *matrix_b ,int *matrix_result ,int width)
{

	// Calculate row and column
	int col= tile_width*blockIdx.x + threadIdx.x;
	int row= tile_width*blockIdx.y + threadIdx.y;


	// Multiplying and storing the result
	for(int k=0;k<width;k++){
		matrix_result[row*width + col] += matrix_a[row*width + k] * matrix_b[k*width + col];
	}

}


int main(int argc,char *argv[]){

	// declaration of host matrix input
	int host_matrix_a[width][width],host_matrix_b[width][width];

	// Declaration of device matrix input
	int *device_matrix_a,*device_matrix_b;

	// declaration of host matrix result
	int host_matrix_result[width][width];

	// Declaration of device matrix result
	int *device_matrix_result;

	//Allocating memory for device matrix
	cudaMalloc(&device_matrix_a,width*width*sizeof(int));
	cudaMalloc(&device_matrix_b,width*width*sizeof(int));
	cudaMalloc(&device_matrix_result,width*width*sizeof(int));

	// Initialization of host input matrix

	for(int i=0;i<width;i++){
		for(int j=0;j<width;j++){
			host_matrix_a[i][j]=1;
			host_matrix_b[i][j]=2;
		}
	}

	cudaMemcpy(device_matrix_a,host_matrix_a,width*width*sizeof(int),cudaMemcpyHostToDevice);
	cudaMemcpy(device_matrix_b,host_matrix_b,width*width*sizeof(int),cudaMemcpyHostToDevice);

	dim3 dimGrid(width/tile_width,width/tile_width,1);
	dim3 dimBlock(tile_width,tile_width,1);


	square_matrix_multiply<<<dimGrid,dimBlock>>> (device_matrix_a,device_matrix_b,device_matrix_result,width);

	cudaMemcpy(host_matrix_result,device_matrix_result,width*width*sizeof(int),cudaMemcpyDeviceToHost);

	for(int i=0;i<width;i++){
		for(int j=0;j<width;j++){
			printf("%d  ",host_matrix_result[i][j]);
		}
		printf("\n");
	}

	cudaFree(device_matrix_a);
	cudaFree(device_matrix_b);
	cudaFree(device_matrix_result);

	return 0;


}