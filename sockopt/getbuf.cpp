#include<iostream>
#include<sys/socket.h>
#include<unistd.h>
using namespace std;

int main(int argc, char** argv){
	int sock = socket(PF_INET, SOCK_STREAM, 0);
	int snd_buf;
	int rcv_buf;
	int len;
	int state;

	len = sizeof(snd_buf);
	state = getsockopt(sock, SOL_SOCKET, SO_SNDBUF, (void*)&snd_buf, (socklen_t*)&len);
	if(state==-1){
		cout<<"getsockopt error.."<<endl;	
	}
	cout<<"output buf size:"<<snd_buf<<" B"<<endl;

	len = sizeof(rcv_buf);
	state = getsockopt(sock, SOL_SOCKET, SO_SNDBUF, (void*)&rcv_buf, (socklen_t*)&len);
	if(state==-1){
		cout<<"getsockopt error.."<<endl;	
	}
	cout<<"input buf size:"<<rcv_buf<<" B"<<endl;
	return 0;	

}
