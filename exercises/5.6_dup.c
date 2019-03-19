#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "tlpi_hdr.h"


int main()
{
    int fd1, fd2, fd3;
    char *file = "sample_5.6.bin";

    if ((fd1 = open(file, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR)) < 0) {
        errExit("during fd1 open()");
    }
    if ((fd2 = dup(fd1)) < 0) {
        errExit("during fd2 dup()");
    }
    if ((fd3 = open(file, O_RDWR)) < 0) {
        errExit("during fd3 open()");
    }

    if (write(fd1, "Hello,", 6) != 6) {
        errExit("during write()");
    }
    if (write(fd2, "world", 6) != 6) {
        errExit("during write()");
    }
    if (lseek(fd2, 0, SEEK_SET) == -1) {
        errExit("during write()");
    }
    if (write(fd1, "HELLO,", 6) != 6) {
        errExit("during write()");
    }
    if (write(fd3, "Gidday", 6) != 6) {
        errExit("during write()");
    }

    close(fd3);
    close(fd2);
    close(fd1);
}

