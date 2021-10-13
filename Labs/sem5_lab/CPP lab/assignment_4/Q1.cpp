#include<bits/stdc++.h>
#include<pthread.h>
#include<semaphore.h>
using namespace std;
#define N 5
void* hello_world(void *arg){
	int i = *(int*)arg;
	
	cout<<"Hello World From thread "<<i+1<<endl;
}
int main(){
	int index[N];
	for(int i=0;i<N;i++){
		index[i]=i;
	}	
	pthread_t process[N];
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);
	for(int i=0;i<N;++i){
		pthread_create(&process[i],&attr,hello_world,&index[i]);
	}
	pthread_attr_destroy(&attr);
	for(int i=0;i<N;i++){
		pthread_join(process[i],NULL);
	}
	pthread_exit(NULL);
	return 0;	
}
