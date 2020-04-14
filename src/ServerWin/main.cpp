#include <WS2tcpip.h>
#include <iostream>

int main()
{
	unsigned short port = 2000;
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		std::cerr << "WSAStartup() error!\n";
		return 1;
	}

	SOCKET hServSock, hClntSock;
	hServSock = socket(PF_INET, SOCK_STREAM, 0);
	if (hServSock == INVALID_SOCKET)
	{
		std::cerr << "socket() error!\n";
		return 1;
	}

	SOCKADDR_IN servAddr, clntAddr;
	int clntAddrSize = sizeof(clntAddr);
	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(2000);

	if (bind(hServSock, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
	{
		std::cerr << "bind() error!\n";
		return 1;
	}

	if (listen(hServSock, SOMAXCONN) == SOCKET_ERROR)
	{
		std::cerr << "listen() error!\n";
		return 1;
	}

	hClntSock = accept(hServSock, (SOCKADDR*)&clntAddr, &clntAddrSize);
	if (hClntSock == INVALID_SOCKET)
	{
		std::cerr << "accept() error!\n";
		return 1;
	}

	char host[NI_MAXHOST];
	char service[NI_MAXSERV];
	ZeroMemory(host, NI_MAXHOST);
	ZeroMemory(service, NI_MAXSERV);

	if (getnameinfo((sockaddr*)&clntAddr, sizeof(clntAddr), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
	{
		std::cout << host << " connected on port " << service << '\n';
	}
	else
	{
		inet_ntop(AF_INET, &clntAddr.sin_addr, host, NI_MAXHOST);
		std::cout << host << "connectod on port " << ntohs(clntAddr.sin_port) << '\n';
	}

	closesocket(hServSock);

	/****** Do things with client ******/

	char buf[128] = { 0 };
	while (recv(hClntSock, buf, sizeof(buf), 0) != 0)
	{
		buf[127] = '\0';
		std::cout << "client sent : " << buf << '\n';
		ZeroMemory(buf, 128);
	}

	std::cout << "client disconnected\n";

	/***********************************/

	closesocket(hClntSock);
	WSACleanup();
	return 0;
}