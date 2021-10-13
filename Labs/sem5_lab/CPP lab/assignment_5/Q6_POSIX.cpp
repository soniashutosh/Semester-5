// Quick Sort Implementation using Posix Thread

// Including Header File

#include<bits/stdc++.h>
#include<pthread.h>
using namespace std;

// Structure
struct data_set
{
	int start_index;
	int end_index;
	int *data;
};

// Swap function for swaping two Elements
void swap(int* a, int* b)  {  
    int t = *a;  
    *a = *b;  
    *b = t;  
} 

// Partion funciton for making partition in array
int partition(int arr[],int left_index,int right_index){

	// Declaration and initialization
	// chosing pivot element form whcih we make partition 

	// Here pivot is last element of the array
	int pivot= arr[right_index];
	int i=left_index-1;

	// Making array as per requirement 
	// arranging element smaller than pivot on left side and larger then pivot on right side
	for(int j=left_index;j<=right_index-1;j++){
		if(arr[j]<pivot){
			i++;
			swap(&arr[i],&arr[j]);
		}
	}
	swap(&arr[i+1],&arr[right_index]);

	// Returing the partition index
	return i+1;

}


// Quicksort Function for sorting array
void* quick_sort(void *data){

	// Retriving back the data sent from thread
	struct data_set *info = (struct data_set*)data;

	// Declaration of left index
	int left_index,right_index,index;

	// Initialization of left and right index
	left_index=info->start_index;
	right_index=info->end_index;

	// Making recursive call of quick_sort function
	if(left_index<right_index){

		// Declation of pthread and pthread attribute type object
		pthread_attr_t attr;
		pthread_t first_thread;
		pthread_t second_thread;

		// Making two pointers of type data_set for making again call form thread
		struct data_set *info1= new data_set;
		struct data_set *info2= new data_set;

		// Their initialization
		info1->data=info->data;
		info2->data=info->data;

		// Initaization of pthread attribute
		pthread_attr_init(&attr);
		// For setting the set detach state of attribute
		pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);

		// Partitioning the array for recursive call
		index = partition(info->data,left_index,right_index);

		info1->start_index=left_index;
		info1->end_index=index-1;

		// Creating pthread type object and printing the error if any
		if(pthread_create(&first_thread,&attr,quick_sort,info1)){
			cout<<"Error in creating thread "<<endl;
			// Exiting in case of not creation of thread
			exit(-1);
		}

		info2->start_index = index+1;
		info2->end_index = right_index;

		// Creating pthread type object and printing the error if any
		if(pthread_create(&second_thread,&attr,quick_sort,info2)){
			cout<<"Error in craeting thread "<<endl;
			// Exiting in case of not creation of thread
			exit(-1);
		}

		// Joining the threads
		pthread_join(first_thread,NULL);
		pthread_join(second_thread,NULL);
	}

	return NULL;

}

int main(){

	// Declaration of Number of threads
	int N;
	struct data_set *info = new data_set;
	// Taking number of elements as input
	cout<<"Enter number of Elements in the Array : "<<endl;
	cin>>N;

	// Declaration of array
	int A[N];
	// Initialization of array
	cout<<"Enter the array: "<<endl;
	for(int i=0;i<N;i++){
		cin>>A[i];
	}
	// Initialization of structure of data_set type
	info->data=A;
	info->start_index=0;
	info->end_index=N-1;

	// Declaration of pthread object
	pthread_t thread_id;

	// Creating and pthread object and printing the array of any
	if(pthread_create(&thread_id,NULL,quick_sort,info)){
		cout<<"Error in creating thread"<<endl;
		// Exit in case of error
		exit(-1);
	}

	// Joining the pthread object
	int r1=pthread_join(thread_id,NULL);

	// Printing the array if any in case of joining
	if(r1){
		cout<<"Error in Joinging thread"<<endl;
		// Exiting in case of error
		exit(-1);
	}

	// Printing the array after sorting
	cout<<"Sorted Array is: "<<endl;
	for(int i=0;i<N;i++){
		cout<<A[i]<<" ";
	}
	cout<<endl;

	// Exiting from pthread programming
	pthread_exit(NULL);

	return 0;
}


