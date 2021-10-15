#include<iostream>
#include<unistd.h>
using namespace std;

int gval = 10;
int main(int argc, char** argv){
	int val = 20;
	pid_t pid;
	pid = fork();
	if(pid == 0){
		gval--;
		val--;
		cout<<"child process_"<<pid<<",gval="<<gval<<",val="<<val<<endl;	
	}else{
		gval++;
		val++;
		cout<<"parent process_"<<pid<<",gval="<<gval<<",val="<<val<<endl;	
	}

	return 0;	

}
