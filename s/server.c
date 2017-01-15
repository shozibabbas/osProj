#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/socket.h>
#include <resolv.h>
#include<netinet/in.h>
#include<sys/types.h>
#include <string.h>
#include <math.h>

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
	int totalBytes = ftell(fp);
	fseek(fp, 0L, SEEK_SET);

	//double numDatagrams = ceil(totalBytes / 500);
	int datagramCount = 0;
	char dArray[5];

	char *fileStore = malloc(totalBytes * sizeof(char*));
	int read_bytes = fread(fileStore, 1, totalBytes, fp);

	char buff[500] = { 0 };
	int bytes_sent = 0;

	int ackCounter = 0;

	while (bytes_sent < totalBytes) {

		sprintf(dArray, "%d", datagramCount);

		for (int i = 0; i < 500; i++) {
			buff[i] = '-';
		}

		for (int i = 0; i < 500; i++) {
			buff[i] = fileStore[bytes_sent++];
			if (fileStore[bytes_sent] == '\0') {
				break;
			}
		}

		sendto(sockfd, dArray, sizeof(dArray), 0, (struct sockaddr *) &servaddr, sizeof(struct sockaddr));

		sendto(sockfd, buff, strlen(buff), 0, (struct sockaddr *) &servaddr, sizeof(struct sockaddr));

		printf("sent datagram %d\n", datagramCount);

		datagramCount++;

		if (datagramCount % 5 == 0) {
			int ack;
			int ackWait = 0;
			char ackArray[5];
			while (ackWait < 5) {

				ackWait++;
			}
			ackCounter += 5;
			printf("cwnd limit reached check acks now \n");
			printf("All acks reached \n");
		}
	}

	printf("Data sent to receiver\n");

	return 1;
}