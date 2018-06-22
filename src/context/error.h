#ifndef _CONTEXT_ERROR_H__
#define _CONTEXT_ERROR_H__

#include <glib.h>

#define CONTEXT_ERROR                   g_quark_from_static_string("libcontext")
#define CONTEXT_ERROR_INVALID_TYPE      1

#endif
