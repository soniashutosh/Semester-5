// Merge Sort Implementation using Semaphore


#include<bits/stdc++.h>
#include<pthread.h>
#include<semaphore.h>
#include <unistd.h> 
using namespace std;

// Decalaration
int r1;
long N;
vector<int> array;

// Declaration of Semaphore
sem_t S1,S2;

// sort first part of array

void* sort_first(void *arg){
	N=*(long* )arg;
	int mid=N/2;
	sort(array.begin(),array.begin()+mid);
	sem_post(&S1);
}

void* sort_second(void *arg){
	N=*(long*)arg;
	int mid=N/2;
	sort(array.begin()+mid,array.end());
	sem_post(&S2);
}

void* merge_array(void *arg){
	N=*(long*)arg;
	int mid=N/2;
	sem_wait(&S1);
	sem_wait(&S2);
	vector<int> left,right;
	for(int i=0;i<mid;i++){
		left.push_back(array[i]);
	}
	for(int i=mid;i<N;i++){
		right.push_back(array[i]);
	}
	int m=left.size(),n=right.size();
	int i=0,j=0,k=0;
	while(i<m and j<n){
		if(left[i]<=right[j]){
			array[k]=left[i];
			i++;
			k++;
		}
		else{
			array[k]=right[j];
			j++;
			k++;
		}
	}
	while(i<m){
		array[k]=left[i];
		i++;
		k++;
	}
	while(j<n){
		array[k]=right[j];
		k++;
		j++;
	}
	
	// After merging Final array will be 
	
	cout<<"Final array is : "<<endl;
	for(int i=0;i<N;i++){
		cout<<array[i]<<"  ";
	}
	cout<<endl;
	
}


int main(int argv,char *argc[]){
	
	// Initialization....
	long N;
	cout<<"Enter the total number of array you want to enter"<<endl;
	cin>>N;
	cout<<"Enter the array"<<endl;
	for(int i=0;i<N;i++){
		int num;
		cin>>num;
		array.push_back(num);
	}

	// Declaration of thread
	pthread_t sort_1,sort_2,merge;
	
	// Declaration of attribute......
	pthread_attr_t attr;
	
	// semaphore initialization
	sem_init(&S1,0,0);
	sem_init(&S2,0,0);
	
	// pthread_attr_t initialization
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);
	
	// Creating thread
	void *ptr=&N;
	r1=pthread_create(&sort_1,&attr,sort_first,ptr);
	if(r1){
		cout<<"Error in creating thread"<<endl;
		exit(-1);
	}
	r1=pthread_create(&sort_2,&attr,sort_second,ptr);
	if(r1){
		cout<<"Error in creating thread"<<endl;
		exit(-1);
	}
	r1=pthread_create(&merge,&attr,merge_array,ptr);
	if(r1){
		cout<<"Error in creating thread"<<endl;
		exit(-1);
	}
	
	// destroying the pthread_attr
	pthread_attr_destroy(&attr);
	
	// Joining the thread
	r1=pthread_join(sort_1,NULL);
	if(r1){
		cout<<"Error in joining thread"<<endl;
		exit(-1);
	}
	r1=pthread_join(sort_2,NULL);
	if(r1){
		cout<<"Error in joining thread"<<endl;
		exit(-1);
	}
	r1=pthread_join(merge,NULL);
	if(r1){
		cout<<"Error in joining thread"<<endl;
		exit(-1);
	}
	
	// Exiting thread
	pthread_exit(NULL);
	
	return 0;
}











