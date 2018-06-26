#ifndef CONTEXT_ERROR_H_
#define CONTEXT_ERROR_H_

#include <glib.h>

#define CONTEXT_ERROR g_quark_from_static_string("libcontext")
#define CONTEXT_ERROR_INVALID_TYPE 1
#define CONTEXT_ERROR_KEY_NOT_FOUND 2
#define CONTEXT_ERROR_DEADLINE_NOT_SUPPORTED 3
#define CONTEXT_ERROR_NOT_CANCELABLE 4

#endif  // CONTEXT_ERROR_H_
