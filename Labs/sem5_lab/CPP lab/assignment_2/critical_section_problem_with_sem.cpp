#include<bits/stdc++.h>
#include<pthread.h>
#include<semaphore.h>
using namespace std;

// Declaration
pthread_t p1,p2; 
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
	// Declaration ......
	pthread_attr_t attr;
	
	// Initialization of semaphore
	sem_init(&semaphore,0,1);
	
	// pthread_attr_t initialization
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);
	
	// creation of process
	int r1=pthread_create(&p1,&attr,p1_start,NULL);
	if(r1){
		cout<<"Error in creating thread"<<endl;
		exit(-1);
	}
	r1=pthread_create(&p2,&attr,p1_start,NULL);
	if(r1){
		cout<<"Error in creating thread"<<endl;
		exit(-1);
	}
	
	// destroying the pthread_attr
	pthread_attr_destroy(&attr);
	
	// Joining the process
	r1=pthread_join(p1,NULL);
	if(r1){
		cout<<"Error in joining thread"<<endl;
		exit(-1);
	}
	r1=pthread_join(p2,NULL);
	if(r1){
		cout<<"Error in joining thread"<<endl;
		exit(-1);
	}
	
	// Exiting pthread
	pthread_exit(NULL);
}
