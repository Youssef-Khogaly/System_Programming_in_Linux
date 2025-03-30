# mv Utility

This project implements a custom version of the `mv` command, a Unix utility used to move or rename files and directories.

## Compilation

To compile the project using CMake, follow these steps:

1. Ensure you have CMake and a C compiler (e.g., `gcc`) installed on your system.
2. Navigate to the project directory:
    ```bash
    cd yourPath/UnixUtilities/mv
    ```
3. Create a build directory and navigate into it:
    ```bash
    mkdir build && cd build
    ```
4. Generate the build files using CMake:
    ```bash
    cmake ..
    ```
5. Compile the project:
    ```bash
    make 
    ```
6. The compiled executable will be located in the `build` directory and can be run from the terminal.

## Usage

Run the compiled `mv` utility with appropriate arguments to move or rename files:
```bash
./mv [source] [destination]
```

## Notes

- Ensure you have the necessary permissions to move or rename the specified files or directories.
- This implementation may not support all features of the standard `mv` utility.
