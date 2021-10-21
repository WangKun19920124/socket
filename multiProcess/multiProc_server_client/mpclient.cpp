#include<iostream>
#include<cstring>
#include<string>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<signal.h>
#include<wait.h>

using namespace std;

#define BUF_SIZE 1024

void child_proc(int sig)
{
	int status;
	if(sig==SIGCHLD){
		waitpid(-1, &status, WNOHANG);
	}
	if(WIFEXITED(status)){
		cout<<"child proc destroyed.."<<endl;
		cout<<"child proc return val= "<<WEXITSTATUS(status)<<endl;	
	}
}

int main(int argc, char** argv)
{
	if(argc!=3){
		cout<<"usage: "<<argv[1]<<"<IP> <port>"<<endl;	
	}
	char buf[BUF_SIZE];

	int sock_clnt = socket(PF_INET, SOCK_STREAM, 0);
	struct sockaddr_in addr_serv;
	memset(&addr_serv, 0, sizeof(addr_serv));
	addr_serv.sin_family = AF_INET;
	addr_serv.sin_addr.s_addr = htonl(atoi(argv[1]));
	addr_serv.sin_port = htons(atoi(argv[2]));
	
	sock_clnt = connect(sock_clnt, (struct sockaddr*)&addr_serv, sizeof(addr_serv));
	if(sock_clnt == -1){
		cout<<"connect error.."<<endl;
		exit(0);	
	}
	//子进程负责写，父进程负责读	
	pid_t pid = fork();
	if(pid == -1){
		cout<<"create child proc error.."<<endl;
		exit(0);	
	}	
	if(pid == 0){
		while(1){
			cout<<"please enter your message: "<<endl;
			cin.getline(buf, 1024, '\n');
			if(buf == "q" || buf == "Q"){
				shutdown(sock_clnt, SHUT_WR);
				return 1;	
			}	
			write(sock_clnt, buf, strlen(buf));	
		}
			
	}else{
		while(1){
			int len_r = read(sock_clnt, buf, BUF_SIZE);
			if(len_r == 0){
				break;	
			}	
			buf[len_r]='\0';
			cout<<"message from server: "<<buf<<endl;	
		}	
		
	}
	close(sock_clnt);
	return 0;
}
