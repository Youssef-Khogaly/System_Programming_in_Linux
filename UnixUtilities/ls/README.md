# Simple `ls` Command Implementation

This repository contains a simple implementation of the Unix `ls` command. The `ls` command is used to list files and directories in a specified directory. This project is designed to provide a basic understanding of how the `ls` command works under the hood.

## Features

- Lists files and directories in the current or specified directory.
- Mimics the basic functionality of the Unix `ls` command.
- Lightweight and easy to understand for educational purposes.

## Getting Started

### Prerequisites

- A Linux-based operating system.
- GCC or any C compiler installed.
- CMake 
### Installation

1. Clone the repository:
    ```bash
    git clone https://github.com/Youssef-Khogaly/System_Programming_in_Linux

    cd UnixUtilities/ls/
    ```

2. Create a build directory and navigate to it:
    ```bash
    mkdir build && cd build
    ```

3. Generate the build files using CMake:
    ```bash
    cmake ..
    ```

4. Build the project:
    ```bash
    make
    ```

### Usage

Run the program to list files in the current directory:
```bash
./ls
```

To list files in a specific directory:
```bash
./ls /path/to/directory
```

To list multiple files or directories:
```bash
./ls /path/to/file1 /path/to/file2 /path/to/directory
```