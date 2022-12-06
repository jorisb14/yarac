
# The yarac target
bin_PROGRAMS = yarac

# Yarac sources
yarac_SOURCES =
yarac_SOURCES += \
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

# TODO: separate flags that should never be changed and user-defined ones!

# Yarac compiler flags
yarac_CFLAGS = \
	-std=gnu11 \
	-Wall \
	-Wextra \
	-Wpedantic \
	-Werror \
	-Wshadow \
	-O0 -g -DYARAC_DEBUG

# Yarac C/C++ preprocessor flags
yarac_CPPFLAGS = \
	-I$(top_srcdir)/include

# Yarac linker flags
yarac_LDFLAGS =
