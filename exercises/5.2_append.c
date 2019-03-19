
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

#include "tlpi_hdr.h"

int main()
{
    int fd;
    const char *infile="hole_copy.bin";
    const char *msg="hello";

    if ((fd = open(infile, O_WRONLY | O_APPEND)) < 0) {
        errExit("during open(%s, .. )", infile);
    }

    if (lseek(fd, 0, SEEK_SET) < 0) {
        errExit("during lseek()");
    }

    if (write(fd, msg, strlen(msg)) != strlen(msg)) {
        errExit("during write()");
    }

    close(fd);

    return EXIT_SUCCESS;
}


