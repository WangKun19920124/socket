/**
 *1byte 存操作数个数
 *1byte 存操作符
 *4byte 存int操作数
 * */


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
#define NUM_SIZE 4
#define RLZ_SIZE 4

int sock_clnt;
sockaddr_in addr_serv;
memset(&addr_serv, 0, sizeof(addr_serv));
char buffer[BUF_SIZE];


void tcp_clnt_conn(){

	sock_clnt = socket(PF_INET, SOCK_STREAM, 0 );
       	if(sock_clnt == -1){
		cout<<"socket error.."<<endl;
	}	

	addr_serv.sin_family=AF_INET;
	addr_serv.sin_addr.s_addr=htonl(INADDR_ANY);
	addr_serv.sin_port = htons(atoi(argv[2]));

	if(connect(sock_clnt, (sockaddr*)&addr_serv, sizeof(addr_serv)) == -1){
		cout<<"connect error.."<<endl;
	}else{
		cout<<"client connected!!"<<endl;
	}
}

int main(int argc, char** argv){
	tcp_client_conn();
	
	unsigned int num_cnt = 0;
	cout<<"enter total num of nums:"<<endl;
	cin>>num_cnt;

	if(num_cnt <= 0){
		cout<<"please enter a valid total num.."<<endl;
	}
	buffer[0]=(char)num_cnt;

	cout<<"enter operator:"<<endl;
	char oper;
	cin.get(oper);
	if(oper!='+' || oper!='-' || oper!='*'){
		cout<<"enter valid operator:"<<endll;
	}
	buffer[1+num_cnt*NUM_SIZE]=oper;

	int num_temp;
	for(int i=0;i<num_cnt;i++){
		cout<<"enter nums"<<i<<":"<<endl;
		cin>>num_temp;
		memcpy(&buffer[i*NUM_SIZE+1],num_temp,sizeof(int));
	}
	
	if(write(sock_clnt, buffer, num_cnt*NUM_SIZE + 2)==-1){
		cout<<"client write error.."<<endl;
	}	
	int result = 0;
	if(read(sock_clnt, &result, RLZ_SIZE)==-1){
		cout<<"result="<<result<<endl;
	}

	cin.get();
	return 0

}

