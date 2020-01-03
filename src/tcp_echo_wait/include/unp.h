#include    <stdio.h>
#include	<unistd.h>          /* read/write/etc functions */
#include    <stdlib.h>
#include    <signal.h>          /* signal process functions */
#include    <string.h>          /* str functions */
#include    <errno.h>           /* definition of errno */
#include    <stdarg.h>		    /* ISO C variable aruments */
#include	<arpa/inet.h>	    /* inet(3) functions */
#include    <sys/wait.h>        /* wait(2) functions */
#include	<sys/socket.h>      /* basic socket definitions */ 
#include	<netinet/in.h>      /* sockaddr_in{} and other Internet defns */

#define MAXLINE 50
#define LISTENQ 1024

/*
 * own functions
*/
ssize_t						/* Write "n" bytes to a descriptor. */
writen(int, const void *, size_t);

/*
 * own functions wrapper
 */
ssize_t
Readline(int, void *, size_t);

/*
 * error wrapper
 */
void
err_doit(int, int, const char *, va_list);

void
err_quit(const char *, ...);

void
err_sys(const char *, ...);

/*
 * socket wrapper
 */
int		 
Accept(int, struct sockaddr *, socklen_t *);

void	 
Bind(int, const struct sockaddr *, socklen_t);

void	 
Connect(int, const struct sockaddr *, socklen_t);

void	 
Listen(int, int);

int		 
Socket(int, int, int);


/*
 * Unix wrapper
 */
void	 
Close(int);

pid_t	 
Fork(void);

ssize_t	 
Read(int, void *, size_t);

void	 
Write(int, void *, size_t);

void
Writen(int, void *, size_t);

/*
 * Inet wrapper
 */
const char *
Inet_ntop(int, const void *, char *strptr, size_t);

void			 
Inet_pton(int, const char *, void *);

/*
 * stdio wrapper
 */
char *
Fgets(char *, int, FILE *);

void
Fputs(const char *, FILE *);
