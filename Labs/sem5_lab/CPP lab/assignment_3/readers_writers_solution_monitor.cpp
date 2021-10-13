
// Header file include
#include<bits/stdc++.h>
#include<pthread.h>
#include<unistd.h>
using namespace std;

int items=10;

class monitor {
	// number of readers
	int readers;
	
	// number of writers
	int writers;
	
	// number of readers waiting 
	int waitreaders;
	
	// number of writers waiting
	int waitwriters;
	
	// condition variable for readers
	pthread_cond_t canread;
	
	// condtion variable for writers
	pthread_cond_t canwrite;
	
	// mutex for synchornization
	pthread_mutex_t condLock;
	
	public:
		
		// Start read Function
		void start_read(int i){
			
			pthread_mutex_lock(&condLock);
			
			if(writers == 1 and waitwriters > 0){
				waitreaders++;
				pthread_cond_wait(&canread,&condLock);
				waitreaders--;
			}
			
			readers++;
			cout<<"Reader "<< i <<" is reading"<<endl;
			
			pthread_mutex_unlock(&condLock);
			
			pthread_cond_broadcast(&canread);
			
		}
		
		// End read function
		void end_read(int i){
			
			pthread_mutex_lock(&condLock);
			
			if(--readers == 0){
				pthread_cond_signal(&canwrite);
			}
			
			pthread_mutex_unlock(&condLock);
			
		}
		
		// Start write Function
		void start_write(int i){
			
			pthread_mutex_lock(&condLock);
			
			if(writers == 1 or readers > 0){
				++waitwriters;
				pthread_cond_wait(&canwrite,&condLock);
				--waitwriters;
			}
			writers = 1;
			cout<<"Writer "<<i<<" is writing"<<endl;
			
			pthread_mutex_unlock(&condLock);
			
		}
		
		// End Write Function
		void end_write(int i){
			
			pthread_mutex_lock(&condLock);
			
			writers =0;
			
			if(waitreaders > 0){
				pthread_cond_signal(&canread);
			}
			else{
				pthread_cond_signal(&canwrite);
			}
			
			pthread_mutex_unlock(&condLock);
			
		}
		
		// constrcutor
		monitor(){
			readers=0;
			writers=0;
			waitreaders=0;
			waitwriters=0;
			
			pthread_cond_init(&canread,NULL);
			pthread_cond_init(&canwrite,NULL);
			
			pthread_mutex_init(&condLock,NULL);
		}
		
		// destuctor
		~monitor(){
			pthread_cond_destroy(&canread);
			pthread_cond_destroy(&canwrite);
			
			pthread_mutex_destroy(&condLock);
		}
	
}

// Global Object of monitor class handles readers and writers

library
;

// Reader funciton

void* reader(void *arg){
	
	int c=0;
	int i = *(int*)arg;
	
	// Read items
	while(c < items){
		sleep(1);
		library.start_read(i);
		library.end_read(i);
		c++;
	}
	
}


// Writers function

void* writer(void *arg){
	
	int c=0;
	int i = *(int*)arg;
	
	while(c < items){
		sleep(1);
		library.start_write(i);
		library.end_write(i);
		c++;
	}
	
}

int main(){
	
	// Declaration
	pthread_t read[items] ,write[items];
	pthread_attr_t attr;
	int id[items];
	
	// Initalization
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);
	
	for(int i=0;i<items;i++){
		id[i]= i;
		
		// Creating thread
		
		// for readers
		pthread_create(&read[i],&attr,reader,&id[i]);
		
		// for writers
		pthread_create(&write[i],&attr,writer,&id[i]);
	}
	
	// Joining threads
	
	// readers
	for(int i=0;i<items;i++){
		pthread_join(read[i],NULL);
	}
	
	// writers
	for(int i=0;i<items;i++){
		pthread_join(write[i],NULL);
	}
	
	// destroying
	
	pthread_attr_destroy(&attr);
	pthread_exit(NULL);
	
	return 0;
}

