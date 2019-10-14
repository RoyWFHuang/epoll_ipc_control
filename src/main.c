#include <pthread.h>
#include <stdlib.h>
#include "PreDefine.h"
#include "IpcCtrl.h"
#include "epolling.h"

void test_event(int fd, void* data)
{
    PRINT_DBG("fd = %d\n", fd );
    //int accfd_int = acceptIpcSocket(fd);
    //PRINT_DBG("accfd_int = %d\n", accfd_int );

    char *buffer = NULL;
    buffer = calloc(1024, sizeof(char));
    int len = read(fd, buffer, 1024);
    PRINT_DBG("buffer[%d] = %s\n", len, buffer);
    free(buffer);
    if(0 == len)
    {
        undefineDeviceEvent(fd);
        epollDelEvent(fd);
    }
}


int main()
{
    pthread_t thread;
    initialEpollDeviceEvent();
    int fd_int = createAndBindIpcSocket("127.0.0.1");
    PRINT_DBG("fd_int = %d\n", fd_int);
    //epollAddEventByFd(fd_int, EPOLLIN | EPOLLET);
    pthread_create(&thread, NULL, epollProcessActivity, NULL);
    setEpollProcessStart();
    listenIpcSocket(fd_int);
    PRINT_DBG("wait accept\n");
    while(1)
    {
        int accfd_int = acceptIpcSocket(fd_int);
        PRINT_DBG("accfd_int = %d\n", accfd_int);
        int index_int = defineDeviceEvent(accfd_int, EVENT_TYPE_READ_WRITE, NULL, &test_event, NULL);
        PRINT_DBG("\n");
        epollAddEvent(index_int, EPOLLIN | EPOLLET);
    }
    return 0;
}