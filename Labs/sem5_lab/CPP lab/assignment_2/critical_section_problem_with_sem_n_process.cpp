#include<bits/stdc++.h>
#include<pthread.h>
#include<semaphore.h>
using namespace std;

// Declaration
sem_t semaphore;
int a=0,x=0;

// Critical Section
void critical_section(){
	// Here -1 because lower thread is 2......so to show readability
	cout<<"Critical section of "<<pthread_self()-1<<" thread"<<endl;
	x++;
}

// Process p
void* p1_start(void *arg){
	while(x<30){
		// Non critical section
		a=(a+1)%2;
		sem_wait(&semaphore);
		critical_section();
		sem_post(&semaphore);
	}
}


int main(int argv,char *argc[]){
	
	//declaration
	int r1,N;
	
	// Taking input of number of process
	cout<<"Enter the number you want to Enter"<<endl;
	cin>>N;
	
	// Declaration of thread
	pthread_t process[N];
	
	// Declaration of attribute......
	pthread_attr_t attr;
	
	// Initialization of semaphore
	sem_init(&semaphore,0,1);
	
	// pthread_attr_t initialization
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);
	
	// creation of process
	for(int i=0;i<N;i++){
		r1=pthread_create(&process[i],&attr,p1_start,NULL);
		if(r1){
			cout<<"Error in creating thread"<<endl;
			exit(-1);
		}			
	}
	
	// destroying the pthread_attr
	pthread_attr_destroy(&attr);
	
	// Joining the process
	for(int i=0;i<N;i++){
		r1=pthread_join(process[i],NULL);
		if(r1){
			cout<<"Error in joining thread"<<endl;
			exit(-1);
		}	
	}

	// Exiting pthread
	pthread_exit(NULL);
}
