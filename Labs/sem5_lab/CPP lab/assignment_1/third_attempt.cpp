
// Third attempt

// mutual Exclusion satisfied.

// Not free from deadlock.

#include<bits/stdc++.h>
#include<pthread.h>
using namespace std;

bool wantp=false,wantq=false;
int x=0;

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
		wantp=true;
		while(wantq==true){
			
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
		if(x>=50){
			return NULL;
		}
		wantq=true;
		while(wantp==true){
			
		}
		cout<<"Crtical Section of Q starts here"<<endl;
		critical_section();
		cout<<"Critical Section of Q ends here"<<endl;
		wantq=false;
	}
}

// starting of the process
void* start_p(void* arg){
	p();
}

void* start_q(void* arg){
	q();
}

int main(){
	pthread_t pid,qid;
	// Creating two thread
	pthread_create(&pid,NULL,*start_p,NULL);
	pthread_create(&qid,NULL,*start_q,NULL);
	
	// Joining thread
	pthread_join(pid,NULL);
	pthread_join(qid,NULL);
	
	// Exit
	pthread_exit(NULL);
	
	return 0;
}



