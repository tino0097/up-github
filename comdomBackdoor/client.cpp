#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>

void gotoxy(int x,int y){
 printf("%c[%d;%df",0x1B,y,x);
 }
 
int main(int argc, char *argv[]){
	system("clear");
	
	char command[1024];
    int sockfd = 0;
    int bytesReceived = 0;
    char recvBuff[1024];
    memset(recvBuff, '0', sizeof(recvBuff));
    struct sockaddr_in serv_addr;

    /* Create a socket*/
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        printf("Oop!!! Could not create socket \n");
        return 1;
    }

    /* Initialize sockaddr_in data structure */
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(5000); // port
    
    char ip[15];
	if (argc < 2) {
		printf("Enter IP address to connect: ");
		scanf("%[^\n]",ip);
	}
	else
		strcpy(ip,argv[1]);

    serv_addr.sin_addr.s_addr = inet_addr(ip);

    /* Attempt a connection */
    if(connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr))<0){
        printf("Error : Connect Failed \n");
        return 1;
    }

    printf("Connected to IP: %s : %d\n",inet_ntoa(serv_addr.sin_addr),ntohs(serv_addr.sin_port));
    
    /*Send command*/
	printf("Command to server: \n");
	scanf("%[^\n]",command);
	if(send(sockfd, command, sizeof(command), 0) < 0){
		perror("Send command failed");
		close(sockfd);
		exit(1);
	}
	else printf("Send command success\n");
	
   	 /* Create file where data will be stored */
    FILE *fp;
	char fname[100];
	unsigned long fsize = 0;
	char fsz[20];
	
	
	read(sockfd, fname, 256);
	read(sockfd, fsz, 20);
	
	
	printf("File Name: %s\n",fname);
	printf("File Size: %s   bytes\n",fsz);
	char *ps, *ptr;
	ps = fsz;
	fsize = strtol(ps, &ptr, 10);
	printf("Receiving file...");
   	fp = fopen(fname, "ab"); 
   	 
    if(fp == NULL){
       	printf("Error opening file\n");
        return 1;
    }
    long double sz = 1;
    
    /* Receive data in chunks of 256 bytes */
    while((bytesReceived = read(sockfd, recvBuff, 1024)) > 0){ 
        sz++;
        gotoxy(0,5);
        printf("Received:%llf  Mb",(sz/1000));
        gotoxy(0,6);
        unsigned long int per = (unsigned long) sz*1024;
        float pers = ((float)per/(float)fsize) * 100;
        printf("Completed: [%0.2f%]     \n",pers);
		fflush(stdout);
        fwrite(recvBuff, 1, bytesReceived, fp);
    }

    if(bytesReceived < 0){
        printf("\n Read Error \n");
    }
    
    printf("File OK....Completed\n");
    return 0;
}
