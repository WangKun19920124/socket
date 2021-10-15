#include<iostream>
#include<unistd.h>
#include<sys/wait.h>
#include<cstring>
using namespace std;

int main(int argc, char** argv)
{
	pid_t pid;
	pid = fork();
	int status;
	if(pid == 0)
	{
		sleep(30);
		return 1;
	}
	else
	{
		while(waitpid(-1, &status, WNOHANG) == 0)
		{
			sleep(5);
			cout<<"sleep 5s"<<endl;	
		}
		if(WIFEXITED(status) == true){
			cout<<"child process return value="<<WEXITSTATUS(status)<<endl;		
		}
		return 0;
		
	}		


}
