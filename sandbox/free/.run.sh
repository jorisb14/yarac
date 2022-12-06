
#!/bin/sh

rm -f ./main.out
gcc -std=gnu11 -DTEST_FLAG=2 -o ./main.out ./main.c
./main.out
