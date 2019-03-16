
#include <inttypes.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "tlpi_hdr.h"

#define BUF_SIZE 1024

// implement tee with a "-a (append)" option 

int main(int argc, char *argv[])
{
    int opt;
    int fdout;
    char * outfile = NULL;
    int extraflag = O_TRUNC;
    char buf[BUF_SIZE];
    ssize_t cnt;

    while ((opt = getopt(argc, argv, "ao:")) != -1) {
        switch (opt) {
        case 'a':
            extraflag = O_APPEND;
            break;
        case 'o':
            outfile = optarg;
            break;
        default:
            break;
        }
    }

    fdout = open(outfile, O_CREAT | O_WRONLY | extraflag, S_IRUSR | S_IWUSR);
    if (fdout < 0) {
        errExit("opening output file %s", outfile);
    }

    while ((cnt = read(0, buf, BUF_SIZE)) > 0) {
        if (write(1, buf, cnt) < 1) {
            errExit("writing to stdout");
        }
        if (write(fdout, buf, cnt) < 1) {
            errExit("writing to output file %s", outfile);
        }
    }

    if (close(fdout) < 0) {
        errExit("closing output file %s", outfile);
    }

    exit(EXIT_SUCCESS);
}
