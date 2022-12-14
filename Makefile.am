
# The yarac target
bin_PROGRAMS = yarac

# Yarac sources
yarac_SOURCES = \
	$(top_srcdir)/include/debug/utils.h \
	$(top_srcdir)/include/cli.h \
	$(top_srcdir)/include/containers.h \
	$(top_srcdir)/include/lexer.h \
	$(top_srcdir)/include/linker.h \
	$(top_srcdir)/include/location.h \
	$(top_srcdir)/include/logger.h \
	$(top_srcdir)/include/parser.h \
	$(top_srcdir)/include/rtm.h \
	$(top_srcdir)/include/types.h \
	 \
	$(top_srcdir)/source/cli.c \
	$(top_srcdir)/source/containers.c \
	$(top_srcdir)/source/lexer.c \
	$(top_srcdir)/source/linker.c \
	$(top_srcdir)/source/logger.c \
	$(top_srcdir)/source/parser.c \
	$(top_srcdir)/source/rtm.c \
	$(top_srcdir)/source/types.c \
	$(top_srcdir)/source/main.c

# Yarac compiler flags
AM_CFLAGS = \
	-std=gnu11 \
	-Wall \
	-Wextra \
	-Wpedantic \
	-Werror \
	-Wshadow

# Yarac C/C++ preprocessor flags
yarac_CPPFLAGS = \
	-I$(top_srcdir)/include
	-I$(top_srcdir)/build/include

# Yarac linker flags
yarac_LDFLAGS =
