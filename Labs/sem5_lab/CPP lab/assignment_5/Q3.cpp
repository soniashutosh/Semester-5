//Write an OpenMP program to find Sum of Natural Numbers using OpenMP Parallel FOR directive and REDUCTION clause.

//// Including Header File

#include<bits/stdc++.h>
#include<omp.h>
#include<unistd.h>
using namespace std;

int main()
{
	// Taking input Upto which we want the sum

	// Declaration
	int N,i,chunk;
	cout<<"Enter the number upto which you want to get sum"<<endl;
	cin>>N;

	// Value of all the items
	int items[N];
	chunk = 2;

	// Just setting the items value of we can do directly but for sake we are 
	// filling items in parallel
	#pragma omp parallel for
		for(i=0;i<N;i++)
			items[i]=i+1;

	int result=0;

	// Just getting sum in reduction clause
	#pragma omp parallel for reduction(+ : result)
		for(i=0;i<N;i++)
			result+=items[i];

	cout<<"Result of First N Natural Number is : "<<result<<endl;



	
	return 0;
}
