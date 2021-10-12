#include<iostream>
#include<cstring>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
using namespace std;
#define BUF_SIZE 100

int main(int argc, char** argv){
	char buf[BUF_SIZE];
	int sock_clnt;
	struct sockaddr_in addr_serv;

	sock_clnt =socket(PF_INET, SOCK_STREAM, 0);
	addr_serv.sin_family = AF_INET;
	addr_serv.sin_addr.s_addr = inet_addr(argv[1]);
	addr_serv.sin_port = htons(atoi(argv[2]));
	
	connect(sock_clnt, (struct sockaddr*)&addr_serv, sizeof(addr_serv));
	
	FILE* fstream = fopen("recv.txt","wt");	
	int len = 0;
	
		len = recv(sock_clnt, buf, BUF_SIZE, 0);
		if(len!=0){
			fwrite(buf, 1, len, fstream);
		}
	

	cout<<"file has been received!!"<<endl;
	
	char msg[] = "thank you!";
	int len_send = send(sock_clnt, msg, strlen(msg), 0);
	if(len_send == -1){
		cout<<"thank you send error.."<<endl;
	}else{
		cout<<"len_send="<<len_send<<endl;
	}

	fclose(fstream);
	close(sock_clnt);
	return 0;

} 
