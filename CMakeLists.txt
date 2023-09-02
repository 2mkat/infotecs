cmake_minimum_required(VERSION 3.16)
project(infotecs)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

add_executable(client first_app/client.h first_app/client.cpp first_app/main.cpp)
target_link_libraries(client Threads::Threads)
add_executable(server second_app/server.h second_app/server.cpp second_app/main.cpp)