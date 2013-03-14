#define _POSIX_SOURCE
#define _BSD_SOURCE

#include <sys/types.h>	/* basic system data types */
#include <sys/socket.h>	/* basic socket definitions */
#include <sys/time.h>	/* timeval{} for select() */
#include <time.h>		/* timespec{} for pselect() */
#include <netinet/in.h>	/* sockaddr_in{} and other Internet defns */
#include <arpa/inet.h>	/* inet(3) functions */
#include <errno.h>
#include <fcntl.h>		/* for nonblocking */
#include <netdb.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>     /* for bzero */
#include <sys/stat.h>	/* for S_xxx file mode constants */
#include <sys/uio.h>		/* for iovec{} and readv/writev */
#include <unistd.h>
#include <sys/wait.h>
#include <sys/select.h>

#define LISTENQ 1024
#define MAXLINE 4096
#define MAXSOCKADDR 128
#define BUFFSIZE 4096

#define SERV_PORT 9050
#define SERV_PORT_STR "9050"
#define SECONDS 15

volatile int stop = 0;
int *perfect_num[1000];
char sendline[MAXLINE];
char recvline[MAXLINE];

int performance(){
   
    int i, j, test = 0;
    printf("Querying manage for perfect number ranges. \n");
	alarm(SECONDS); 
    while (!stop) {
		for (i = 1;!stop;i++){
            for (j = 1; j < i; j++){
                if (i % j == 0)
                    test = 1;
            }
        }
    }
    return i;
}

void perfect_number(int sockfd, int operations){

    int i, j, perfect_count;
    for (i = 1; i < operations; i++){
        for (j = 1; j < i; j++){
            if (i % j == 0)
                perfect_count = perfect_count + j;
        }
        if (perfect_count == i){ 
            sprintf(sendline, "C#%d", perfect_count);
            write(sockfd, sendline, strlen(sendline) + 1);
        }
        perfect_count = 0;

    }

}

void sigalrm_handler(int sig){

    stop = 1;
}

int main(int argc, char **argv)
{
	struct sigaction sact;
    	int i;
	int sockfd, operations, max_op;
	struct sockaddr_in servaddr;
       
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

    /*Signal Handler */
	sigemptyset(&sact.sa_mask);
    	sact.sa_flags = 0;
    	sact.sa_handler = sigalrm_handler;
    	sigaction(SIGALRM, &sact, NULL);
	
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

	connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

   	printf("Compute starting. Testing system performance. \n");
    	operations = performance();
    	printf("Performance is %d operations in %d seconds. \n", operations, SECONDS);

<<<<<<< HEAD
    sprintf(sendline, "%d", operations);
    /* Send Maximum Operation */
    write(sockfd, sendline, strlen(sendline) + 1);
 
    read(sockfd, recvline, MAXLINE);
    max_op = atoi(recvline);
    printf("Maximum operations: %d \n", max_op);
    perfect_number(sockfd, max_op);

    printf("Done \n");
=======
    	sprintf(sendline, "%d \n", operations);
    	write(sockfd, sendline, strlen(sendline) + 1);
 
    	read(sockfd, recvline, MAXLINE);
    	max_op = atoi(recvline);
    	printf("Maximum operations: %d \n", max_op);
    	perfect_number(max_op, array);

    /*Send array of the result report.py */
    	printf("Done \n");
>>>>>>> 44f1a07ab9e2ffbcc0888cdffff092379ac51e58

    	close(sockfd);         
     
	return 0;
}


