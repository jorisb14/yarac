
# !/bin/sh

# Cleanup
[ -e ./configure 			] && rm -- ./configure
[ -e ./configure~ 			] && rm -- ./configure~
[ -e ./Makefile.in 			] && rm -- ./Makefile.in
[ -e ./aclocal.m4 			] && rm -- ./aclocal.m4
[ -e ./include/config.h.in 	] && rm -- ./include/config.h.in
[ -e ./tests/Makefile.in 	] && rm -- ./tests/Makefile.in

autoreconf --install
