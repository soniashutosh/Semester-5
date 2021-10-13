// Quick Sort implementation using OpenMP

// Including header file

#include<bits/stdc++.h>
#include<omp.h>
using namespace std;

// Swapping two elements using pointer
void swap(int* a, int* b) { 
	int t = *a; 
	*a = *b; 
	*b = t; 
} 

// Partitioning of the array elements
int partition(int arr[],int start,int end){

	// Declaration
	int pivot = arr[end];
	int i = (start - 1); 

	// Rearranging the array
	for (int j = start; j <= end - 1; j++) 
	{  
		if (arr[j] < pivot) 
		{ 
			i++;  
			swap(&arr[i], &arr[j]); 
		} 
	} 
	swap(&arr[i + 1], &arr[end]); 
	// returning the respective index
	return (i + 1); 
}

// QuickSort Function using openmp
void quicksort(int arr[],int start,int end){
	// Declaration
	int index;

	if(start<end){
		// Getting the index of pivot by partitioning 
		index=partition(arr,start,end);

		// Parallel sections
		#pragma omp parallel sections
		{
			#pragma omp section
			{
				// Evaluating the left half
				quicksort(arr,start,index-1);
			}
			#pragma omp section
			{	
				// Evaluating the right half
				quicksort(arr,index+1,end);
			}
		}
	}
}

int main(){

	// Declaration
	int N;
	// Taking input the number of elements we wants
	cout<<"Enter the number of Elements you want to Enter"<<endl;
	cin>>N;

	// Declaration of array
	int arr[N];
	cout<<"Enter the array: "<<endl;
	// taking input that array
	for(int i=0;i<N;i++){
		cin>>arr[i];
	}

	// Calling quicksort having parallel code implementation
	quicksort(arr,0,N-1);

	// Printing the sorted array
	cout<<"Array after Sorting is: "<<endl;

	for(int i=0;i<N;i++){
		cout<<arr[i]<<" ";
	}
	cout<<endl;


}
