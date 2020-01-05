#include	"unp.h"

#define SERV_PORT 9877

void 
str_echo(int sockfd)
{
	ssize_t		n;
	char		buf[MAXLINE];

	for( ; ; )
	{
		while( (n = read(sockfd, buf, MAXLINE)) > 0)
			Writen(sockfd, buf, n);

		if(n < 0 && errno == EINTR)
			continue;
		else if(n < 0)
			err_sys("str_echo: read error");
		else
			break;
	}
}

/* 错误的版本
void sig_child(int signo)
{
	pid_t		pid;
	int			stat;

	pid = wait(&stat);
	printf("child %d terminated\n", pid);

	return;
}
*/

// 正确的版本
void
sig_child(int signo)
{
	pid_t	pid;
	int		stat;
	printf("in sig_child\n");
	while( (pid = waitpid(-1, &stat, WNOHANG)) > 0)
		printf("child %d terminated\n", pid);
	return;
}

typedef void Sigfunc(int);
Sigfunc * Signal(int signo, Sigfunc *func)
{
	struct sigaction act, oact;

	act.sa_handler = func;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	if(signo == SIGALRM)
	{
#ifdef SA_INTERRUPT
		act.sa_flags |= SA_INTERRUPT;
#endif
	}
	else
	{
#ifdef SA_RESTART
		act.sa_flags |= SA_RESTART;
#endif
	}
	if(sigaction(signo, &act, &oact) < 0)
		return (SIG_ERR);

	return (oact.sa_handler);
}

int
main(int argc, char **argv)
{
	int					listenfd, connfd;
	pid_t				childpid;
	socklen_t			clilen;
	struct sockaddr_in	cliaddr, servaddr;

	listenfd = Socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port        = htons(SERV_PORT);

	Bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

	Listen(listenfd, LISTENQ);

	Signal(SIGCHLD, sig_child);// 取消注释 或者 使用系统提供的signal函数

	for ( ; ; ) {
		clilen = sizeof(cliaddr);
		// connfd = Accept(listenfd, (struct sockaddr *) &cliaddr, &clilen);
		
		if( (connfd = accept(listenfd, (struct sockaddr *) &cliaddr, &clilen)) < 0)
		{
			if(errno ==EINTR)
				continue;
			else
				err_sys("accept error");
		}

		if ( (childpid = Fork()) == 0) {	/* 子进程 */
			Close(listenfd);	/* 关闭监听套接字 */
			str_echo(connfd);	/* 处理请求 */
			exit(0);
		}
		Close(connfd);			/* 父进程关闭连接套接字 */
	}
}
