# Установка минимальной версии CMake
cmake_minimum_required(VERSION 3.12)

# Определение названия проекта FarishEngineCore
set(ENGINE_PROJECT_NAME FarishEngineCore)

# Список публичных заголовочных файлов
set(ENGINE_PUBLIC_INCLUDES
	includes/FarishEngineCore/test.h
)

# Список приватных исходных файлов
set(ENGINE_PRIVATE_SOURCES	
	src/FarishEngineCore/test.cpp
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