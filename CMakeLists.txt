cmake_minimum_required(VERSION 3.14)
project(SaveStateProject_DynamicStatic)

set(CMAKE_CXX_STANDARD 14)

add_executable(SaveStateProject_DynamicStatic main.cpp Serializable.cpp Serializable.h SerializationManager.h Singleton.h LinkedList.cpp LinkedList.h Student.cpp Student.h PointerObj.h)