
// First attempt
// Pros
// Mutual Exclusion holds
// Free from deadlock

//cons
// If one process dies other gets bolcked.

#include <bits/stdc++.h>
#include <pthread.h>
using namespace std;

int turn = 1;
int x=0;

// Critical Section
void* critical_section(){
	x++;
}

// Process P
void* p(){
	while(1){
		if(x>=50){
			return NULL;
		}
		cout<<"In process p"<<endl;
		while(turn!=1){
			
		}
		critical_section();
		turn=2;
	}
}

// Process Q
void* q(){
	while(1){
		if(x>=50){
			return NULL;
		}
		cout<<"In process q"<<endl;
		while(turn!=2){
			
		}
		critical_section();
		turn=1;
	}
}

// Loop forever type section
void* start_p(void* arg){
	p();
}

void* start_q(void* arg){
	q();
}

int main(){
	
	// creation of two thread
	pthread_t pid,qid;
	pthread_create(&pid,NULL,&start_p,NULL);
	pthread_create(&qid,NULL,&start_q, NULL);
	
	// joining of thread
	pthread_join(pid,NULL);
	pthread_join(qid,NULL);
	
	// Exit
	pthread_exit(NULL);
	
	pthread_exit(NULL);
	
}

