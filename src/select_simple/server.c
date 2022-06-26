#include <time.h>
#include <sys/select.h>
#include <sys/time.h>
#include "unp.h"

void TestTimeout() 
{
    struct timeval t;

    t.tv_sec = 10;
    t.tv_usec = 0;

    select(0, NULL, NULL, NULL, &t);
}

void TestFDTimeout()
{
    struct timeval t;

    t.tv_sec = 10;
    t.tv_usec = 0;

    fd_set fset;

    FD_ZERO(&fset);
    FD_SET(fileno(stdin), &fset);

    int val;
    val = select(fileno(stdin)+1, &fset, NULL, NULL, &t);

    if (FD_ISSET(fileno(stdin), &fset)) {
        char in[30];
        Fgets(in, 30, stdin);

        char str[30];
        sprintf(str, "sec:%d usec:%d\n", t.tv_sec, t.tv_usec);
        Fputs(str, stdout);
    }

}

void TestFD() 
{
    fd_set fset;

    printf("fdset[0] is %d.\n", fset.__fds_bits[0]);

    FD_SET(3, &fset);

    printf("fdset[0] is %d, after set 3.\n", fset.__fds_bits[0]);
}

void PrintCurTime()
{
    time_t cur;
    struct tm* timeinfo;

    time(&cur);
    timeinfo = localtime(&cur);
    
    char str[30];
    sprintf(str, "%s", asctime(timeinfo));
    Fputs(str, stdout);
}

int main()
{
    PrintCurTime();

    // TestTimeout();
    // TestFDTimeout();
    TestFD();

    PrintCurTime();
    return 0;
}
