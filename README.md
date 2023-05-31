# scg_test

SCG Coding Test (May 2023):  Simple test working with Google Protocol Buffers

# Build Instructions

First and foremost, you will need to clone the scg_test repository.
After that, the build instructions vary with the language.
Please follow the build instructions described below for your language of choice.

## C++ Solution

### Linux

* Install CMake
* Open CMake GUI
* Specify the source directory, which is the same location as the CMakeLists.txt
* Specify the build directory
* Add CMAKE_BUILD_TYPE variable with String as its type with Debug as its value
* Click Configure
  * Specify Unix Makefiles as the generator
  * Specify x64 as the platform
  * Click Finish
* Click Generate
* Open Terminal
* Build the project
  * Change directory to the build directory
  * Type `cmake --build . --target all`
  * Press Enter
* Run the scg_test_cpp executable
  * Type `./scg_test_cpp`
  * Press Enter

NOTE:  You can simplify the steps after "Click Generate" if you use an IDE, such as Qt Creator.

### Windows

* Install CMake
* Open CMake GUI
* Specify the source directory, which is the same location as the CMakeLists.txt
* Specify the build directory
* Add CMAKE_BUILD_TYPE variable with String as its type with Debug as its value
* Click Configure
  * Specify Visual Studio 17 2022 as the generator
  * Specify x64 as the platform
  * Click Finish
* Click Generate
* Click Open Solution
* Build the solution
* Run the scg_test target

## C# Solution

* Open the scg_test.sln in the source_cs folder
* Build the solution
* Run the scg_test target
