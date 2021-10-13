
// Header file include
#include<bits/stdc++.h>
#include<pthread.h>
#include<unistd.h>
using namespace std;

int times=0;

class Monitor{
	// buffer for the store
	int buffer=0;
	
	// capacity of the store
	int capacity;
	
	// condtion variable for Not Empty and Not Full
	pthread_cond_t notEmpty,notFull;
	
	// mutex variable for synchorization
	pthread_mutex_t condLock;
	
	public:
		
		// Append operation
		void append(){
			pthread_mutex_lock(&condLock);
			cout<<"Producer is producing"<<endl;
			// Wait for buffer to not Full
			if(buffer==capacity){
				pthread_cond_wait(&notFull,&condLock);
			}
			buffer++;
			pthread_cond_signal(&notEmpty);
			pthread_mutex_unlock(&condLock);
		}
		
		// Take operation
		void take(){
			pthread_mutex_lock(&condLock);
			cout<<"Consumer is taking"<<endl;
			// Wait for Buffer to not Empty
			if(buffer==0){
				pthread_cond_wait(&notEmpty,&condLock);
			}
			buffer--;
			pthread_cond_signal(&notFull);
			pthread_mutex_unlock(&condLock);
		}
		
		
		// Constructor
		Monitor(){
			capacity=25;
			pthread_cond_init(&notEmpty,NULL);
			pthread_cond_init(&notFull,NULL);
			pthread_mutex_init(&condLock,NULL);
		}
		
		// Destructor
		~Monitor(){
			pthread_cond_destroy(&notEmpty);
			pthread_cond_destroy(&notFull);
			pthread_mutex_destroy(&condLock);
		}
		
}
// Global variable of monitor where producer is storing and consumer is taking.....
store;


// Produce Function
void* produce(void *arg){
	while(times<1000){
		sleep((rand()%100)*0.01);
		store.append();
		times++;
	}
}


// Consumr Function
void* consume(void *arg){
	while(times<1000){
		sleep((rand()%100)*0.02);
		store.take();
		times++;
	}
}


int main(){
	
	// Declaration...
	
	pthread_t producer, consumer;
	pthread_attr_t attr;
	
	// Initialization
	
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);
	
	// Creation
	pthread_create(&producer,&attr,produce,NULL);
	pthread_create(&consumer,&attr,consume,NULL);
	
	// Destroying
	pthread_attr_destroy(&attr);
	pthread_exit(NULL);
	
	return 0;
	
	
}

