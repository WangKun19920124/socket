#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<cstring>
#include<string>
using namespace std;

#define BUF_SIZE 1024
#define RLZ_SIZE 4
#define NUM_SIZE 4

int sock_listen;
int sock_clnt;
sockaddr_in addr_serv;
memset(&addr_serv, 0, sizeof(addr_serv));

sockaddr_in addr_clnt;
socklen_t addr_clnt_sz = sizeof(sockaddr_in);

void errorOutput(string errMsg){
	cout<<errMsg<<endl;
}

void tcp_server_conn(){
	sock_listen = socket(PF_INET, SOCK_STREAM, 0);
	if(sock_listen == -1){
		errorOutput("socket error..");
	}

	addr_serv.sin_family = AF_INET;
	addr_serv.sin_addr.s_addr = htonl(INADDR_ANY);
	addr_serv.port = htons(atoi(argv[1]));

	if(bind(sock_serv, (sockaddr*)&addr_serv, 0) == -1){
		errorOutput("bind error");
	}

	if(listen(sock_serv, 5)){
		errorOutput("listen error");
	}

	sock_clnt = accept(sock_serv, (sockaddr*)&addr_clnt, &addr_clnt_sz);

	if(sock_clnt == -1){
		errorOutput("accept error..");
	}else{
		cout<<"server connected!!"<<endl;
	}
}

int calc(int cnt_num, char* buffer, char op){
	int result_temp = buffer[0];
	switch(op){
		case '+':
			for(int i=0;i<cnt_num;i++){
				result_temp+=buffer[i];
			}
			break;
		case '-':
			for(int i=0;i<cnt_num;i++){
				result_temp-=buffer[i];
			}
			break;
		case '*':
			for(int i=0;i<cnt_num;i++){
				result_temp*=buffer[i];
			}
	}
	return result_temp;
}

int main(int argc, char** argv){
	tcp_server_conn();

	for(int i=0;i<2;i++){
		unsigned int num_cnt =0;	//num_cnt在buff中仅1byte，所以用无符最好，表示0~255范围数字
		int result = 0;
		if(read(sock_clnt, (char*)&num_cnt, 1)==-1){
			errorOutput("read num count error..");
		}

		int recv_total = 0;
		int recv_temp = 0;

		while(recv_total < num_cnt*NUM_SIZE + 1){
			recv_temp = read(sock_clnt, &buff[recv_total], BUF_SIZE - recv_total);
			if(recv_temp == -1){
				errorOutput("read num and operator error..");
			}else{
				recv_total += recv_temp;
			}		
			
			if(recv_total == num_cnt*NUM_SIZE + 1){
				cout<<"all data has been received!!"<<endl;
			}

		}
		char oper = buffer[recv_total-1];
		result = calc(num_cnt, buff, oper);

		if(write(sock_clnt, &result, RLZ_SIZE) == -1){
			cout<<"server write result error.."<<endl;
		}

		close(sock_clnt);

	}
	close(sock_listen);

	cin.get();
	return 0;
}
