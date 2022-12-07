
# Init autoconf
AC_INIT([gnucabs], [0.1], [http://localhost/index.html], [gnucabs], [http://localhost/index.html])

# Minimum accepted autoconf version
AC_PREREQ([2.71])

# Source directory (with sanity check file)
AC_CONFIG_SRCDIR([./source/main.c])

# Tests directory (with sanity check file)
AC_CONFIG_TESTDIR([./tests/test.c])

# Condifguration header for the project
AC_CONFIG_HEADERS([./include/config.h])

# Auxiliary files directory
AC_CONFIG_AUX_DIR([./aux])

# Initializing automake tool
AM_INIT_AUTOMAKE([1.9 -Wall -Werror foreign subdir-objects])

# Setup output targets
AC_CONFIG_FILES([Makefile tests/Makefile])

# Find C compiler
AC_PROG_CC

# Set language to C
AC_LANG(C)

# Checks for header files.
AC_CHECK_HEADERS([
	assert.h
	stdlib.h
	stddef.h
	stdarg.h
	stdint.h
	string.h
	limits.h
	float.h
	stdio.h
	ctype.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_INLINE

# Checks for library functions.
AC_CHECK_FUNCS([
	malloc
	realloc
	free
	fprintf
	printf
	vfprintf
	sscanf
	memcpy
	memcmp
	strncmp
	strlen
	isdigit
	fopen
	fclose
	fgetc
	fgets
	fseek])

# Generate output
AC_OUTPUT

# Printing options
echo ""

echo "Configuration Parameters:"
echo "target............... ${with_target}"
echo "AR_FLAGS............. ${AR_FLAGS}"
echo "CC................... ${CC}"
echo "CFLAGS............... ${CFLAGS}"
echo "HOST................. ${HOST}"
echo "HOSTNAME............. ${HOSTNAME}"
echo "LDFLAGS.............. ${LDFLAGS}"
echo "host................. ${host}"
echo "install prefix ...... ${prefix}"
