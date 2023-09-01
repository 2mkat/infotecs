cmake_minimum_required(VERSION 3.16)
project(infotecs)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

add_executable(server first_app/server.h first_app/server.cpp first_app/main.cpp)
target_link_libraries(server Threads::Threads)
add_executable(client second_app/client.h second_app/client.cpp second_app/main.cpp)