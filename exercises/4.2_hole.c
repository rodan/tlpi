
#include <inttypes.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#include "tlpi_hdr.h"

#define DATA_SIZE 500

int main(int argc, char *argv[])
{
    int fdout;
    char fill = 'a';
    int hole = 2000000;
    char buf[DATA_SIZE];
    static char *outfile = "hole.bin";

    memset(buf, fill, DATA_SIZE);

    if ((fdout = open(outfile, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR)) < 0 ) {
        errExit("opening file %s", outfile);
    }

    if (write(fdout, buf, DATA_SIZE) < DATA_SIZE) {
        errExit("writing");
    }

    if (lseek(fdout, hole, SEEK_CUR) < 0) {
        errExit("lseek");
    }

    if (write(fdout, buf, DATA_SIZE) < DATA_SIZE) {
        errExit("writing end");
    }
  
    close(fdout);

    return EXIT_SUCCESS;
}
