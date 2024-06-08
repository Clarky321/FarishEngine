# Установка минимальной версии CMake
cmake_minimum_required(VERSION 3.12)

# Определение названия проекта FarishEngineCore
set(ENGINE_PROJECT_NAME FarishEngineCore)

# Список публичных заголовочных файлов
set(ENGINE_PUBLIC_INCLUDES

	includes/FarishEngineCore/IsometricMap.h
	includes/FarishEngineCore/Tile.h
	includes/FarishEngineCore/Camera.h
	includes/FarishEngineCore/Input.h
	includes/FarishEngineCore/Utils.h

	includes/FarishEngineCore/UIModule.h
)

# Список приватных исходных файлов
set(ENGINE_PRIVATE_SOURCES

	src/FarishEngineCore/IsometricMap.cpp
	src/FarishEngineCore/Camera.cpp
	src/FarishEngineCore/Input.cpp
	src/FarishEngineCore/Utils.cpp
	
	src/FarishEngineCore/UIModule.cpp
)

# Общий список исходных файлов
set(ENGINE_ALL_SOURCE
	${ENGINE_PUBLIC_INCLUDES}
	${ENGINE_PRIVATE_SOURCES}
)

# Создание статической библиотеки с названием FarishEngineCore
add_library(${ENGINE_PROJECT_NAME} STATIC ${ENGINE_ALL_SOURCE})

# Группировка файлов в структуру проекта в IDE
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${ENGINE_ALL_SOURCE})

# Добавление путей к заголовочным файлам для внешних пользователей и для компиляции
target_include_directories(${ENGINE_PROJECT_NAME}
	PUBLIC
		includes
	PRIVATE
		src
)

# Установка стандарта C++ для компиляции
target_compile_features(${ENGINE_PROJECT_NAME} PUBLIC cxx_std_17)

# ------------------------------------------------------------------------------------- #

add_subdirectory(../external/raylib ${CMAKE_CURRENT_BINARY_DIR}/raylib)
#add_subdirectory(../external/raygui/projects/CMake ${CMAKE_CURRENT_BINARY_DIR}/raygui)
target_link_libraries(${ENGINE_PROJECT_NAME} PUBLIC raylib)

# ------------------------------------------------------------------------------------- #

# Добавление подмодуля GLAD и его сборка
add_subdirectory(../external/glad ${CMAKE_CURRENT_BINARY_DIR}/glad)
# Линковка с библиотекой GLAD
target_link_libraries(${ENGINE_PROJECT_NAME} PUBLIC glad)

# ------------------------------------------------------------------------------------- #

set(IMGUI_INCLUDES
	../external/imgui/imgui.h
	
	../external/imgui/imconfig.h
	../external/imgui/imgui_internal.h
	
	../external/imgui/imstb_rectpack.h
	../external/imgui/imstb_textedit.h
	../external/imgui/imstb_truetype.h
	
	../external/imgui/backends/imgui_impl_opengl3.h
)

set(IMGUI_SOURCES

	../external/imgui/imgui.cpp
	
	../external/imgui/backends/imgui_impl_opengl3.cpp
	
	../external/imgui/imgui_draw.cpp
	../external/imgui/imgui_widgets.cpp
	../external/imgui/imgui_tables.cpp
	
	../external/imgui/imgui_demo.cpp
)

add_library(ImGui STATIC
	${IMGUI_INCLUDES}
	${IMGUI_SOURCES}
)

target_include_directories(ImGui PUBLIC ../external)
target_include_directories(ImGui PUBLIC ../external/imgui)
target_link_libraries(${ENGINE_PROJECT_NAME} PUBLIC ImGui)

# ------------------------------------------------------------------------------------- #

add_subdirectory(../external/imgui_raylib ${CMAKE_CURRENT_BINARY_DIR}/imgui_raylib)
target_link_libraries(${ENGINE_PROJECT_NAME} PUBLIC imgui_raylib)

# ------------------------------------------------------------------------------------- #

add_subdirectory(../external/tinyfiledialogs ${CMAKE_CURRENT_BINARY_DIR}/tinyfiledialogs)
target_link_libraries(${ENGINE_PROJECT_NAME} PUBLIC tinyfiledialogs)

# ------------------------------------------------------------------------------------- #