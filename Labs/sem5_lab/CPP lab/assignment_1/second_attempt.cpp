
// Second Attempt

// pros
// No deadlock .
// Free from starvation.

// cons
// Mutual Exclusion principle not holds.

#include<bits/stdc++.h>
#include<pthread.h>
using namespace std;

int x=0;
bool wantp=false,wantq=false;

// Critical Section
void critical_section(){
	x++;
}

// Process p
void* p(){
	while(1){
		if(x>=50){
			return NULL;
		}
		while(wantq==true){
			
		}
		wantp=true;
		cout<<"Critical Section of P starts"<<endl;
		critical_section();
		cout<<"Critical Section of P ends"<<endl;
		wantp=false;
	}
}

// Process q
void* q(){
	while(1){
		if(x>=50){
			return NULL;
		}
		while(wantp==true){
			
		}
		wantq=true;
		cout<<"Critical Section of Q starts"<<endl;
		critical_section();
		cout<<"Critical Section of Q ends"<<endl;
		wantq=false;
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
	pthread_t pid,qid;
	// creating two thread
	pthread_create(&pid,NULL,&start_p,NULL);
	pthread_create(&qid,NULL,&start_q,NULL);
	
	// joining of thread
	pthread_join(pid,NULL);
	pthread_join(qid,NULL);
	
	// Exit
	pthread_exit(NULL);
	
	return 0;
}


