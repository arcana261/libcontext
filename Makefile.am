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
	src/context/map.h \
	src/context/map.c \
	src/context/error.h
libcontext_1_la_LDFLAGS = -versioninfo $(LIBVERSION)

# installation header files
include_HEADERS = \
	src/context/map.h \
	src/context/error.h

