cmake_minimum_required(VERSION 3.14)
project(CLION_SaveState)

set(CMAKE_CXX_STANDARD 14)

add_executable(CLION_SaveState main.cpp Serializable.cpp Serializable.h SerializationManager.h SerializationManager.cpp LinkedList.cpp LinkedList.h Student.cpp Student.h PointerObj.h)