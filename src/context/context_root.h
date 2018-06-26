#ifndef CONTEXT_CONTEXT_ROOT_H__
#define CONTEXT_CONTEXT_ROOT_H__

#include <glib-object.h>

G_BEGIN_DECLS

#define CONTEXT_TYPE_ROOT context_root_get_type()
G_DECLARE_FINAL_TYPE(ContextRoot, context_root, CONTEXT, ROOT, GObject)

struct _ContextRootClass {
  GObjectClass parent_class;
};

ContextRoot* context_root_new(void);

G_END_DECLS

#endif  // CONTEXT_CONTEXT_ROOT_H__
