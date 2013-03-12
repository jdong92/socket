#define _POSIX_SOURCE
#define _BSD_SOURCE

#include	<sys/types.h>	/* basic system data types */
#include	<sys/socket.h>	/* basic socket definitions */
#include	<sys/time.h>	/* timeval{} for select() */
#include	<time.h>		/* timespec{} for pselect() */
#include	<netinet/in.h>	/* sockaddr_in{} and other Internet defns */
#include	<arpa/inet.h>	/* inet(3) functions */
#include	<errno.h>
#include	<fcntl.h>		/* for nonblocking */
#include	<netdb.h>
#include	<signal.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include   	<strings.h>     /* for bzero */
#include	<sys/stat.h>	/* for S_xxx file mode constants */
#include	<sys/uio.h>		/* for iovec{} and readv/writev */
#include	<unistd.h>
#include	<sys/wait.h>
#include	<sys/select.h>

#define LISTENQ 1024
#define MAXLINE 4096
#define MAXSOCKADDR 128
#define BUFFSIZE 4096

#define SERV_PORT 9000
#define SERV_PORT_STR "9000"

volatile int stop = 0;

void sigalrm_handler( int sig ){

    stop = 1;
}

int main(int argc, char **argv)
{
    struct sigaction sact;
	int i, j, n, max, perfect_count = 0;
	int sockfd;
	struct sockaddr_in servaddr;
	char sendline[MAXLINE];
	char recvline[MAXLINE];
   
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	sigemptyset(&sact.sa_mask);
    sact.sa_flags = 0;
    sact.sa_handler = sigalrm_handler;
    sigaction(SIGALRM, &sact, NULL);
	
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

	connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

    while(fgets(sendline, MAXLINE, stdin) != NULL){

        bzero(recvline, MAXLINE);
        write(sockfd, sendline, strlen(sendline) + 1);
        if(read(sockfd, recvline, MAXLINE) == 0){
            perror("Something broke");
            exit(-1);
        }
        fputs(recvline, stdout);
    }
    /*

    printf("Querying manage for perfect number ranges. \n");
	alarm(15); 
    while (!stop) {
		for (i = 1;!stop;i++){
		    for (j = 1; j < i && !stop; j++){
		        if (i % j == 0)
		            perfect_count = perfect_count + j;

		    	}
		        if (perfect_count == i){
		    	
                }
	            perfect_count = 0;
		}
    }
    sprintf(sendline, "%d \n", i);
    write(sockfd, sendline, strlen(sendline) + 1);
    for (;;){

          if ((n = read(sockfd, recvline, MAXLINE)) == 0){
              close(sockfd);
              break;
          }else{
              max = atoi(recvline);
              fputs(recvline, stdout);
              break;
          }


    }

    printf("Perfect Number: %d \n", max);
    */
	return 0;
}


