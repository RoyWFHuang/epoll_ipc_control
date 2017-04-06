#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT(epollings, 0.1, aa@bb.cc)
AM_INIT_AUTOMAKE 
AC_CONFIG_SRCDIR([inc/epolling.h])
#AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC

# Checks for libraries.
AC_PROG_RANLIB

# Checks for header files.
AC_CHECK_HEADERS([fcntl.h stddef.h stdint.h string.h sys/socket.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T

# Checks for library functions.
AC_CHECK_FUNCS([memset socket])

AC_CONFIG_FILES([Makefile
                 src/Makefile])
AC_OUTPUT
