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
ssize_t	 
Read(int, void *, size_t);

void	 
Write(int, void *, size_t);

void	 
Close(int);