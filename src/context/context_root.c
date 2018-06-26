#include <time.h>

#include "./error.h"
#include "context/context.h"
#include "context/context_root.h"
#include "context/valuemap.h"

static void context_root_context_interface_init(ContextInterface* iface);

typedef struct { ContextValueMap* values; } ContextRootPrivate;

G_DEFINE_TYPE_WITH_CODE(
    ContextRoot, context_root, G_TYPE_OBJECT,
    G_IMPLEMENT_INTERFACE(CONTEXT_TYPE, context_root_context_interface_init)
        G_ADD_PRIVATE(ContextRoot))

static void context_root_dispose(GObject* gobject) {
  ContextRootPrivate* priv =
      context_root_get_instance_private(CONTEXT_ROOT(gobject));

  g_clear_object(&priv->values);

  G_OBJECT_CLASS(context_root_parent_class)->dispose(gobject);
}

static void context_root_class_init(ContextRootClass* klass) {
  GObjectClass* gobject_class;

  gobject_class = G_OBJECT_CLASS(klass);

  gobject_class->dispose = context_root_dispose;
}

static void context_root_init(ContextRoot* self) {
  ContextRootPrivate* priv;
  priv = context_root_get_instance_private(self);

  priv->values = NULL;
}

static gboolean context_root_has_deadline(const Context* self) {
  g_return_val_if_fail(CONTEXT_IS_ROOT((Context*)self), FALSE);
  return FALSE;
}

static time_t context_root_get_deadline(const Context* self, GError** err) {
  g_return_val_if_fail(CONTEXT_IS_ROOT((Context*)self), 0);

  g_set_error(err, CONTEXT_ERROR, CONTEXT_ERROR_DEADLINE_NOT_SUPPORTED,
              "[%s:%d] root context does not support deadlines", __FILE__,
              __LINE__);

  return 0;
}

static GCond* context_root_get_done(const Context* self, GError** err) {
  g_return_val_if_fail(CONTEXT_IS_ROOT((Context*)self), NULL);

  g_set_error(err, CONTEXT_ERROR, CONTEXT_ERROR_NOT_CANCELABLE,
              "[%s:%d] root context is not cancelable", __FILE__, __LINE__);

  return NULL;
}

static void context_root_cancel(Context* self, GError** err) {
  g_return_if_fail(CONTEXT_IS_ROOT((Context*)self));

  g_set_error(err, CONTEXT_ERROR, CONTEXT_ERROR_NOT_CANCELABLE,
              "[%s:%d] root context is not cancelable", __FILE__, __LINE__);
}

static GError* context_root_get_error(const Context* self) {
  g_return_val_if_fail(CONTEXT_IS_ROOT((Context*)self), NULL);

  return NULL;
}

const ContextValueMap* context_root_get_valuemap(const Context* self) {
  ContextRootPrivate* priv;

  g_return_val_if_fail(CONTEXT_IS_ROOT((Context*)self), NULL);

  priv = context_root_get_instance_private(CONTEXT_ROOT((Context*)self));

  if (priv->values == NULL) {
    priv->values = g_object_new(CONTEXT_TYPE_VALUEMAP, NULL);
  }

  return priv->values;
}

static void context_root_context_interface_init(ContextInterface* iface) {
  iface->has_deadline = context_root_has_deadline;
  iface->get_deadline = context_root_get_deadline;
  iface->get_done = context_root_get_done;
  iface->cancel = context_root_cancel;
  iface->get_error = context_root_get_error;
  iface->get_valuemap = context_root_get_valuemap;
}
