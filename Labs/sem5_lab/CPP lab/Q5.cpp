// Take Employee Information (Name, ID, Designation, Salary of last 5 years) from user and find the % hike in salary of the employee using pthread and Mutex lock (use structure)


// Including header file

#include<bits/stdc++.h>
#include<pthread.h>
#include<unistd.h>
using namespace std;

// Employee structure
struct Employee{
	char name[100];
	int ID;
	char designation[1000];
	vector<int> salary;
};

// Declaration of Elmpoyee
struct Employee info_employee;

// Declaration of mutex variable
pthread_mutex_t Lock;

float hike=0;

void* calculate_hike(void *arg){
	int val=*(int*)arg;

	// Finding percentage hike of the Employee

	// Locking the mutex variable

	pthread_mutex_lock(&Lock);
	// Calculation of percenatage hike
	hike = info_employee.salary[val]-info_employee.salary[val-1];
	hike =  (hike*100)/info_employee.salary[val-1];

	// Giving user the output
	cout<<"Percentage hike of "<<val<<" year is : "<<hike<<endl;


	// Unlocking the mutex variable
	pthread_mutex_unlock(&Lock);

	return arg;

}

int main(){
		

	// Taking Data of Employee
	cout<<"Enter the name of the Employee:  "<<endl;
	cin>>info_employee.name;
	
	cout<<"Enter the Id of the Employee:   "<<endl;
	cin>>info_employee.ID;
	
	cout<<"Enter the Designation of the Employee:  "<<endl;
	cin>>info_employee.designation;
	
	cout<<"Enter the salary of the Employee of 5 years:  "<<endl;
	for(int i=0;i<5;i++){
		int temp;
		cin>>temp;
		info_employee.salary.push_back(temp);
	}

	int id[4];
	for(int i=0;i<4;i++){
		id[i]=i+1;
	}

	// Declaration of Employee
	pthread_t find_hike[4];
	pthread_attr_t attr;

	// Initialization of Attribute
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);

	// Creation of pthread
	for(int i=0;i<4;i++){
		int r1=pthread_create(&find_hike[i],&attr,calculate_hike,&id[i]);
		if(r1){
			cout<<"Error in Creating Process"<<endl;
		}
	}

	// Joining the pthread
	for(int i=0;i<4;i++){
		int r1=pthread_join(find_hike[i],NULL);
		if(r1){
			cout<<"Error in Joining Process"<<endl;
		}
	}
	
}
