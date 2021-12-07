cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(tests)

set(SOURCES
	common/catch.hpp

	headers/interface.h
	source/tests.cpp

	source/myStore.cpp
	headers/event.h
	headers/priorityQueue.h

)

add_executable(${PROJECT_NAME} ${SOURCES})

add_executable(main
				main.cpp
				headers/interface.h
				source/myStore.cpp
				headers/event.h
				headers/priorityQueue.h
)

target_include_directories(${PROJECT_NAME} PRIVATE /common)