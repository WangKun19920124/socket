#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<unistd.h>

#define BUFF_SIZE 1024
#define PORT "5000"
#define IP "192.168.8.145"

int main(int argc,char** argv){
	int sock_serv;
	char msg[BUFF_SIZE];

	struct sockaddr_in addrServ;
	memset(&addrServ,0,sizeof(addrServ));
	sock_serv=socket(PF_INET,SOCK_STREAM,0);
	if(sock_serv==-1){
		printf("socket error..");
	}

	addrServ.sin_family=AF_INET;
	addrServ.sin_addr.s_addr=inet_addr(argv[1]);
	addrServ.sin_port=htons(atoi(argv[2]));
	
	int con = connect(sock_serv,(struct sockaddr*)&addrServ,sizeof(addrServ));
	if(con==-1){
		printf("connect error..\n");
		printf("%d\n",con);
	}

	if(read(sock_serv,msg,sizeof(msg)-1)==-1){
		printf("read error");
	}
	printf("msg:%s\n",msg);
	close(sock_serv);

	return 0;
}
