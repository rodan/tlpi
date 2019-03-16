
#include <inttypes.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "tlpi_hdr.h"

#define BUF_SIZE 512

uint8_t empty_buf(char *buff, int size);



// cp from infile to outfile and detect holes
int main(int argc, char *argv[])
{
    int fdin, fdout;
    char *infile = NULL;
    char *outfile = NULL;
    int opt;
    char buf[BUF_SIZE];
    ssize_t cnt;
    uint8_t detect_holes = 0;
    ssize_t seek_cnt = 0;

    while ((opt = getopt(argc, argv, "di:o:")) != -1) {
        switch (opt) {
        case 'd':
            detect_holes = 1;
            break;
        case 'i':
            infile = optarg;
            break;
        case 'o':
            outfile = optarg;
            break;
        default:
            break;
        }
    }

    if ((fdin = open(infile, O_RDONLY)) < 0) {
        errExit("opening input file");
    }

    if ((fdout = open(outfile, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR)) < 0) {
        errExit("opening output file");
    }

    while ((cnt = read(fdin, buf, BUF_SIZE)) > 0) {
        if (detect_holes) {
            if (!empty_buf(buf, cnt)) {
                if (lseek(fdout, seek_cnt*BUF_SIZE, SEEK_SET) < 0) {
                    errExit("during lseek");
                }
                if (write(fdout, buf, cnt) != cnt) {
                    errExit("during write");
                }
            }
        } else {
            if (write(fdout, buf, cnt) != cnt) {
                errExit("during write");
            }
        }
        seek_cnt++;
    }

    close(fdin);
    close(fdout);
}

// returns 1 if buff contains all zeroes
uint8_t empty_buf(char *buff, int size)
{
    int i;

    for (i=0; i<size; i++) {
        if (buff[i]) {
            return 0;
        }
    }
    return 1;
}


