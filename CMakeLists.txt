# CMakeLists.txt from protobuf/examples
# modified for scg_test

# Minimum CMake required
cmake_minimum_required(VERSION 2.8.12)

# Project
project(scg_test)

# Find required protobuf package
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "C:/vcpkg-2023.04.15/packages/protobuf_x64-windows")
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
  set(PROTO_IN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/protodef)
  set(${example}_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/${example}.cpp)
  set(${example}_PROTOS ${PROTO_IN_DIR}/${example}.proto)

  #Code Generation
  set(PROTO_OUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/protodef/protoFiles)
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
    protobuf_generate(TARGET ${executable_name})
  endif()

set(PROTO_BIN_DIR "C:/vcpkg-2023.04.15/packages/protobuf_x64-windows/debug/bin")
add_custom_command(TARGET ${example}_cpp POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    "${PROTO_BIN_DIR}/libprotobufd.dll"
    "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/libprotobufd.dll")
add_custom_command(TARGET ${example}_cpp POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    "${PROTO_BIN_DIR}/libprotobuf-lited.dll"
    "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/libprotobuf-lited.dll")
add_custom_command(TARGET ${example}_cpp POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    "${PROTO_BIN_DIR}/libprotocd.dll"
    "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/libprotocd.dll")
set(ZLIB_BIN_DIR "C:/vcpkg-2023.04.15/packages/zlib_x64-windows/debug/bin")
add_custom_command(TARGET ${example}_cpp POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    "${ZLIB_BIN_DIR}/zlibd1.dll"
    "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/zlibd1.dll")

endforeach()
