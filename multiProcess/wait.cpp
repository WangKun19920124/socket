#include<iostream>
#include<unistd.h>
#include<sys/wait.h>
#include<cstring>
using namespace std;

int main(int argc, char** argv){
	pid_t pid = fork();
	int status;
	
	if(pid == 0){
		return 1;	
	}else{
		cout<<"child process:"<<pid<<endl;
		
		pid = fork();
		if(pid == 0){
			return 2;
				
		}else{
			cout<<"child process:"<<pid<<endl;
			
			wait(&status);
			if(WIFEXITED(status)){
				cout<<"child process"<<WEXITSTATUS(status)<<" is killed..."<<endl;

			}
			wait(&status);
			if(WIFEXITED(status)){
				cout<<"child process"<<WEXITSTATUS(status)<<" is killed..."<<endl;

			}
			sleep(60);
			return 0;	
		}	
	}



}
