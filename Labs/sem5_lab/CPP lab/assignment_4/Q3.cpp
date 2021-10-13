// Write a program to find minimum val

// Including header files

#include<bits/stdc++.h>
#include<pthread.h>
#include<unistd.h>
using namespace std;

// Decalaraion
int minimum=INT_MAX;
pthread_mutex_t Lock;

void* helper(void* arg){
	
	int val=*(int*)arg;
	
	
	// Locking the mutex varaible
	pthread_mutex_lock(&Lock);
	
	// Updating the minimum if needed
	if(minimum > val){
		minimum = val;
	}
	
	// Unlocking the mutex variable
	pthread_mutex_unlock(&Lock);
}



int main(){
	
	// Decalaration
	int N,r;
	
	cout<<"Enter the value of N :"<<endl;
	cin>> N;
	
	vector<int> items(N,0);
	
	cout<<"Now Enter the array: "<<endl;
	for(int i=0;i<N;i++){
		cin>>items[i];
	}
	
	// Declaration
	pthread_t process[N];
	pthread_attr_t attr;
	
	// attribute initialization
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);
	
	// creation of thread
	for(int i=0;i<N;i++){
		r=pthread_create(&process[i],&attr,helper,&items[i]);
		if(r){
			cout<<"Error in creating Thread"<<endl;
			exit(-1);
		}
	}
	
	// Destroying the attribute variable
	pthread_attr_destroy(&attr);
	
	// Joining of pthread
	for(int i=0;i<N;i++){
		r=pthread_join(process[i],NULL);
		if(r){
			cout<<"Error in joining Thread"<<endl;
			exit(-1);
		}
	}
	
	// Printing the minimum value of the array
	cout<<"Minimum value in the array is : "<<minimum<<endl;
	
	pthread_exit(NULL);
	
	return 0;
}
