#include <iostream>
#include <cstdlib>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>

int main(int argc, char *argv[]) {

    // Run with no file input
    const int NOFILEINPUT = 2;
    if (argc < NOFILEINPUT) {
        return 0; 
    }

    // Since, the 4096 is most of filesystem common numbers
    const int BUFFERSIZE = 4096;
    char buffer[BUFFERSIZE];

    // Null -> Need put input a next line \n. Fixed it 
    for (int i = 1; i < argc; i++) {
        const char *OUTPUTCASE = "wcat: cannot open file\n";
        const int OUTPUTCASESIZE = strlen(OUTPUTCASE);
        // Open the file and need O_RDONLY model 
        int fd = open(argv[i], O_RDONLY);
        if (fd < 0) {
            write(STDOUT_FILENO, OUTPUTCASE, OUTPUTCASESIZE);
            return 1;  
        }

        while (true) {
            ssize_t ret = read(fd, buffer, BUFFERSIZE);
            // Handling about the unsuccessful case
            if (ret < 0) {
                write(STDOUT_FILENO, OUTPUTCASE, OUTPUTCASESIZE);
                close(fd);
                return 1;
            }
            // Handling about the EOF case
            if (ret == 0) {
                break;
            }

            // Null -> Need put input a next line \n. Fixed it 
            const char *WRITEERRORHANDLE = "wcat: write error\n";
            const int WRITEERRORHANDLESIZE = strlen(WRITEERRORHANDLE);
            // Write to STDOUT
            ssize_t bytesWritten = write(STDOUT_FILENO, buffer, ret);
            if (bytesWritten < 0) {
                // Write error
                write(STDOUT_FILENO, WRITEERRORHANDLE, WRITEERRORHANDLESIZE);
                close(fd);
                return 1;
            }
        }
        close(fd);
    }
    return 0; 
}

