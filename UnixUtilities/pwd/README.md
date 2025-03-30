# pwd: Print Working Directory

`pwd` is a simple utility that prints the current working directory of the user

## Features

- Prints the absolute path of the current working directory.

## Requirements

- CMake 3.10 or higher
- A C compiler (e.g., GCC or Clang)

## Build Instructions

1. Clone the repository:
    ```bash
    git clone <repository-url>
    cd pwd
    ```

2. Create a build directory and navigate to it:
    ```bash
    mkdir build
    cd build
    ```

3. Run CMake to configure the project:
    ```bash
    cmake ..
    ```

4. Build the project:
    ```bash
    cmake --build .
    ```

## Usage

After building the project, you can run the `pwd` utility as follows:

```bash
./pwd
```

This will print the absolute path of the current working directory.