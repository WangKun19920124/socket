#include<iostream>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
using namespace std;

int main(int argc, char** argv){
	int sock = socket(PF_INET, SOCK_STREAM, 0);
	int snd_buf;
	int rcv_buf;
	int len;
	int state;
	
	snd_buf = atoi(argv[1]);
	rcv_buf = atoi(argv[1]);

	len = sizeof(snd_buf);
	state = setsockopt(sock, SOL_SOCKET, SO_SNDBUF, (void*)&snd_buf, (socklen_t)len);
	if(state==-1){
		cout<<"getsockopt error.."<<endl;	
	}

	len = sizeof(rcv_buf);
	state = setsockopt(sock, SOL_SOCKET, SO_RCVBUF, (void*)&rcv_buf, (socklen_t)len);
	if(state==-1){
		cout<<"getsockopt error.."<<endl;	
	}

	state = getsockopt(sock, SOL_SOCKET, SO_SNDBUF, (void*)&snd_buf, (socklen_t*)&len);
	if(state==-1){
		cout<<"getsockopt error.."<<endl;	
	}
	cout<<"output buff size:"<<snd_buf<<endl;
	state = getsockopt(sock, SOL_SOCKET, SO_RCVBUF, (void*)&rcv_buf, (socklen_t*)&len);
	if(state==-1){
		cout<<"getsockopt error.."<<endl;	
	}
	cout<<"input buff size:"<<rcv_buf<<endl;

	return 0;	


}
