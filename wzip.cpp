#include <iostream>
#include <cstdlib>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>

void writeRun(int count, char c) {
    write(STDOUT_FILENO, &count, sizeof(int));
    write(STDOUT_FILENO, &c, 1);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        write(STDOUT_FILENO, "wzip: file1 [file2 ...]\n", 24);
        return 1;
    }

    int fd;
    const int BUFSIZE = 4096;
    char buffer[BUFSIZE];
    bool firstChar = true;
    char currentChar;
    int count = 0;

    for (int i = 1; i < argc; i++) {
        fd = open(argv[i], O_RDONLY);
        if (fd < 0) {
            write(STDOUT_FILENO, "wzip: cannot open file\n", 23);
            return 1;
        }

        while (true) {
            ssize_t bytesRead = read(fd, buffer, BUFSIZE);
            if (bytesRead < 0) {
                // read for error
                write(STDOUT_FILENO, "wzip: cannot open file\n", 23);
                close(fd);
                return 1;
            }
            if (bytesRead == 0) {
                // check EOF
                break;
            }

            for (ssize_t j = 0; j < bytesRead; j++) {
                if (firstChar) {
                    currentChar = buffer[j];
                    count = 1;
                    firstChar = false;
                } else {
                    if (buffer[j] == currentChar) {
                        count++;
                    } else {
                        writeRun(count, currentChar);
                        currentChar = buffer[j];
                        count = 1;
                    }
                }
            }
        }
        close(fd);
    }

    // Handling about after processing all files
    // Then flush the last run if we have one
    if (!firstChar) {
        writeRun(count, currentChar);
    }

    return 0;
}
