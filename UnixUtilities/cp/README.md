# Simple `cp` Command Implementation

This project is a simple implementation of the Unix `cp` command, written in C. The `cp` command is used to copy files and directories in Linux systems. 

## Features

- Copy a single file to a destination file.
- Copy a file to a destination directory.
- Basic error handling for invalid inputs or permissions.

## Usage

1. Build the program using CMake:
    ```bash
    mkdir build
    cd build
    cmake ..
    make
    ```

2. Run the program:
    ```bash
    ./cp source_file destination
    ```

## Example

Copy a file to another file:
```bash
./cp file1.txt file2.txt
```

Copy a file to a directory:
```bash
./cp file1.txt /path/to/destination/
```

## Test Cases

The following scenarios are considered for testing the `cp` command implementation:

1. **Copy file**: Verify that a file is successfully copied to a new file.
2. **Copy large file**: Ensure the program handles large files correctly.
3. **Copy to existing file**: Check if the destination file is overwritten as expected.
4. **Source file doesn't exist**: Confirm that an appropriate error is displayed when the source file is missing.
5. **Invalid argument**: Test the program's behavior with invalid or insufficient arguments.
6. **Smaller new file**: Validate that the destination file is correctly truncated if it exists and is larger than the source file.

## Limitations

- Does not support recursive copying of directories.
