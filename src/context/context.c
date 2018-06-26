#include "context/context.h"
#include "context/context_root.h"

G_DEFINE_INTERFACE(Context, context, G_TYPE_OBJECT)

static void context_default_init(ContextInterface* iface) {}

gboolean context_has_deadline(const Context* self) {
  ContextInterface* iface;

  g_return_val_if_fail(CONTEXT_IS_CONTEXT((Context*)self), FALSE);

  iface = CONTEXT_CONTEXT_GET_IFACE((Context*)self);
  g_return_val_if_fail(iface->has_deadline != NULL, FALSE);

  return iface->has_deadline(self);
}

time_t context_get_deadline(const Context* self, GError** err) {
  ContextInterface* iface;

  g_return_val_if_fail(CONTEXT_IS_CONTEXT((Context*)self), 0);
  g_return_val_if_fail(err == NULL || *err == NULL, 0);

  iface = CONTEXT_CONTEXT_GET_IFACE((Context*)self);
  g_return_val_if_fail(iface->get_deadline != NULL, 0);

  return iface->get_deadline(self, err);
}

GCond* context_get_done(const Context* self) {
  ContextInterface* iface;

  g_return_val_if_fail(CONTEXT_IS_CONTEXT((Context*)self), NULL);

  iface = CONTEXT_CONTEXT_GET_IFACE((Context*)self);
  g_return_val_if_fail(iface->get_done != NULL, NULL);

  return iface->get_done(self);
}

void context_cancel(Context* self, GError** err) {
  ContextInterface* iface;

  g_return_if_fail(CONTEXT_IS_CONTEXT((Context*)self));
  g_return_if_fail(err == NULL || *err == NULL);

  iface = CONTEXT_CONTEXT_GET_IFACE((Context*)self);
  g_return_if_fail(iface->cancel != NULL);

  iface->cancel(self, err);
}

GError* context_get_error(const Context* self) {
  ContextInterface* iface;

  g_return_val_if_fail(CONTEXT_IS_CONTEXT((Context*)self), NULL);

  iface = CONTEXT_CONTEXT_GET_IFACE((Context*)self);
  g_return_val_if_fail(iface->get_error != NULL, NULL);

  return iface->get_error(self);
}

const ValueMap* context_get_valuemap(const Context* self) {
  ContextInterface* iface;

  g_return_val_if_fail(CONTEXT_IS_CONTEXT((Context*)self), NULL);

  iface = CONTEXT_CONTEXT_GET_IFACE((Context*)self);
  g_return_val_if_fail(iface->get_valuemap != NULL, NULL);

  return iface->get_valuemap(self);
}

Context* context_background(void) {
  return CONTEXT_CONTEXT(context_root_new());
}
