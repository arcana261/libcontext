#ifndef CONTEXT_CONTEXT_H_
#define CONTEXT_CONTEXT_H_

#include <glib-object.h>
#include <time.h>

#include "context/valuemap.h"

#define CONTEXT_TYPE context_get_type()
#define CONTEXT(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), CONTEXT_TYPE, Context))
#define IS_CONTEXT(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), CONTEXT_TYPE))
#define CONETXT_GET_INTERFACE(inst) (G_TYPE_CHECK_GET_INTERFACE ((inst), CONTEXT_TYPE, ContextInterface))

typedef struct _Context Context;
typedef struct _ContextInterface ContextInterface;

G_DECLARE_INTERFACE(Context, context, CONTEXT, CONTEXT, GObject)

struct _ContextInterface {
  GTypeInterface parent_iface;

  gboolean (*has_deadline)(const Context* self);
  time_t (*get_deadline)(const Context* self, GError** err);
  GCond* (*get_done)(const Context* self);
  void (*cancel)(Context* self, GError** err);
  GError* (*get_error)(const Context* self);
  const ValueMap* (*get_valuemap)(const Context* self);
};

GType context_get_type(void);

gboolean context_has_deadline(const Context* self);
time_t context_get_deadline(const Context* self, GError** err);
GCond* context_get_done(const Context* self);
void context_cancel(Context* self, GError** err);
GError* context_get_error(const Context* self);
const ValueMap* context_get_valuemap(const Context* self);

Context* context_background(void);
Context* context_todo(void);
Context* context_withcancel(const Context* parent);
Context* context_withdeadline(const Context* parent, time_t deadline);
Context* context_withtimeout(const Context* parent, time_t duration);
Context* context_withvaluemap(const Context* parent, const ValueMap* valuemap);

#endif  // CONTEXT_CONTEXT_H_
