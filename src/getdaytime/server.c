#include	<time.h>
#include    <stdio.h>
#include	<unistd.h>          /* read/write/etc functions */
#include    <stdlib.h>
#include    <string.h>          /* str functions */
#include    <errno.h>           /* definition of errno */
#include    <stdarg.h>		    /* ISO C variable aruments */
#include	<arpa/inet.h>	    /* inet(3) functions */
#include	<sys/socket.h>      /* basic socket definitions */ 
#include	<netinet/in.h>      /* sockaddr_in{} and other Internet defns */

#define MAXLINE 50
#define LISTENQ 1024

void
err_doit(int errnoflag, int error, const char *fmt, va_list ap)
{
	char	buf[MAXLINE];

	vsnprintf(buf, MAXLINE-1, fmt, ap);
	if (errnoflag)
		snprintf(buf+strlen(buf), MAXLINE-strlen(buf)-1, ": %s",
		  strerror(error));
	strcat(buf, "\n");
	fflush(stdout);
	fputs(buf, stderr);
	fflush(NULL);
}

void
err_quit(const char *fmt, ...)
{
	va_list		ap;

	va_start(ap, fmt);
	err_doit(0, 0, fmt, ap);
	va_end(ap);
	exit(1);
}

void
err_sys(const char *fmt, ...)
{
	va_list		ap;

	va_start(ap, fmt);
	err_doit(1, errno, fmt, ap);
	va_end(ap);
	exit(1);
}

int
main(int argc, char **argv)
{
	int					listenfd, connfd;
	struct sockaddr_in	servaddr;
	char				buff[MAXLINE];
	time_t				ticks;

	if( (listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		err_sys("socket error");

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port        = htons(13);

	if(bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0)
        err_sys("bind error");

	if(listen(listenfd, LISTENQ) < 0)
        err_sys("listen error");

	for ( ; ; ) {
		if( (connfd = accept(listenfd, (struct sockaddr *) NULL, NULL)) < 0) {
			if(errno == EPROTO || errno == ECONNABORTED)
				continue;
			else
				err_sys("accept error");
		}

        ticks = time(NULL);
        snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
        if( write(connfd, buff, strlen(buff)) != strlen(buff))
			err_sys("write error");

		if (close(connfd) == -1)
			err_sys("close error");
	}

	if (close(listenfd) == -1)
		err_sys("close error");
}
