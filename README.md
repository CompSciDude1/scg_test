# scg_test

SCG Coding Test (May 2023):  Simple test working with Google Protocol Buffers

# Build Instructions

First and foremost, you will need to clone the scg_test repository.
Use your favorite version control tool to clone it.
After that, the build instructions vary with the language.
Please follow the build instructions described below for your language of choice.

## C++ Solution

### Linux

Make sure you have the following software installed:

* CMake
* g++
* Qt Creator (optional)

Now, to build scg_test, do the following:

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

#### Qt Creator

If you have Qt Creator installed, then it simplifies the steps:

* Open CMakeLists.txt in the source_cpp as the project
* Click Configure Project
* Build the project
  * Click Build
* Run the scg_test_cpp executable
  * Click Run

### Windows

Make sure you have the following software installed:

* CMake
* Visual Studio 2022 (with C++ desktop development tools)
* Qt Creator (optional)

Now, to build scg_test, do the following:

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

#### Qt Creator

If you have Qt Creator installed, then it simplifies the steps.  However, you still need MSVC installed, so it might be better to stick with Visual Studio.  If you do choose to use Qt Creator, the steps are the same as the Qt Creator section under the Linux section.

NOTE:  Currently, this project does not support Clang.

## C# Solution

Make sure you have the following software installed:

* Visual Studio 2022 (with C# desktop development tools)

Now, to build scg_test, do the following:

* Open the scg_test.sln in the source_cs folder
* Build the solution
* Run the scg_test target
