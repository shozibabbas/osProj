#include <stdio.h>
#include <stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<string.h>

int main(int argc, char *argv[]) {
	if (argc != 3)
	{
		printf("not enough arguments");
		return 0;
	}

	char* fileName = argv[1];
	int portNumber = atoi((char *)argv[2]);

	char buff[12000];
	char file_buffer[12000];
	int sd, connfd, len;

	struct sockaddr_in servaddr, cliaddr;

	sd = socket(AF_INET, SOCK_DGRAM, 0);

	if (sd == -1)
	{
		printf(" socket not created in server\n");
		exit(0);
	}

	bzero(&servaddr, sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_port = htons(portNumber);

	if (bind(sd, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0)
		printf("Not binded\n");

	len = sizeof(cliaddr);

	//recvfrom(sd, buff, 1024, 0,
	//	(struct sockaddr *)&cliaddr, &len);

	//printf("%s\n", buff);

	FILE *fp;
	fp = fopen("receivedFile.txt", "ab");
	if (NULL == fp)
	{
		printf("\n Error opening file \n");
	}

	printf("waiting for server");

	while (1) {
		recvfrom(sd, buff, 12000, 0, (struct sockaddr *) &cliaddr, &len);

		printf("%s\n", buff);

	}


	return 1;
}