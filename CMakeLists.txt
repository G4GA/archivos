cmake_minimum_required(VERSION 3.22)

project(tareas_noe LANGUAGES CXX)

add_compile_options(-Wall -pedantic)

set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS OFF)

function (target PROJECT_NAME)
    #Agrupa archivos en variables
    file (GLOB_RECURSE SRC CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/src/*.cpp")
    add_executable(${PROJECT_NAME} ${SRC})
    target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}/include")
    #Solo usa este si quieres que tus ejecutables se guearden en una carpeta diferente a la de 
    #set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../${PROJECT_NAME}")
endfunction()

target(simply_linked_lists)
target(tree_binary)
target(graph)