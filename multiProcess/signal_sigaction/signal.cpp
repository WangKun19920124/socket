//signal用于Handler函数注册
//信号发生后，将调用Handler函数
#include<iostream>
#include<unistd.h>
#include<signal.h>

void timeout(int sig)
{
	std::cout<<"time out.."<<std::endl;
	alarm(2);
}

void ctrlc(int sig)
{
	std::cout<<"ctrl-c has been pressed.."<<std::endl;
}

int main(int argc, char** argv)
{
	signal(SIGALRM, timeout);
	signal(SIGINT, ctrlc);
	alarm(2);
	for(int i=0;i<3;i++){
		std::cout<<"wait.."<<std::endl;
		sleep(100);	
	}
	return 0;

}

