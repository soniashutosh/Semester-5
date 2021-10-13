#include<bits/stdc++.h>
#include<pthread.h>
#include<unistd.h>
using namespace std;
long long result=0;
pthread_mutex_t Lock;

void* helper(void* arg){	
	int val=*(int*)arg;
	int term = val*val;
	pthread_mutex_lock(&Lock);
	result+=term;
	pthread_mutex_unlock(&Lock);
}



int main(){
	int N,r;
	cout<<"Enter the value of N upto which you want summation "<<endl;
	cin>> N;
	vector<int> items(N,0);
	for(int i=0;i<N;i++){
		items[i]=i+1;
	}
	pthread_t process[N];
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);
	for(int i=0;i<N;i++){
		r=pthread_create(&process[i],&attr,helper,&items[i]);
		if(r){
			cout<<"Error in creating Thread"<<endl;
			exit(-1);
		}
	}
	pthread_attr_destroy(&attr);
	for(int i=0;i<N;i++){
		r=pthread_join(process[i],NULL);
		if(r){
			cout<<"Error in joining Thread"<<endl;
			exit(-1);
		}
	}
	cout<<"Result of the series is "<<result<<endl;
	pthread_exit(NULL);
	return 0;
}
