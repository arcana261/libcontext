ACLOCAL_AMFLAGS = -I m4 --install
AM_CPPFLAGS = -I$(top_srcdir)/src
AM_CFLAGS = 
AM_LDFLAGS = 

EXTRA_DIST = \
	autogen.sh

# include glib as dependency
AM_CFLAGS += $(GLIB_CFLAGS)
AM_LDFLAGS += $(GLIB_LIBS)

# include gobject as dependency
AM_CFLAGS += $(GOBJECT_CFLAGS)
AM_LDFLAGS += $(GOBJECT_LIBS)

# targets
lib_LTLIBRARIES = libcontext-1.la

# libcontext-1.la
libcontext_1_la_SOURCES = \
	src/context/valuemap.h \
	src/context/valuemap.c \
	src/context/error.h
libcontext_1_la_LDFLAGS = $(AM_LDFLAGS) -versioninfo $(LIBVERSION)

# installation header files
include_HEADERS = \
	src/context/valuemap.h \
	src/context/error.h

# tests
check_PROGRAMS = \
 test/context/valuemap_test 

# context/valuemap test
test_context_valuemap_test_SOURCES = test/context/valuemap_test.c
test_context_valuemap_test_LDADD = $(lib_LTLIBRARIES)

# makefile includes
include make/lint.am
include make/format.am
include make/check.am
include make/sanity.am
include make/coverage.am
