#include <pthread.h>
#include <unistd.h>
#include "PreDefine.h"
#include "IpcCtrl.h"
#include "epolling.h"



int main()
{
    int fd_int = createAndConnectIpcSocket("127.0.0.1");
    ssize_t size = write(fd_int, "it's echo man0\n", 15);
    sleep(1);
    size = write(fd_int, "it's echo man1\n", 15);
    sleep(1);
    close(fd_int);
    return 0;
}