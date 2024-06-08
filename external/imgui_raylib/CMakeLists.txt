cmake_minimum_required(VERSION 3.12)

project(imgui_raylib)

add_library(imgui_raylib STATIC
	include/imgui_impl_raylib.h
	src/imgui_impl_raylib.cpp
)

target_include_directories(imgui_raylib PUBLIC include src)