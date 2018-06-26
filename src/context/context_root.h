#ifndef CONTEXT_CONTEXT_ROOT_H__
#define CONTEXT_CONTEXT_ROOT_H__

#include <glib-object.h>

#define CONTEXT_TYPE_ROOT context_root_get_type()
#define CONTEXT_ROOT(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj), CONTEXT_TYPE_ROOT, ContextRoot))
#define CONTEXT_IS_ROOT(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj), CONTEXT_TYPE_ROOT))
#define CONTEXT_ROOT_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_CAST((klass), CONTEXT_TYPE_ROOT, ContextRootClass))
#define CONTEXT_IS_ROOT_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_TYPE((klass), CONTEXT_TYPE_ROOT))
#define CONTEXT_ROOT_GET_CLASS(obj) \
  (G_TYPE_INSTANCE_GET_CLASS((obj), CONTEXT_TYPE_ROOT, ContextRootClass))

typedef struct _ContextRoot ContextRoot;
typedef struct _ContextRootClass ContextRootClass;

struct _ContextRoot {
  GObject parent_instance;
};

struct _ContextRootClass {
  GObjectClass parent_class;
};

GType context_root_get_type(void);

#endif  // CONTEXT_CONTEXT_ROOT_H__
