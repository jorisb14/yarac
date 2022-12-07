
cmake_minimum_required(VERSION 3.3)
project("map" LANGUAGES C)

file(GLOB MAP_SOURCE_FILES
	"./main.c"
)
add_executable(${PROJECT_NAME} ${MAP_SOURCE_FILES})
