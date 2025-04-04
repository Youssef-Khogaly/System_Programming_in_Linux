# NanoShell

## Requirements
- CMake 3.10 or higher
- GCC or any C compiler

## EnvPath
Update _ENV_PATH_ macro in shell.h file to absolute path to  NanoShell/bin directory
## Building NanoShell

To build NanoShell, follow these steps:

1. Clone the repository:
    ```bash
    git clone https://github.com/Youssef-Khogaly/System_Programming_in_Linux.git
    ```

2. Navigate to the project directory:
    ```bash
    cd NanoShell
    ```

3. Create a build directory and navigate into it:
    ```bash
    mkdir build && cd build
    ```

4. Build the project using CMake:
    ```bash
    cmake .. && make
    ```

5. Run the project:
    ```bash
    ./shell
    ```
