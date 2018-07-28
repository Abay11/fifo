#include <iostream>

#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <limits.h>

using namespace std;

int main()
{
    char*in="/home/adygha/Projects/Qt/in.fifo",
            *out="/home/adygha/Projects/Qt/out.fifo";
    int fd_read, fd_write;

    if(mkfifo(in, 0666)==-1 && errno!=EEXIST)
        std::cerr<<"Error creating input pipe!\n";
    if(mkfifo(out, 0666)==-1 && errno!=EEXIST)
        std::cerr<<"Error creating output pipe!\n";


    size_t size;
    char buf[PIPE_BUF];

    while(true)
    {
        fd_read=open(in, O_RDONLY);
        assert(fd_read!=-1);
        bzero(buf, sizeof(buf));
        size=read(fd_read, buf, sizeof(buf));
        assert(size!=-1);
        if(size==0)
        {
            close(fd_read);
            break;
        }
        printf("%s\n",buf);
        if(size==0)
            break;

        fd_write=open(out, O_WRONLY);
        assert(fd_write!=-1);
        size=write(fd_write, buf, size);
        assert(size!=-1);
        close(fd_write);
    }
}
