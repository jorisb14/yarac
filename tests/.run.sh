
#!/bin/sh

# Going to the tests directory
cd ./../tests

if [ ! -d ./bin ]; then
	mkdir -p ./bin
fi

# Cleanup
[ -e ./bin/unit_tester.out ] && rm -- ./bin/unit_tester.out

# Compiling unit_tester
gcc \
	-std=gnu11 \
	-Wall \
	-Wextra \
	-Wpedantic \
	-Werror \
	-Wshadow \
	-O3 \
	-DYARAC_RELEASE=1 \
	-DUT_TESTS_CAP=1024 \
	-DUT_SUPRESS_LOGS=1 \
	-I./../include \
	-I./include \
	-o ./bin/unit_tester.out \
	./source/main.c \
	./source/unit_tester.c \
	./../source/logger.c \
	./../source/cli.c \
	./../source/rtm.c \
	./../source/containers.c \
	./../source/types.c \
	./../source/lexer.c \
	./../source/parser.c \
	./../source/linker.c

# Run the tester
./bin/unit_tester.out
