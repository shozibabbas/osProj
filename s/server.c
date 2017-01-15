#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/socket.h>
#include <resolv.h>
#include<netinet/in.h>
#include<sys/types.h>
#include <string.h>

int main(int argc, char *argv[]) {
	if (argc != 3)
	{
		printf("not enough arguments");
		return 0;
	}

	char* fileName = argv[1];
	int portNumber = atoi((char *)argv[2]);

	//char buff[2000];
	int sockfd, connfd, len;

	struct sockaddr_in servaddr, cliaddr;
	// create socket in client side
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	if (sockfd == -1)
	{
		printf(" socket not created in client\n");
		exit(0);
	}

	bzero(&servaddr, sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = INADDR_ANY; // ANY address or use specific address
	servaddr.sin_port = htons(portNumber);  // Port address

	//printf("Type ur  UDP client message\n");
	//scanf("%s", buff);

	//// send  msg to server

	//sendto(sockfd, buff, strlen(buff), 0,
	//	(struct sockaddr *)&servaddr, sizeof(struct sockaddr));

	/* Open the file that we wish to transfer */
	FILE *fp = fopen("sample.txt", "rb");
	if (fp == NULL)
	{
		printf("File open error");
		return 1;
	}

	fseek(fp, 0L, SEEK_END);
	int sz = ftell(fp);
	fseek(fp, 0L, SEEK_SET);

	char *fileStore = malloc(sz * sizeof(char*));
	int read_bytes = fread(fileStore, 1, sz, fp);

	char buff[500] = { 0 };
	int bytes_sent = 0;

	while (bytes_sent < sz) {
		for (int i = 0; i < 500; i++) {
			buff[i] = fileStore[bytes_sent + i];
		}

		bytes_sent += 500;

		sendto(sockfd, buff, strlen(buff), 0, (struct sockaddr *) &servaddr, sizeof(struct sockaddr));
	}

	//while (1) {
	//	char buff[10308] = { 0 };

	//	sendto(sockfd, fileStore, strlen(fileStore), 0, (struct sockaddr *) &servaddr, sizeof(struct sockaddr));

	//	if (read_bytes < 10308)
	//	{
	//		if (feof(fp))
	//		{
	//			printf("File has been sent...\n");
	//			break;
	//		}
	//	}
	//}

	return 1;
}