#define _FILE_OFFSET_BITS 64

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#include "tlpi_hdr.h"

int main(int argc, char **argv)
{
    char *file = NULL;
    int fd = -1;
    int flag = O_APPEND;
    ssize_t num_bytes = 100, wr_counter;
    char *fill_byte;

    printf("int size is %ld, long size is %ld, off_t size is %ld\n", sizeof(int), sizeof(long), sizeof(off_t) );

    if (argc < 4) {
        usageErr("filename num_bytes fill_byte [x]\n");
    }

    file = argv[1];

    if (argv[3] != NULL) {
        fill_byte = argv[3];
    }

    if (argv[4] != NULL) {
        flag = 0;
    }

    num_bytes = atol(argv[2]);

    if ((fd = open(file, flag | O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR)) < 0) {
        errExit("during open(file, ... )", file);
    }

    wr_counter = num_bytes;
    while (wr_counter) {
        if (!flag) {
            if (lseek(fd, 0, SEEK_END) == -1) {
                errExit("during lseek()");
            }
        }
        if (write(fd, fill_byte, 1) != 1) {
            errExit("during write()");
        }
        wr_counter--;
    }

    return EXIT_SUCCESS;
}
