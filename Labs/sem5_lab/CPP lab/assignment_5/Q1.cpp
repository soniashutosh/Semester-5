// Write an OpenMP program to print each thread’s unique identifier.

// Including Header File

#include<bits/stdc++.h>
#include<omp.h>
#include<unistd.h>
using namespace std;


int main(){

	// Taking number of threads
	int number_of_threads;

	cout<<"Enter number of threads: "<<endl;
	cin>>number_of_threads;

	if(number_of_threads>10){
		cout<<"Number of threads are large ...\n Exiting process... Start again"<<endl;
		exit(-1);
	}

	// Setting number of threads for execution
	omp_set_num_threads(number_of_threads);

	#pragma omp parallel
	{
		int threadid = omp_get_thread_num();
		cout<<"Hello World. My thread id is: "<<threadid<<endl;
	}

	return 0;

}
