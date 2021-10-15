#include<iostream>
#include<unistd.h>
using namespace std;

int main(int argc, char** argv){
	pid_t pid;
	pid = fork();
	if(pid == 0){
		cout<<"pid="<<pid<<",i'm child process.."<<endl;	

	}else{
		cout<<"pid="<<pid<<",i'm parent process.."<<endl;
		sleep(60);	
	}


	if(pid == 0){
		cout<<"child process end.."<<endl;	
	}else{
		cout<<"parent process end.."<<endl;	
			
	}
	return 0;	

}
