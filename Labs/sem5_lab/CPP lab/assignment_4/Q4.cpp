// Write a Program to compute the total of the matrix using pthread and Mutex lock on global varaible 'total'

// Including header files

#include<bits/stdc++.h>
#include<pthread.h>
#include<unistd.h>
using namespace std;

// Decalaraion
long long total=0;
pthread_mutex_t Lock;

void* helper(void* arg){
	
	int val=*(int*)arg;
	
	// Locking the mutex varaible
	pthread_mutex_lock(&Lock);
	
	// Updating the result
	total+=val;
	
	// Unlocking the mutex variable
	pthread_mutex_unlock(&Lock);
}



int main(){
	
	// Decalaration
	int N,M,r;
	
	cout<<"Enter the row and column of the matrix respectively"<<endl;
	cin>>N>>M;
	
	vector<vector<int> > items(N,vector<int>(M,0));
	
	for(int i=0;i<N;i++){
		for(int j=0;j<M;j++){
			cin>>items[i][j];
		}
	}
	
	// Declaration
	pthread_t process[N][M];
	pthread_attr_t attr;
	
	// attribute initialization
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);
	
	// creation of thread
	for(int i=0;i<N;i++){
		for(int j=0;j<M;j++){
			r=pthread_create(&process[i][j],&attr,helper,&items[i][j]);
			if(r){
				cout<<"Error in creating Thread"<<endl;
				exit(-1);
			}	
		}
	
	}
	
	// Destroying the attribute variable
	pthread_attr_destroy(&attr);
	
	// Joining of pthread
	for(int i=0;i<N;i++){
		for(int j=0;j<M;j++){
			r=pthread_join(process[i][j],NULL);
			if(r){
				cout<<"Error in joining Thread"<<endl;
				exit(-1);
			}	
		}
	}
	
	// Printing the total value of the matrix
	cout<<"Result of the series is "<<total<<endl;
	
	pthread_exit(NULL);
	
	return 0;
}
