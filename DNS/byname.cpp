#include<iostream>
#include<cstring>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<netdb.h>
using namespace std;

int main(int argc, char** argv){
	struct hostent* host;
	host = gethostbyname(argv[1]);

	if(host == NULL){
		cout<<"gethostbyaddr error.."<<endl;	
	}

	cout<<"official name:"<<host->h_name<<endl;
	int i=0;
	while(host->h_aliases[i]!=NULL){
		cout<<"name list:"<<host->h_aliases[i]<<endl;
		i++;	
	}	


	cout<<"addr type:"<<((host->h_addrtype == AF_INET)?"AF_INET":"AF_INET6")<<endl;

	cout<<"addr length:"<<host->h_length<<endl;

	int j=0;
	while(host->h_addr_list[j]!=NULL){
		cout<<"IP:"<<inet_ntoa(*(in_addr*)&host->h_addr_list[j])<<endl;
		char str[1024];	
		inet_ntop(AF_INET, &host->h_addr_list[j], str, sizeof(str));
		cout<<"IP_:"<<str<<endl;
		j++;	
	
	}

	return 0;

}
