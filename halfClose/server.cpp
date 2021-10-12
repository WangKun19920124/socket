#include<iostream>
#include<cstring>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
using namespace std;
#define BUF_SIZE 100


int main(int argc, char** argv){
	char buf[BUF_SIZE];
	int sock_serv;
	struct sockaddr_in addr_serv;
	memset(&addr_serv, 0, sizeof(addr_serv));
	sock_serv = socket(PF_INET, SOCK_STREAM, 0);
	addr_serv.sin_family = AF_INET;
	addr_serv.sin_addr.s_addr = htonl(INADDR_ANY);
	addr_serv.sin_port = htons(atoi(argv[1]));

	bind(sock_serv, (struct sockaddr*)&addr_serv, sizeof(addr_serv));

	listen(sock_serv, 10);

	int sock_clnt;
	struct sockaddr_in addr_clnt;
	int addr_clnt_sz = sizeof(addr_clnt);

	sock_clnt = accept(sock_serv, (struct sockaddr*)&addr_clnt, (socklen_t*)&addr_clnt_sz);
	if(sock_clnt == -1){
		cout<<"connect error.."<<endl;
	}

	FILE* fstream = fopen("./test.txt", "rt");
	int len_fp = 0;
	while(1){
		len_fp = fread(buf, 1, BUF_SIZE, fstream);
		if(len_fp < BUF_SIZE){
			send(sock_clnt, &buf, len_fp, 0);
			break;
		}else if(len_fp == BUF_SIZE){
			send(sock_clnt, &buf, BUF_SIZE, 0);
		}
	}


	shutdown(sock_clnt, SHUT_WR);
	memset(buf, 0, sizeof(buf));
	int len_recv = recv(sock_clnt, buf, BUF_SIZE, 0);
	cout<<"meg from client:"<<buf<<endl;


	fclose(fstream);
	close(sock_clnt);
	return 0;

}
