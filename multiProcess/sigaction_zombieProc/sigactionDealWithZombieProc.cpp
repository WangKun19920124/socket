#include<iostream> 
#include<signal.h> 
#include<wait.h> 
#include<unistd.h>
using namespace std;

void child_proc(int sig)
{
	int status;
	if(sig == SIGCHLD){
		waitpid(-1, &status, WNOHANG);		
	}
	if(WIFEXITED(status)){
		cout<<"child zombie proc has been destroyed.."<<endl;	
		cout<<"child proc return val = "<<WEXITSTATUS(status)<<endl;	

	}	
}
int main(int argc, char** argv){
	struct sigaction act;
	act.sa_handler = child_proc;
	act.sa_flags = 0;

	sigaction(SIGCHLD, &act, 0);

	pid_t pid = fork();

	if(pid == 0){
		cout<<"i'm child proc.."<<endl;
		sleep(5);
		return 1;	
	}else{
		cout<<"child proc id = "<<pid<<endl;
		pid = fork();

		if(pid == 0){
			cout<<"i'm child proc.."<<endl;
			sleep(5);
			return 2;	
		}else{
			cout<<"child proc id = "<<pid<<endl;
			for(int i=0;i<3;i++){
				cout<<"wait.."<<endl;
				sleep(5);	
			
			}	
		
		}	
	
	}
}
