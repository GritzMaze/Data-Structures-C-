cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(tests)

set(SOURCES
	common/catch.hpp

	interface.h
	tests.cpp

	myStore.cpp
	event.h
	priorityQueue.h

)

add_executable(${PROJECT_NAME} ${SOURCES})

add_executable(main
				main.cpp
				interface.h
				myStore.cpp
				event.h
				priorityQueue.h
)

target_include_directories(${PROJECT_NAME} PRIVATE /common)