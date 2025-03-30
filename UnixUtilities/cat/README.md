# Simple Cat Utility

This repository contains an implementation of a simple version of the `cat` utility, a standard Unix command-line tool used to display the contents of a single file.

## Features

- Display the contents of a single file.
- Mimics basic functionality of the Unix `cat` command for a single file.

## Usage

```bash
./mcat [file]
```

## Example

```bash
# Display contents of a single file
./mcat file.txt
```

## Build

To build the program using CMake, follow these steps:

1. Create a build directory:
    ```bash
    mkdir build && cd build
    ```

2. Run CMake to configure the project:
    ```bash
    cmake ..
    ```

3. Compile the program:
    ```bash
    make
    ```

The compiled executable will be located in the `build` directory.
