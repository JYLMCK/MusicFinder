#include <WS2tcpip.h>
#include <iostream>
#include <string>

#include "shared/MusicFinderCore.h"

void ClearConsole()
{
	COORD topLeft = {0, 0};
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen;
	DWORD written;

	GetConsoleScreenBufferInfo(console, &screen);
	FillConsoleOutputCharacterA(console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written);
	FillConsoleOutputAttribute(console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
	                           screen.dwSize.X * screen.dwSize.Y, topLeft, &written);
	SetConsoleCursorPosition(console, topLeft);
}

int main()
{
	ClearConsole();
	std::cout << "*******************************************\n"
	             "*                                         *\n"
	             "*         Welcome To MusicFinder!         *\n"
	             "*                                         *\n"
	             "*******************************************\n"
	             "                        (Created By JYLMCK)\n";

	constexpr char ip[] = "127.0.0.1";
	constexpr unsigned short port = 2000;
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		std::cerr << "WSAStartup() error!\n";
		WSACleanup();
		return 1;
	}

	SOCKET hSocket = socket(PF_INET, SOCK_STREAM, 0);
	if (hSocket == INVALID_SOCKET)
	{
		std::cerr << "socket() error!\n";
		WSACleanup();
		return 1;
	}

	SOCKADDR_IN servAddr;
	ZeroMemory(&servAddr, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	inet_pton(AF_INET, ip, &servAddr.sin_addr.S_un.S_addr);
	servAddr.sin_port = htons(2000);

	if (connect(hSocket, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
	{
		std::cerr << "connect() error!\n";
		WSACleanup();
		return 1;
	}

	/****** Do things with server ******/

	std::string input;
	std::getline(std::cin, input);
	auto result = ParseInput(input);
	if (result.has_value())
	{
		std::cout << "Searching for [ " << result->first << "]\n";
		send(hSocket, result->second.c_str(), static_cast<int>(result->second.size()), 0);
	}
	else
	{
		std::cout << "Invalid input!\n";
	}
	/***********************************/

	closesocket(hSocket);
	WSACleanup();
	return 0;
}