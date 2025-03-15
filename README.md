# Unix Utilities

---

## Overview

This project involves building simple versions of common UNIX command-line utilities in C++, Trying to deepen understanding of UNIX systems programming.

The utilities implemented include:

- **wcat**: Simplified implementation of the UNIX `cat` command.
- **wgrep**: A minimalistic version of the UNIX `grep` command.
- **wzip & wunzip**: Basic compression and decompression utilities for file management.

---

## Objectives

Through this project, I aim to:

- Strengthen proficiency in C/C++ programming.
- Enhance familiarity with UNIX shell and command-line environments.
- Master fundamental file I/O operations using system calls (`open`, `read`, `write`, `close`).
- Understand basic text processing and file manipulation techniques.
- Develop experience in writing robust, error-handling code compliant with UNIX standards.

---

## Project Structure

```
project_root/
├── wcat.cpp    # Reads and prints file contents (simplified cat)
├── wgrep.cpp   # Searches text files for matching patterns
├── wzip.cpp    # Simple run-length file compression
└── wunzip.cpp  # Decompression utility for files compressed with wzip
```

---

## Compiling the Utilities

To compile each utility, use the provided flags for warnings and errors:

```bash
g++ -g -Wall -Werror -o wcat wcat.cpp
```

---

## Utility Details

### **1. wcat**

- **Purpose:** Reads specified files and prints their contents.
- **Usage:**
  ```bash
  ./wcat file1.cpp file2.cpp
  ```
- **Error Handling:** Outputs "`wcat: cannot open file`" if file open operation fails.

### **Core Learning Points:**
- Using file descriptors and system calls (`open`, `read`, `write`, `close`).
- Handling command-line arguments in C++.

---

## wgrep Utility

- **Description:** Searches for lines containing a specific string across multiple files.
- **Usage:**
  ```bash
  ./wgrep "search_term" file.txt
  ```
- **Error Handling:** Outputs "`wgrep: cannot open file`" on failure to open files.

### **Core Learning Points:**
- Buffer management for processing arbitrary-length lines.
- Using standard input/output for flexible I/O operations.

---

## File Compression: wzip & wunzip

- **wzip** compresses files using run-length encoding, writing output in binary format.
- **wunzip** decompresses files compressed with **wzip**.

**Example usage:**
```bash
./wzip file.txt > compressed.z
./wunzip compressed.z
```

### **Core Learning Points:**
- Binary I/O operations and handling non-ASCII data.
- Implementing compression algorithms (run-length encoding).

---

## Technical Requirements

Each utility must:
- Compile without warnings/errors (`-Wall`, `-Werror`).
- Pass provided test cases and handle additional custom tests.

---

## Technical Skills & Tools

- **Languages:** C/C++
- **System Calls:** `open`, `read`, `write`, `close`
- **Tools:** GCC/G++ compiler, Unix command-line interface
- **Editor:** Familiarity with editors such as Emacs or Vim

---

## Future Improvements

- Extend utilities with additional features (e.g., command-line flags).
- Implement advanced compression algorithms.
- Enhance error handling robustness.

---

## License

Licensed under the MIT License - see [LICENSE](LICENSE) file for details.

---

**[Back to top](#unix-utilities)**

