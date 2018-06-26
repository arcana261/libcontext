#include "context/context_root.h"
#include "context/context.h"

static void context_root_context_interface_init(ContextInterface* iface);

G_DEFINE_TYPE_WITH_CODE(
    ContextRoot, context_root, G_TYPE_OBJECT,
    G_IMPLEMENT_INTERFACE(CONTEXT_TYPE, context_root_context_interface_init))

static void context_root_class_init(ContextRootClass* klass) {}

static void context_root_init(ContextRoot* self) {}

static gboolean context_root_context_has_deadline(const Context* self) {
  g_return_val_if_fail(CONTEXT_IS_ROOT((Context*)self), FALSE);

  return FALSE;
}

static void context_root_context_interface_init(ContextInterface* iface) {
  iface->has_deadline = context_root_context_has_deadline;
}
