
// Header file include
#include<bits/stdc++.h>
#include<pthread.h>
using namespace std;

int times=0;
int x=0;

class monitor {
	// Variables
	int s;
	
	// comditon variable for not Zero
	pthread_cond_t notZero;
	
	// mutex variable for synchronization
	pthread_mutex_t condLock;
	
	public:
		// Operation wait
		void wait(){
			pthread_mutex_lock(&condLock);
			if(s==0){
				pthread_cond_wait(&notZero,&condLock);
			}
			s=s-1;
			pthread_mutex_unlock(&condLock);
		}
		
		// Operation Signal
		void signal(){
			pthread_mutex_lock(&condLock);
			s=s+1;
			pthread_cond_signal(&notZero);
			pthread_mutex_unlock(&condLock);
		}
		
		// Constructor
		monitor(){
			// s=k
			s=2;
			pthread_cond_init(&notZero,NULL);
			pthread_mutex_init(&condLock,NULL);
		}
		
		// Destructor
		~monitor(){
			pthread_cond_destroy(&notZero);
			pthread_mutex_destroy(&condLock);
		}
}

// Global Object of Monitor
Sem
;


// Critical Section of the Problem

void critical_section(){
	cout<<"Enters ino critical Section"<<endl;
	x++;
	cout<<"Exiting critical Section of ";
}

//  Main Process  for P and Q

void* process_P(void *arg){
	
	// Loop Forever
	while(times<100){
		// Non Critical Section
		times++;
		// Wait Operation
		Sem.wait();
		cout<<"P ";
		// Critical Section code
		critical_section();
		// Signal Operation
		cout<<"P"<<endl;
		Sem.signal();
	}
	
}

void* process_Q(void *arg){
	
	// Loop Forever
	while(times<100){
		// Non Critical Section
		times++;
		// Wait Operation
		Sem.wait();
		cout<<"Q ";
		// Critical Section code
		critical_section();
		// Signal Operation
		cout<<"Q"<<endl;
		Sem.signal();
	}
	
}

int main(){
	// Declaration
	pthread_t process_p, process_q;
	pthread_attr_t attr;
	
	// Initialization
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);
	
	// Creation
	pthread_create(&process_p,&attr,process_P,NULL);
	pthread_create(&process_q,&attr,process_Q,NULL);
	
	// Joining 
	pthread_join(process_p,NULL);
	pthread_join(process_q,NULL);
	
	// Destroying
	pthread_attr_destroy(&attr);
	pthread_exit(NULL);
	
	return 0;
}



