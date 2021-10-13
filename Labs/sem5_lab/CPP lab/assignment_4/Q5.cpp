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

int main(){
	
	int number_of_employee;
	// Number of Employee
	cout<<"Enter the number of Employee for which you want to find the percentage hike: "<<endl;
	cin>>number_of_employee;
	
	while(number_of_employee--){
		
		struct Employee info_employee;
		
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
			info_employee.salary[i]=temp;
		}
		
		
		
	}
	
}
