# cd Command Implementation

This repository contains an implementation of the `cd` (change directory) command in Linux.

## Features

- Change the current working directory.
- Handle relative and absolute paths.
- Error handling for invalid paths or permissions.

## Getting Started

### Prerequisites

- A Linux-based operating system.
- CMake (minimum version 3.10)
- requires GCC or any compatible C compiler.


This project implements a custom `cd` command for navigating directories in a Unix-like environment. 
It supports the following functionalities:
- `cd .` to stay in the current directory.
- `cd /` to navigate to the root directory.
- `cd ~` to navigate to the user's home directory.
- `cd ..` to move to the parent directory.
- Includes error handling for scenarios such as:
    - Invalid directory paths.
    - Insufficient permissions to access a directory.
    - Missing arguments or incorrect usage.

The project is built using 
### Installation

1. Clone the repository:
    ```bash
    git clone https://github.com/Youssef-Khogaly/System_Programming_in_Linux
    ```
2. Navigate to the project directory:
    ```bash
    cd UnixUtilities/cd/
    ```
3. Build the project using CMake:
    ```bash
    mkdir build && cd build
    cmake ..
    make
    ```

## Usage

```bash
./cd /path/to/directory
```
