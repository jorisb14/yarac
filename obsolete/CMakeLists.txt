
cmake_minimum_required(VERSION 3.3)
project("yarac" LANGUAGES C)

if(CMAKE_C_COMPILER_ID MATCHES "GNU")
	set(PEDANTIC_COMPILE_FLAGS -pedantic-errors -Wall -Wextra -pedantic
		-Wold-style-cast -Wundef
		-Wredundant-decls -Wwrite-strings -Wpointer-arith
		-Wcast-qual -Wformat=2 -Wmissing-include-dirs
		-Wcast-align
		-Wctor-dtor-privacy -Wdisabled-optimization
		-Winvalid-pch -Woverloaded-virtual
		-Wconversion -Wundef
		-Wno-ctor-dtor-privacy -Wno-format-nonliteral)

	if(NOT CMAKE_C_COMPILER_VERSION VERSION_LESS 4.6)
		set(PEDANTIC_COMPILE_FLAGS ${PEDANTIC_COMPILE_FLAGS}
			-Wno-dangling-else -Wno-unused-local-typedefs)
	endif()

	if(NOT CMAKE_C_COMPILER_VERSION VERSION_LESS 5.0)
		set(PEDANTIC_COMPILE_FLAGS ${PEDANTIC_COMPILE_FLAGS} -Wdouble-promotion
			-Wtrampolines -Wzero-as-null-pointer-constant -Wuseless-cast
			-Wvector-operation-performance -Wsized-deallocation -Wshadow)
	endif()

	if(NOT CMAKE_C_COMPILER_VERSION VERSION_LESS 6.0)
		set(PEDANTIC_COMPILE_FLAGS ${PEDANTIC_COMPILE_FLAGS} -Wshift-overflow=2
			-Wnull-dereference -Wduplicated-cond)
	endif()
	
	set(WERROR_FLAG -Werror)
	set(CFLAGS "${CFLAGS} -std=gnu11")
endif()

set(YARAC_BIN_DIRECTORY     "${CMAKE_CURRENT_SOURCE_DIR}/build")
set(YARAC_INCLUDE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(YARAC_SOURCE_DIRECTORY  "${CMAKE_CURRENT_SOURCE_DIR}/source")

file(GLOB YARAC_HEADER_FILES
	"${YARAC_INCLUDE_DIRECTORY}/location.h"
	"${YARAC_INCLUDE_DIRECTORY}/logger.h"
	"${YARAC_INCLUDE_DIRECTORY}/rtm.h"
	"${YARAC_INCLUDE_DIRECTORY}/containers.h"
	"${YARAC_INCLUDE_DIRECTORY}/types.h"
	"${YARAC_INCLUDE_DIRECTORY}/cli.h"
	"${YARAC_INCLUDE_DIRECTORY}/lexer.h"
	"${YARAC_INCLUDE_DIRECTORY}/parser.h"
	"${YARAC_INCLUDE_DIRECTORY}/linker.h"
	"${YARAC_INCLUDE_DIRECTORY}/debug/utils.h"
)

set(YARAC_PUBLIC_HEADER_FILES
	"${YARAC_INCLUDE_DIRECTORY}/location.h"
	"${YARAC_INCLUDE_DIRECTORY}/logger.h"
	"${YARAC_INCLUDE_DIRECTORY}/rtm.h"
	"${YARAC_INCLUDE_DIRECTORY}/containers.h"
	"${YARAC_INCLUDE_DIRECTORY}/types.h"
	"${YARAC_INCLUDE_DIRECTORY}/cli.h"
	"${YARAC_INCLUDE_DIRECTORY}/lexer.h"
	"${YARAC_INCLUDE_DIRECTORY}/parser.h"
	"${YARAC_INCLUDE_DIRECTORY}/linker.h"
	"${YARAC_INCLUDE_DIRECTORY}/debug/utils.h"
)

file(GLOB YARAC_SOURCE_FILES
	"${YARAC_SOURCE_DIRECTORY}/logger.c"
	"${YARAC_SOURCE_DIRECTORY}/rtm.c"
	"${YARAC_SOURCE_DIRECTORY}/containers.c"
	"${YARAC_SOURCE_DIRECTORY}/types.c"
	"${YARAC_SOURCE_DIRECTORY}/cli.c"
	"${YARAC_SOURCE_DIRECTORY}/lexer.c"
	"${YARAC_SOURCE_DIRECTORY}/parser.c"
	"${YARAC_SOURCE_DIRECTORY}/linker.c"
	"${YARAC_SOURCE_DIRECTORY}/main.c"
)

string(TOUPPER "${CMAKE_BUILD_TYPE}" BUILD_VARIANT)
set(YARAC_BUILD_VARIANT "YARAC_${BUILD_VARIANT}")
message(${YARAC_BUILD_VARIANT})

add_executable(${PROJECT_NAME} ${YARAC_SOURCE_FILES})

target_compile_definitions(${PROJECT_NAME}
	PUBLIC
		"${YARAC_BUILD_VARIANT}=1"
)

target_include_directories(${PROJECT_NAME}
	PUBLIC
		$<INSTALL_INTERFACE:include>
		$<BUILD_INTERFACE:${YARAC_INCLUDE_DIRECTORY}>
)

set_target_properties(${PROJECT_NAME} PROPERTIES
	PUBLIC_HEADER
		"${YARAC_PUBLIC_HEADER_FILES}"
)
