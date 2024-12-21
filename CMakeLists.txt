cmake_minimum_required(VERSION 3.27)
project(Fluid2_0)

set(CMAKE_CXX_STANDARD 20)

set(types "FLOAT,FIXED(32,5),DOUBLE, FIXED(32, 16)")

set(sizes "S(36,84)")

add_compile_definitions(
        TYPES="${types}"
        SIZES="${sizes}"
)
add_executable(generator generator.cpp)

add_custom_command(
        TARGET generator POST_BUILD  # Построить после того, как generator собран
        COMMAND ./generator         # Запускаем исп файл 1
        COMMENT "Running generator"
)

add_executable(Fluid2_0 main.cpp)

add_dependencies(Fluid2_0 generator)
