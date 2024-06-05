# Установка минимальной версии CMake
cmake_minimum_required(VERSION 3.12)

# Определение названия проекта
set(PROJECT_NAME FarishEngine)
project(${PROJECT_NAME})

# Добавления поддиректории для модуля FarishEngineCore (ядро движка)
add_subdirectory(FarishEngineCore)

# Добавления поддиректории для модуля FarishEngineEditor (запускаем файл приложения)
add_subdirectory(FarishEngineEditor)

# Установка FarishEngineEditor в качестве стартового проекта для Visual Studio
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT FarishEngineEditor)