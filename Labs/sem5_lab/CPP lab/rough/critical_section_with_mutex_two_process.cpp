#include<bits/stdc++.h>
#include<pthread.h>
#include<mpi.h>
using namespace std;

pthread_t p1,p2;
// pthread_mutex variable initialization
pthread_mutex_t sem;
// variable initialization
int a=0,x=0;

// Critical Section
void critical_section(){
	x++;
}

// Process p
void* p1_start(void *arg){
	while(x<20){
		// Non critical section
		a=(a+1)%2;
		pthread_mutex_lock(&sem);
		cout<<"P1 citical section starts here"<<endl;
		critical_section();
		cout<<"P1 critcal sections ends here"<<endl;
		pthread_mutex_unlock(&sem);
	}
}

// Process q
void* p2_start(void *arg){
	while(x<20){
		// Non critical section
		a=(a+1)%2;
		pthread_mutex_lock(&sem);
		cout<<"P2 critical section starts here"<<endl;
		critical_section();
		cout<<"P2 critcal section ends here"<<endl;
		pthread_mutex_unlock(&sem);
	}


}

int main(int argc,char *argv[]){
	// Initialization ......
	pthread_attr_t attr;

	// Pthread_mutex_intialization...
	pthread_mutex_init(&sem,NULL);

	// pthread_attr_t initialization
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);

	// creation of process
	int r1=pthread_create(&p1,&attr,p1_start,NULL);
	if(r1){
		cout<<"Error in creating attribute"<<endl;
		exit(-1);
	}
	r1=pthread_create(&p2,&attr,p2_start,NULL);
	if(r1){
		cout<<"Error in creating attribute"<<endl;
		exit(-1);
	}

	// destroying the pthread_attr
	pthread_attr_destroy(&attr);

	// Joining the process
	r1=pthread_join(p1,NULL);
	if(r1){
		cout<<"Error in joining attribute"<<endl;
		exit(-1);
	}
	r1=pthread_join(p2,NULL);
	if(r1){
		cout<<"Error in joining attribute"<<endl;
		exit(-1);
	}

	//Pthread mutex variable destroy
	pthread_mutex_destroy(&sem);

	// Exiting pthread
	pthread_exit(NULL);
}

