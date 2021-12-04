cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(tests)

set(SOURCES
	common/catch.hpp

	interface.h
	tests.cpp

	myStore.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

add_executable(main
				main.cpp
				interface.h
				myStore.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE /common)