#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<unistd.h>
#include<iostream>
using namespace std;

#define BUFF_SIZE 1024

int main(int argc, char* argv[]){
    if(argc!=2){
	printf("格式： %s <port>\n",argv[0]);
    }

    int sock_listen;
    int sock_clnt;
    struct sockaddr_in addr_serv;
    memset(&addr_serv,0 ,sizeof(addr_serv));

    struct sockaddr_in addr_clnt;
    socklen_t addr_clnt_sz;
    addr_clnt_sz=sizeof(addr_clnt);

    char message[BUFF_SIZE];
    

    sock_listen=socket(PF_INET, SOCK_STREAM, 0);
    if(sock_listen==-1){
    	cout<<"socket error.."<<endl;
    }

    addr_serv.sin_family=AF_INET;
    addr_serv.sin_addr.s_addr=htonl(INADDR_ANY);
    addr_serv.sin_port=htons(atoi(argv[1]));
    
    if(bind(sock_listen,(struct sockaddr*)&addr_serv,sizeof(addr_serv))==-1){
    	cout<<"bind error.."<<endl;
    }
    
    if(listen(sock_listen, 10)==-1){
    	cout<<"listen error.."<<endl;
    }
    
    sock_clnt=accept(sock_listen,(struct sockaddr*)&addr_clnt, &addr_clnt_sz);
    if(sock_clnt==-1){
   	cout<<"accept error.."<<endl;      
    }else{
	cout<<"connected!"<<endl;
    }

    int str_len=0;
    str_len=read(sock_clnt, message, BUFF_SIZE);
    if(str_len!=0){
        write(sock_clnt, message, str_len);
    }
    close(sock_clnt);
    close(sock_listen);
    return 0;
}
