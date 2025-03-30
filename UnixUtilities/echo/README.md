# Echo Utility  

This project implements a simple Unix utility: `echo`. The `echo` command is used to display a line of text or string passed as an argument.  
## Build Instructions  

This project uses `CMake` as the build system. Follow the steps below to build the project:  

1. Clone the repository:  
    ```bash  
    git clone <repository-url>  
    cd echo  
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
    make  
    ```  

## Usage  

After building the project, you can run the `echo` utility as follows:  

```bash  
./echo [STRING...]  
```  
### Examples  
1. Basic usage:  
    ```bash  
    ./echo "Hello, World!"  
    ```  