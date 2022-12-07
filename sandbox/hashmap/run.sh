
#!/bin/sh

# Cleanup
[ -e ./main.out ] && rm -- ./main.out

# Compiling unit_tester
gcc \
	-std=gnu11 \
	-Wall \
	-Wextra \
	-Wpedantic \
	-Werror \
	-Wshadow \
	-o ./main.out \
	./main.c

# Run the tester
./main.out
