#include "unp.h"

ssize_t						/* Write "n" bytes to a descriptor. */
writen(int fd, const void *vptr, size_t n)
{
	size_t		nleft;		// 剩余需要写入的字节数
	ssize_t		nwritten;	// write函数的返回值
	const char	*ptr;		// 指向接下来要从vptr中读取数据的位置

	ptr = vptr;				// 初始化
	nleft = n;				// 初始化
	while (nleft > 0) {
		if ( (nwritten = write(fd, ptr, nleft)) <= 0) { // 出错或返回值为0
			if (nwritten < 0 && errno == EINTR)
				nwritten = 0;		// 出错，并且errno为EINTR，再次调用write
			else
				return(-1);			// 其他情况，返回-1；
		}

		nleft -= nwritten;			// 更新剩余需要写入的字节数
		ptr   += nwritten;			// 更新指针
	}
	return(n);
}
