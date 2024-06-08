cmake_minimum_required(VERSION 3.12)

project(tinyfiledialogs)

add_library(tinyfiledialogs STATIC 
	include/tinyfiledialogs.h
	src/tinyfiledialogs.c
)

target_include_directories(tinyfiledialogs PUBLIC include)