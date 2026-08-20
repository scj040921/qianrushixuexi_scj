#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.71])
AC_INIT([life], [1.0.0], [2465618779@qq.com])
AC_CONFIG_SRCDIR([include/head.h])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.
# FIXME: Replace 'main' with a function in '-llife':
AC_CHECK_LIB([life], [haircut])
AC_CHECK_LIB([life], [havemeal])

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AM_INIT_AUTOMAKE([-Wall -Werror])
AM_PROG_AR
AC_PROG_RANLIB

AC_CONFIG_FILES([Makefile
                 lib/Makefile
                 src/Makefile])
AC_OUTPUT