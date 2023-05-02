// 課題の為非推奨な関数を使用している
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <WinSock2.h>
#include <stdio.h>
#include <iostream>

#pragma comment(lib, "ws2_32.lib")

int main(void) {
	WSADATA		wsaData;
	char		hostname[256];

	const WORD version = MAKEWORD(2, 2);	// version
	const auto status = WSAStartup(version, &wsaData);
	// winsock2の初期化
	if(status == SOCKET_ERROR) {
		puts("reset winsock faild");
		return -1;
	}
	// 端末名の取得
	gethostname(hostname, (int)sizeof(hostname));

	// version
	printf_s("version(wVersion):%u\n", wsaData.wVersion);
	printf_s("LOBYTE:%u\n", LOBYTE(wsaData.wVersion));
	printf_s("HIBYTE:%u\n", HIBYTE(wsaData.wVersion));
	printf_s("HighVersion:%u\n", wsaData.wHighVersion);
	printf_s("\n");
	printf_s("description:%s\n", wsaData.szDescription);
	printf_s("\n");
	printf_s("system status:%s\n", wsaData.szSystemStatus);
	printf_s("\n");
	printf_s("host name:%s\n", hostname);
	printf_s("\n");

	// IPアドレスの取得
	HOSTENT* const ipHost = gethostbyname(hostname);
	IN_ADDR(address);
	for(int i = 0; ipHost->h_addr_list[i] != NULL; ++i) {
		memcpy_s(&address, sizeof(decltype(address)), ipHost->h_addr_list[i], ipHost->h_length);
		printf_s("IP Address[%d]:%s\n", i, inet_ntoa(address));
	}

	WSACleanup();

	return 0;
}

