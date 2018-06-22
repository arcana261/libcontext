ACLOCAL_AMFLAGS = -I m4 --install
AM_CPPFLAGS = -I$(top_srcdir)/src
AM_CFLAGS = 
AM_LDFLAGS = 

EXTRA_DIST = \
	autogen.sh

# include glib as dependency
AM_CFLAGS += $(GLIB_CFLAGS)
AM_LDFLAGS += $(GLIB_LIBS)
