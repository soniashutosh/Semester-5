
// Dekkers algorithm implementation

// Free from satrvation
// Mutual Exlusion satsisfied
// Free from deadlock

#include<bits/stdc++.h>
#include<pthread.h>
using namespace std;

int turn=1;
bool wantp=false,wantq=false;
int x=0;

// Critical Section
void critical_section(){
	x++;
}

// process P
void* p(){
	while(1){
		if(x>=50){
			return NULL;
		}
		wantp=true;
		while(wantq){
			if(turn==2){
				wantp=false;
				while(turn!=1){
					
				}
				wantp=true;
			}
		}
		cout<<"Critical Section of P starts here"<<endl;
		critical_section();
		cout<<"Critical Section of P ends here"<<endl;
		turn=2;
		wantp=false;
	}
}

// process Q
void* q(){
	while(1){
		if(x>=50){
			return NULL;
		}
		wantq=true;
		while(wantp){
			if(turn==1){
				wantq=false;
				while(turn!=2){
					
				}
				wantq=true;
			}
		}
		cout<<"Critical Section of Q starts here"<<endl;
		critical_section();
		cout<<"Critical Section of Q ends here"<<endl;
		turn=1;
		wantq=false;
	}
}

// start P
void* start_p(void* arg){
	p();
}

// start q
void* start_q(void* arg){
	q();
}


int main(){
	pthread_t pid,qid;
	// creating two thread
	pthread_create(&pid,NULL,&start_p,NULL);
	pthread_create(&qid,NULL,*start_q,NULL);
	
	// Joining threads
	pthread_join(pid,NULL);
	pthread_join(qid,NULL);
	
	// Exit
	pthread_exit(NULL);
	
	return 0;
}

