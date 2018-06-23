#ifndef CONTEXT_ERROR_H_
#define CONTEXT_ERROR_H_

#include <glib.h>

#define CONTEXT_ERROR g_quark_from_static_string("libcontext")
#define CONTEXT_ERROR_INVALID_TYPE 1
#define CONTEXT_ERROR_KEY_NOT_FOUND 1

#endif  // CONTEXT_ERROR_H_
