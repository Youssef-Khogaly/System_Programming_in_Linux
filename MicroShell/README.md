# MicroShell

MicroShell is a lightweight shell implementation written in C for Linux systems. It provides basic shell functionalities, including built-in commands, I/O redirection, local and environmental variable management, and more. This project is designed to help users understand the inner workings of a shell and serve as a foundation for further exploration into system programming.

## Features

### Built-in Commands
MicroShell supports the following built-in commands:

- **`cp`**: Copy file.
    ```bash
    cp source.txt destination.txt
    ```
- **`mv`**: move or rename a file
    ```bash
    mv source.txt destination.txt
    ```
- **`cd`**: Change the current working directory.
    ```bash
    cd /path/to/directory
    cd ~
    ```

- **`ls`**: List directory contents.
    ```bash
    ls
    ```

- **`pwd`**: Print the current working directory.
    ```bash
    pwd
    ```

- **`echo`**: Display a line of text or variable values.
    ```bash
    echo "Hello, World!"
    echo $myvar
    ```

- **`cat`**: Concatenate and display file contents.
    ```bash
    cat file.txt
    ```

- **`printenv`**: Print all environment variables.
    ```bash
    printenv
    ```

### I/O Redirection
MicroShell supports input and output redirection:

- **`<`**: Redirect input from a file.
    ```bash
    cat < input.txt
    ```

- **`>`**: Redirect output to a file (overwrite).
    ```bash
    echo "Hello, File!" > output.txt
    ```

- **`2>`**: Redirect error output to a file.
    ```bash
    cp  2> error.log
    ```

### Local Variable Management

- **Set Local Variables**: Assign values to local variables.
    ```bash
    myvar="Hello"
    echo $myvar
    ```

- **Unset Local Variables**: Remove local variables.
    ```bash
    unset myvar
    ```

### Environmental Variable Management

- **Set Environmental Variables**: Export variables to the environment.
    ```bash
    export x=4
    ```

- **Export Local Variables to Environmental Variables**: Add a local variable to the environment.
    ```bash
    myvar="Hello"
    export myvar
    ```

- **Unset Environmental Variables**: Remove environmental variables.
    ```bash
    unsetenv x
    ```

### Build with CMake
MicroShell uses CMake as its build system. To build the project, follow these steps:

1. Clone the GitHub repository:
    ```bash
        git clone https://github.com/Youssef-Khogaly/System_Programming_in_Linux
        cd MicroShell
       ```

2. Create a build directory:
   ```bash
        mkdir build && cd build
        ```

3. Run CMake to configure the project:
   ```bash
        cmake ..
        ```

4. Compile the source code:
   ```bash
        make
        ```

5. Run the shell:
   ```bash
        ./shell
        ```
