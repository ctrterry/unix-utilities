
#include <iostream>
#include <cstdlib>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <string>

bool contains(const std::string & haystack, const std::string &needle) {
    return (haystack.find(needle) != std::string::npos);
}

int main(int argc, char *argv[]) {
    const char * msg = "wgrep: searchterm [file ...]\n";
    const int msgLength = strlen(msg);
    if (argc < 2) {
        write(STDOUT_FILENO, msg, msgLength);
        return 1;
    }

    std::string searchTerm = argv[1];


    const char * msgFileHandling = "wgrep: cannot open file\n";
    const int length = strlen(msgFileHandling);

    if (argc == 2) {
        int fd = STDIN_FILENO;
        std::string accumulator;
        const int BUFSIZE = 4096;
        char buffer[BUFSIZE];

        while (true) {
            ssize_t bytesRead = read(fd, buffer, BUFSIZE);
            if (bytesRead < 0) {
                write(STDOUT_FILENO, msgFileHandling, length);
                return 1;
            }
            if (bytesRead == 0) {
                if (!accumulator.empty()) {
                    if (contains(accumulator, searchTerm)) {
                        write(STDOUT_FILENO, accumulator.c_str(), accumulator.size());
                        write(STDOUT_FILENO, "\n", 1);
                    }
                }
                break;
            }

            for (ssize_t i = 0; i < bytesRead; i++) {
                if (buffer[i] == '\n') {
                    if (contains(accumulator, searchTerm)) {
                        write(STDOUT_FILENO, accumulator.c_str(), accumulator.size());
                        write(STDOUT_FILENO, "\n", 1);
                    }
                    accumulator.clear();
                } else {
                    accumulator.push_back(buffer[i]);
                }
            }
        }

    } else {
        // Since, we have at least one file: argv[2], argv[3], ...
        for (int fileIndex = 2; fileIndex < argc; fileIndex++) {
            int fd = open(argv[fileIndex], O_RDONLY);
            if (fd < 0) {
                // Trying to check the error opening file
                write(STDOUT_FILENO, msgFileHandling, length);
                return 1;
            }

            // Using a accumulate
            std::string accumulator;
            const int BUFSIZE = 4096;
            char buffer[BUFSIZE];

            while (true) {
                ssize_t bytesRead = read(fd, buffer, BUFSIZE);
                if (bytesRead < 0) {
                    write(STDOUT_FILENO, msgFileHandling , length);
                    close(fd);
                    return 1;
                }
                if (bytesRead == 0) {
                    // Check about the EOF
                    if (!accumulator.empty()) {
                        if (contains(accumulator, searchTerm)) {
                            write(STDOUT_FILENO, accumulator.c_str(), accumulator.size());
                            write(STDOUT_FILENO, "\n", 1);
                        }
                    }
                    break;
                }
                // Process  the datas
                for (ssize_t i = 0; i < bytesRead; i++) {
                    if (buffer[i] == '\n') {
                        // we have a full line
                        if (contains(accumulator, searchTerm)) {
                            write(STDOUT_FILENO, accumulator.c_str(), accumulator.size());
                            write(STDOUT_FILENO, "\n", 1);
                        }
                        accumulator.clear();
                    } else {
                        accumulator.push_back(buffer[i]);
                    }
                }
            }

            close(fd);
        }
    }

    return 0;
}
