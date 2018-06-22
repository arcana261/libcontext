AC_PREREQ([2.69])
AC_INIT([sample_app], [0.1.0], [https://github.com/arcana261/autotools/issues])

# check file exists
# AC_CONFIG_SRCDIR([src/hello.c])

AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])

AM_INIT_AUTOMAKE([1.14 -Wall -Werror foreign subdir-objects])

AM_PROG_AR
AC_PROG_CC
AC_LANG([C])

LT_INIT

AC_PROG_INSTALL

# check availability of cpplint
AX_CPPLINT

# check support for required compiler flags for sanity checkings
AX_SANITIZER

# Checks for existence of coverage tools and define variables for reporting coverage
AX_COVERAGE

# check availability of debian packaging tools
AX_DPKG

# resolve glib-2.0
PKG_CHECK_MODULES([GLIB], [glib-2.0 >= 2.40])

# outputs
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile])
#AC_CONFIG_FILES([whine.pc])

# generate all files
AC_OUTPUT

# show report
AC_MSG_RESULT([
Configure Information:
  C Compiler        : $CC
    DEFS            :   $DEFS
    CPPFLAGS        :   $CPPFLAGS
    CFLAGS          :   $CFLAGS

  C++ Compiler      : $CXX
    DEFS            :   $DEFS
    CPPFLAGS        :   $CPPFLAGS
    CXXFLAGS        :   $CXXFLAGS

  Linker            : $LD
    LDFLAGS         :   $LDFLAGS
    LIBS            :   $LIBS

glib:
	CFLAGS          : $GLIB_CFLAGS
	CPPFLAGS        : $GLIB_CPPFLAGS
	CXXFLAGS        : $GLIB_CXXFLAGS
	LIBS            : $GLIB_LIBS

Development:
	Linter                        : $CPPLINT
	Leak Sanitizer Checking       : $SANITY_LEAK
	Address Sanitizer Checking    : $SANITY_ADDRESS
	Undefined Sanitizer Checking  : $SANITY_UNDEFINED
	Thread Sanitizer Checking     : $SANITY_THREAD
	Memory Sanitizer Checking     : $SANITY_MEMORY

Coverage Reports      : $COVERAGE_SUPPORT
    gcov                : $GCOV
      COVERAGE_CFLAGS   : $COVERAGE_CFLAGS
      COVERAGE_CXXFLAGS : $COVERAGE_CXXFLAGS
      COVERAGE_OPTFLAGS : $COVERAGE_OPTFLAGS
      COVERAGE_LDFLAGS  : $COVERAGE_LDFLAGS
      COVERAGE_LIBS     : $COVERAGE_LIBS
    lcov                : $LCOV

Debian packaging:
  dpkg-deb              : $DPKG_DEB
])
