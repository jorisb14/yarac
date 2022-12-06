
#!/bin/sh

cd ./../tests
tests_dir=./
yarac_include_dir=./../include
yarac_source_dir=./../source

if [ ! -d $tests_dir/bin ]; then
	mkdir -p $tests_dir/bin
fi

# Cleanup
[ -e $tests_dir/bin/unit_tester.out ] && rm -- $tests_dir/bin/unit_tester.out

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
	-I$yarac_include_dir \
	-I$tests_dir/include \
	-o $tests_dir/bin/unit_tester.out \
	$tests_dir/source/main.c \
	$tests_dir/source/unit_tester.c \
	$yarac_source_dir/logger.c \
	$yarac_source_dir/cli.c \
	$yarac_source_dir/rtm.c \
	$yarac_source_dir/containers.c \
	$yarac_source_dir/types.c \
	$yarac_source_dir/lexer.c \
	$yarac_source_dir/parser.c \
	$yarac_source_dir/linker.c

# Run the tester
$tests_dir/bin/unit_tester.out
