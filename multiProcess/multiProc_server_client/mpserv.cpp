#include<iostream>
#include<cstring>
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
	if(sig == SIGCHLD){
		waitpid(-1, &status, WNOHANG);		
	}
	if(WIFEXITED(status)){
		cout<<"child proc id = "<<WEXITSTATUS(status)<<"has been destroyed.."<<endl;	
	}
}

int main(int argc, char** argv)
{
	//僵尸子进程销毁
	struct sigaction act;
	act.sa_handler = child_proc;
//	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	sigaction(SIGCHLD,&act,0);
	//通信，父进程负责连接，子进程负责通信
	char buf[BUF_SIZE];
	int sock_listen;
	sock_listen = socket(PF_INET, SOCK_STREAM, 0);
	if(sock_listen == -1){
		cout<<"sock_listen error.."<<endl;	
	}
	struct sockaddr_in addr_serv;
	memset(&addr_serv, 0, sizeof(addr_serv));
	addr_serv.sin_family = AF_INET;
	addr_serv.sin_addr.s_addr = htonl(INADDR_ANY);
	addr_serv.sin_port = htons(atoi(argv[1]));

	if(bind(sock_listen, (struct sockaddr*)&addr_serv, sizeof(addr_serv)) == -1){
		cout<<"bind error.."<<endl;	
	}
	
	if(listen(sock_listen, 10) == -1){
		cout<<"listen error.."<<endl;	
	}	

	int sock_clnt;
	socklen_t addr_clnt_sz;
	struct sockaddr_in addr_clnt;
	while(1){
		addr_clnt_sz = sizeof(addr_clnt);
		sock_clnt = accept(sock_listen, (struct sockaddr*)&addr_clnt, &addr_clnt_sz);
		if(sock_clnt == -1){
			cout<<"accept error.."<<endl;
			close(sock_clnt);	//队列中没有客户端发起的连接，sock_clnt创建失败，关闭sock_clnt
			continue;	
		}
	
		//创建子进程处理IO
		pid_t pid = fork();
		if(pid == -1){
			close(sock_clnt);
			continue;	
		}

		if(pid == 0){
			close(sock_listen);		//子进程将自己的sock_listen文件描述符关闭
			while(1){
				int len_r = read(sock_clnt, buf, BUF_SIZE);
				if(len_r == 0)
					break;
				buf[len_r]='2';
				buf[len_r+1]='3';
				buf[len_r+2]='3';
				write(sock_clnt, buf, len_r);	
			}
			close(sock_clnt);
			cout<<"child proc return"<<endl;
			return 1;
			
		}else{
			cout<<"create child proc id = "<<pid<<endl;
			close(sock_clnt);	//父进程将自己的sock_clnt文件描述符关闭
					
		}
		
		close(sock_listen);
		//sleep(600);
		cout<<"father proc return"<<endl;
		return 0;

	}
			









}
