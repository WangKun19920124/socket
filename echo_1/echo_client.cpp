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
/*
    while(1){
	memset(&msg_w,0,sizeof(msg_w));
	memset(&msg_r,0,sizeof(msg_r));
        printf("input your message(Q/q to quit):");
	string msg_temp;
	cin>>msg_temp;
        if(msg_temp=="Q"||msg_temp=="q"){
            break;
        }else{
            for(auto i=0;i<msg_temp.size();i++){
                msg_w[i]=msg_temp.at(i);
            }
        }        

        if(write(sock_clnt, &msg_w, BUFF_SIZE)==-1){
            //error("write error..");
        }

        if(read(sock_clnt,&msg_r,BUFF_SIZE)==-1){
            //error("read error..");
        }

        cout<<"message from server: "<<msg_r<<endl;
    }
*/


    cout<<"input your msg:"<<endl;
    cin.getline(msg,1024,'\n');	//按行读取。cin>>遇到空格会略过，不读取留在缓冲区
    int nbytes = write(sock_clnt,msg,strlen(msg));
    if(nbytes!=0){
    	 read(sock_clnt,msg,BUFF_SIZE-1);
    }
   
    cout<<msg<<endl;
    close(sock_clnt);
    return 0;
}
