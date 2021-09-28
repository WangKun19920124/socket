#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<unistd.h>

#define BUFF_SIZE 1024
#define PORT "5000"

int main(int argc,char** argv){
	int sockListen;
	int sockClnt;
	char msg[]="hello";
	struct sockaddr_in addrListen;
	struct sockaddr_in addr_clnt;
	memset(&addrListen,0,sizeof(addrListen));
	
	sockListen=socket(PF_INET,SOCK_STREAM,0);
	if(sockListen==-1){
		printf("socket error..\n");
	}

	addrListen.sin_family=AF_INET;
	addrListen.sin_addr.s_addr=htonl(INADDR_ANY);
	addrListen.sin_port=htons(atoi(argv[1]));
	if(bind(sockListen,(struct sockaddr*)&addrListen,sizeof(addrListen))==-1){
		printf("bind error..");
	}

	if(listen(sockListen,5)==-1){
		printf("listen error..");
	}
	socklen_t addr_clnt_sz=sizeof(addr_clnt);
	sockClnt = accept(sockListen,(struct sockaddr*)&addr_clnt,&addr_clnt_sz);
	if(sockClnt==-1){
		printf("accept error..");
	}
	write(sockClnt,msg,sizeof(msg));

	close(sockListen);
	close(sockClnt);

	return 0;
}
