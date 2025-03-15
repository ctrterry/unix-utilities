#include <iostream>
#include <cstdlib>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        write(STDOUT_FILENO, "wunzip: file1 [file2 ...]\n", 26);
        return 1;
    }

    const int INT_SIZE = sizeof(int); 
    for (int i = 1; i < argc; i++) {
        int fd = open(argv[i], O_RDONLY);
        if (fd < 0) {
            write(STDOUT_FILENO, "wunzip: cannot open file\n", 25);
            return 1;
        }

        while (true) {
            // Check about the read 4 bytes for the run length
            int count;
            ssize_t bytesRead = read(fd, &count, INT_SIZE);
            if (bytesRead == 0) {
                // Check the EOF
                break;
            }
            if (bytesRead < 0) {
                write(STDOUT_FILENO, "wunzip: cannot open file\n", 25);
                close(fd);
                return 1;
            }
            if (bytesRead < INT_SIZE) {
                // Since, when the file was ended unexpectedly, and then just break;
                break;
            }

            // Hand about the 1 bit char 
            char c;
            ssize_t charRead = read(fd, &c, 1);
            if (charRead <= 0) {
                // Check unexpected EOF
                // also check for the read error
                break;
            }
            for (int k = 0; k < count; k++) {
                write(STDOUT_FILENO, &c, 1);
            }
        }
        close(fd);
    }
    return 0;
}
