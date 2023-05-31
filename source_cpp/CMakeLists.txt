# CMakeLists.txt from protobuf/examples
# modified for scg_test

# Minimum CMake required
cmake_minimum_required(VERSION 2.8.12)

# Project
project(scg_test)

message(STATUS "CMAKE_CXX_COMPILER_ID: ${CMAKE_CXX_COMPILER_ID}")

# Determine operating system suffix
if (UNIX AND NOT APPLE)
  message(STATUS "Assuming operating system is Linux-based.")
  set(SCG_OS "linux")
elseif(WIN32)
  message(STATUS "Assuming operating system is Windows.")
  set(SCG_OS "windows")
else()
  message(STATUS "Unknown operating system.  Using \"null\".")
  set(SCG_OS "null")
endif()

# Find required protobuf package
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/protobuf_x64-${SCG_OS}")
find_package(protobuf CONFIG REQUIRED)

if(protobuf_VERBOSE)
  message(STATUS "Using Protocol Buffers ${protobuf_VERSION}")
endif()

set(CMAKE_INCLUDE_CURRENT_DIR TRUE)

# http://www.cmake.org/Wiki/CMake_FAQ#How_can_I_build_my_MSVC_application_with_a_static_runtime.3F
if(MSVC AND protobuf_MSVC_STATIC_RUNTIME)
  foreach(flag_var
      CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
      CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
    if(${flag_var} MATCHES "/MD")
      string(REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
    endif(${flag_var} MATCHES "/MD")
  endforeach()
endif()

foreach(example scg_test)
  set(PROTO_IN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../protodef)
  set(${example}_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/${example}.cpp)
  set(${example}_PROTOS ${PROTO_IN_DIR}/${example}.proto)

  #Code Generation
  set(PROTO_OUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../protodef/protoFiles)
  if(protobuf_MODULE_COMPATIBLE) #Legacy Support
    protobuf_generate_cpp(${PROTO_OUT_DIR}/${example}_PROTO_SRCS ${PROTO_OUT_DIR}/${example}_PROTO_HDRS ${${example}_PROTOS})
    list(APPEND ${example}_SRCS ${${example}_PROTO_SRCS} ${${example}_PROTO_HDRS})
  endif()

  #Executable setup
  set(executable_name ${example}_cpp)
  add_executable(${executable_name} ${${example}_SRCS} ${${example}_PROTOS})
  if(protobuf_MODULE_COMPATIBLE) #Legacy mode
    target_include_directories(${executable_name} PUBLIC ${PROTOBUF_INCLUDE_DIRS})
    target_link_libraries(${executable_name} ${PROTOBUF_LIBRARIES})
  else()
    target_link_libraries(${executable_name} protobuf::libprotobuf)
    protobuf_generate(TARGET ${executable_name}
      IMPORT_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/..
    )
  endif()

# Copy scb_test.pb to build directory
add_custom_command(TARGET ${example}_cpp POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    "${CMAKE_CURRENT_SOURCE_DIR}/../protomessage/scg_test.pb"
    "${CMAKE_CURRENT_BINARY_DIR}/protomessage/scg_test.pb")

# Copy dependencies to binary directory
# Append d to library file name
set(DEBUG_CHAR "")
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(DEBUG_CHAR "d")
endif()
# Determine library extension
if (UNIX AND NOT APPLE)
    set(LIBRARY_EXTENSION ".a")
    set(LIBRARY_DIRECTORY "lib")
elseif(WIN32)
    set(LIBRARY_EXTENSION ".dll")
    set(LIBRARY_DIRECTORY "bin")
else()
    set(LIBRARY_EXTENSION ".")
endif()

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(PROTO_BIN_DIR "${CMAKE_CURRENT_SOURCE_DIR}/protobuf_x64-${SCG_OS}/debug/${LIBRARY_DIRECTORY}")
else()
    set(PROTO_BIN_DIR "${CMAKE_CURRENT_SOURCE_DIR}/protobuf_x64-${SCG_OS}/${LIBRARY_DIRECTORY}")
endif()
add_custom_command(TARGET ${example}_cpp POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    "${PROTO_BIN_DIR}/libprotobuf${DEBUG_CHAR}${LIBRARY_EXTENSION}"
    "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/libprotobuf${DEBUG_CHAR}${LIBRARY_EXTENSION}")
add_custom_command(TARGET ${example}_cpp POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    "${PROTO_BIN_DIR}/libprotobuf-lite${DEBUG_CHAR}${LIBRARY_EXTENSION}"
    "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/libprotobuf-lite${DEBUG_CHAR}${LIBRARY_EXTENSION}")
add_custom_command(TARGET ${example}_cpp POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    "${PROTO_BIN_DIR}/libprotoc${DEBUG_CHAR}${LIBRARY_EXTENSION}"
    "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/libprotoc${DEBUG_CHAR}${LIBRARY_EXTENSION}")

# Determine proper zlib library name
if (UNIX AND NOT APPLE)
    set(ZLIB_LIBRARY "libz${LIBRARY_EXTENSION}")
elseif(WIN32)
    set(ZLIB_LIBRARY "zlib${DEBUG_CHAR}1${LIBRARY_EXTENSION}")
else()
    message(STATUS "Unknown operating system.  Using zlib${DEBUG_CHAR}${LIBRARY_EXTENSION} for the zlib library.")
    set(LIBRARY_EXTENSION "zlib${DEBUG_CHAR}${LIBRARY_EXTENSION}")
endif()

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(ZLIB_BIN_DIR "${CMAKE_CURRENT_SOURCE_DIR}/zlib_x64-${SCG_OS}/debug/${LIBRARY_DIRECTORY}")
else()
    set(ZLIB_BIN_DIR "${CMAKE_CURRENT_SOURCE_DIR}/zlib_x64-${SCG_OS}/${LIBRARY_DIRECTORY}")
endif()
add_custom_command(TARGET ${example}_cpp POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    "${ZLIB_BIN_DIR}/${ZLIB_LIBRARY}"
    "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/${ZLIB_LIBRARY}")

endforeach()
