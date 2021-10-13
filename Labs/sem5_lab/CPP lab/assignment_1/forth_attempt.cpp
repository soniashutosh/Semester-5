
// Fourth Attempt

// Mutual Exclusion satisfied
// Free from deadlock

// Startvation may happens.

#include<bits/stdc++.h>
#include<pthread.h>
using namespace std;

bool wantp=false,wantq=false;
int x=0;

// Critical Section
void critical_section(){
	x++;
}

// process P
void* p(){
	while(1){
		if(x>=10){
			return NULL;
		}
		wantp=true;
		while(wantq){
			wantp=false;
			wantp=true;
		}
		cout<<"Critical Section of P starts here"<<endl;
		critical_section();
		cout<<"Critical Section of P ends here"<<endl;
		wantp=false;
	}
}

// Process Q
void* q(){
	while(1){
		if(x>=10){
			return NULL;
		}
		wantq=true;
		while(wantp){
			wantq=false;
			wantp=true;
		}
		cout<<"Critical Section of Q starts here"<<endl;
		critical_section();
		cout<<"Critical Section of Q ends here"<<endl;
		wantq=false;
	}
}

// start for join process P
void* start_p(void* arg){
	p();
}

// start for join process Q
void* start_q(void* arg){
	q();
}

int main(){
	pthread_t pid,qid;
	// creating two threads
	pthread_create(&pid,NULL,&start_p,NULL);
	pthread_create(&qid,NULL,&start_q,NULL);
	
	// Joining  threads
	pthread_join(pid,NULL);
	pthread_join(qid,NULL);
	
	// Exit
	pthread_exit(NULL);
	
	return 0;
}

