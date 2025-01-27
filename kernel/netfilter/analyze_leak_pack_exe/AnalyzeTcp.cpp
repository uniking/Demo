#include "AnalyzeTcp.h"

int main(int argn, char* argv[])
{
	int sockfd;
	socklen_t len;
	int ret;

	sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
	if(sockfd < 0)
	{
		cout<<"can not create a socket"<<endl;
		return -1;
	}



	while(true)
	{
			TCP_DATA tcp_data = {0};
			len = sizeof(TCP_DATA);

			ret = getsockopt(sockfd, IPPROTO_IP, SOCKET_OPS_GET, &tcp_data, &len);
			if(ret == 0)
			{
				cout<<"s:"<<tcp_data.sip<<" sp:"<<tcp_data.s_port<<" dip:"<<tcp_data.dip<<" dp:"<<tcp_data.d_port<<" seq:"<<tcp_data.seq<<" w_seq:"<<tcp_data.want_seq<<endl;
			}
			else
			{
				cout<<"ret != 0"<<endl;
				sleep(3);
			}
	}

	return 0;
}
