#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include<string.h>
#include<iostream>
#include<string>
using namespace std;

#define BUFF_SIZE 1024

int main(int argc, char** argv){
    int sock_clnt;
    struct sockaddr_in addr_clnt;
    memset(&addr_clnt,0 ,sizeof(addr_clnt));

    char msg[BUFF_SIZE];
    sock_clnt=socket(AF_INET, SOCK_STREAM,0);

    addr_clnt.sin_family=PF_INET;
    addr_clnt.sin_addr.s_addr=inet_addr(argv[1]);
    addr_clnt.sin_port=htons(atoi(argv[2]));

    if(connect(sock_clnt,(struct sockaddr*)&addr_clnt, sizeof(addr_clnt))==-1){
	cout<<"connect error.."<<endl;
    }else{
        printf("connected..\n");
    }

    cout<<"input your msg:"<<endl;
    cin.getline(msg,1024,'\n');	//按行读取。cin>>遇到空格会略过，不读取留在缓冲区
    int bytes_total = write(sock_clnt,msg,strlen(msg));
    int bytes_temp=0;
    if(bytes_temp <bytes_total){
    	bytes_temp += read(sock_clnt,msg,BUFF_SIZE-1);
	
    }
    if(bytes_temp == bytes_total){
    	cout<<"all data has been recv!"<<endl;
    }
    msg[bytes_temp]='\0';
    cout<<msg<<endl;
    close(sock_clnt);
    return 0;
}
