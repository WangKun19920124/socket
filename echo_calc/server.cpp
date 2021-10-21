#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<cstring>
#include<string.h>
using namespace std;

#define BUF_SIZE 1024
#define RLZ_SIZE 4
#define NUM_SIZE 4

int calc(char cnt_num, char* buffer, char op){
	int result_temp = buffer[0] - '0';
	int num_cnt_temp = cnt_num - '0';
	switch(op){
		case '+':
			for(int i=1;i < num_cnt_temp;i++){
				result_temp += (buffer[i] - '0'); 
			}
			break;
		case '-':
			for(int i=1;i < num_cnt_temp;i++){
				result_temp -= (buffer[i] - '0');
			}
			break;
		case '*':
			for(int i=1;i < num_cnt_temp;i++){
				result_temp *= (buffer[i] - '0');
			}
	}
	return result_temp;
	
}


int main(int argc, char** argv){
	int sock_listen;
	int sock_clnt;
	struct sockaddr_in addr_serv;
	memset(&addr_serv, 0, sizeof(addr_serv));
	struct sockaddr_in addr_clnt;
	socklen_t addr_clnt_sz = sizeof(addr_clnt);
	char buff[BUF_SIZE];

	if(argc!=2){
		cout<<"format:"<<argv[0]<<"<port>"<<endl;
	}

	addr_serv.sin_family = AF_INET;
	addr_serv.sin_addr.s_addr = htonl(INADDR_ANY);
	addr_serv.sin_port = htons(atoi(argv[1]));
	
	sock_listen = socket(PF_INET, SOCK_STREAM, 0);
	if(sock_listen == -1){
		cout<<"socket error.."<<endl;
	}

	if(bind(sock_listen, (sockaddr*)&addr_serv, sizeof(addr_serv))==-1){
		cout<<"bind error.."<<endl;
	}
	
	if(listen(sock_listen, 10) == -1){
		cout<<"listen error.."<<endl;
	}

	sock_clnt = accept(sock_listen, (sockaddr*)&addr_clnt, &addr_clnt_sz);
	if(sock_clnt == -1){
		cout<<"accept error.."<<endl;
	}else{
		cout<<"server connected!!"<<endl;
	}

	while(1){
		char num_cnt;
		int result = 0;
		if(read(sock_clnt,&num_cnt,1)==-1){
			cout<<"read error.."<<endl;
		}
		cout<<"num_clnt="<<num_cnt<<endl;
		
		int recv_total = 0;
		int recv_temp = 0;

		while(recv_total < (int)(num_cnt - '0') + 1){
			recv_temp = read(sock_clnt, &buff, BUF_SIZE);
			recv_total += recv_temp;
			if(recv_temp == -1){
				cout<<"read error.."<<endl;
			}else if(recv_total == (int)(num_cnt - '0') +1){
				cout<<"all data has been received!!"<<endl;
			}
		}

		char oper = buff[recv_total - 1];
		result = calc(num_cnt, buff, oper);

		int send_total = 0;
		int send_temp = 0;
		while(send_total < RLZ_SIZE){
			send_temp = write(sock_clnt, &result, RLZ_SIZE);
			if(send_temp == -1){
				cout<<"server write result error.."<<endl;
			}else{
				send_total += send_temp;
			}
			
		}

		close(sock_clnt);
	}

	close(sock_listen);
	return 0;

}






















