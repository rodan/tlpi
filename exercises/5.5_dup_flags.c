#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <fcntl.h>

#include "tlpi_hdr.h"


int main()
{
    int fd1, fd2;
    char *file = "sample_5.5.bin";

    if ((fd1 = open(file, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR)) < 0) {
        errExit("during fd1 open()");
    }
    if ((fd2 = dup(fd1)) < 0) {
        errExit("during fd2 dup()");
    }

    if (write(fd1, "Hello ", 6) != 6) {
        errExit("during write()");
    }

    printf("flags for fd1 are 0x%x, flags for fd2 are 0x%x\n",  fcntl(fd1, F_GETFL),  fcntl(fd2, F_GETFL));    

    if (write(fd2, "world", 6) != 6) {
        errExit("during write()");
    }

    close(fd2);
    close(fd1);
}

