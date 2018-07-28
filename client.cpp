#include <iostream>

#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>


using namespace std;

int main()
{
    char*out="/home/adygha/Projects/Qt/in.fifo",
            *in="/home/adygha/Projects/Qt/out.fifo";
    char buf[PIPE_BUF];
    bzero(buf, sizeof(buf));
    strcpy(buf, "First test");

    printf("%s send\n", buf);

    int fd_write, fd_read, res;

    if(mkfifo(in, 0666)==-1 && errno!=EEXIST)
        std::cerr<<"Error creating input pipe!\n";

    if(mkfifo(out, 0666)==-1 && errno!=EEXIST)
        std::cerr<<"Error creating output pipe!\n";

    fd_write=open(out, O_WRONLY);
    assert(fd_write!=-1);
    res=write(fd_write, buf, strlen(buf));
    assert(res!=-1);
    close(fd_write);

    bzero(buf, sizeof(buf));

    fd_read=open(in, O_RDONLY);
    assert(fd_read!=-1);
    res=read(fd_read, buf, sizeof(buf));
    assert(res!=-1);
    close(fd_read);

    printf("%s received\n", buf);

}
