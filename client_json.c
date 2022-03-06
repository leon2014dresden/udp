/*
	Simple udp client
*/
#include<stdio.h>
#include<winsock2.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"cJSON.h"

#pragma comment(lib,"ws2_32.lib") //Winsock Library

#define SERVER "127.0.0.1"	//ip address of udp server
#define BUFLEN 512	//Max length of buffer
#define PORT 9999	//The port on which to listen for incoming data

int main(void)
{
	struct sockaddr_in si_other;
	int s, slen=sizeof(si_other);
	char buf[BUFLEN];
	char message[BUFLEN];
	WSADATA wsa;

	//Initialise winsock
	printf("\nInitialising Winsock...");
	if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
	{
		printf("Failed. Error Code : %d",WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	printf("Initialised.\n");
	
	//create socket
	if ( (s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == SOCKET_ERROR)
	{
		printf("socket() failed with error code : %d" , WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	
	//setup address structure
	memset((char *) &si_other, 0, sizeof(si_other));
	si_other.sin_family = AF_INET;
	si_other.sin_port = htons(PORT);
	si_other.sin_addr.S_un.S_addr = inet_addr(SERVER);




	int num[5] = {1,2,3,4,5};
	int len = sizeof(num)/sizeof(num[0]);

	//start communication
	while(1)
	{	
		//创建一个空的文档（对象）
		cJSON *json = cJSON_CreateObject();

		//向文档中增加一个键值对{"name":"王大锤"}
		cJSON_AddItemToObject(json,"name",cJSON_CreateString("王大锤"));
		//向文档中添加一个键值对
		//cJSON_AddItemToObject(json,"age",cJSON_CreateNumber(29));
		cJSON_AddNumberToObject(json,"age",29);

		cJSON *array = cJSON_CreateArray();
		cJSON_AddItemToObject(json,"love",array);
		cJSON_AddItemToArray(array,cJSON_CreateString("LOL"));
		cJSON_AddItemToArray(array,cJSON_CreateString("NBA"));
		cJSON_AddItemToArray(array,cJSON_CreateString("Go shopping"));

		cJSON *array2 = cJSON_CreateArray();
		cJSON_AddItemToObject(json,"member",array2);
		for (int i = 0; i < len; i++) {
			cJSON_AddItemToArray(array2,cJSON_CreateNumber(num[i]));
		}


		cJSON_AddNumberToObject(json,"score",59);
		cJSON_AddStringToObject(json,"address","beijing");

		//将json结构格式化到缓冲区
		strcpy(message, cJSON_Print(json));



		//send the message
		if (sendto(s, message, strlen(message) , 0 , (struct sockaddr *) &si_other, slen) == SOCKET_ERROR)
		{
			printf("sendto() failed with error code : %d" , WSAGetLastError());
			exit(EXIT_FAILURE);
		}

		//释放json结构所占用的内存
		cJSON_Delete(json);
	}

	closesocket(s);
	WSACleanup();

	return 0;
}