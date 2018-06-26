#ifndef CONTEXT_VALUEMAP_H_
#define CONTEXT_VALUEMAP_H_

#include <glib-object.h>
#include <glib.h>

#define CONTEXT_TYPE_VALUEMAP context_valuemap_get_type()
#define CONTEXT_VALUEMAP(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj), CONTEXT_TYPE_VALUEMAP, ContextValueMap))
#define CONTEXT_IS_VALUEMAP(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj), CONTEXT_TYPE_VALUEMAP))
#define CONTEXT_VALUEMAP_CLASS(klass)                      \
  (G_TYPE_CHECK_CLASS_CAST((klass), CONTEXT_TYPE_VALUEMAP, \
                           ContextValueMapClass))
#define CONTEXT_IS_VALUEMAP_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_TYPE((klass), CONTEXT_TYPE_VALUEMAP))
#define CONTEXT_VALUEMAP_GET_CLASS(obj)                    \
  (G_TYPE_INSTANCE_GET_CLASS((obj), CONTEXT_TYPE_VALUEMAP, \
                             ContextValueMapClass))

typedef struct _ContextValueMap ContextValueMap;
typedef struct _ContextValueMapClass ContextValueMapClass;

struct _ContextValueMap {
  GObject parent_instance;
};

struct _ContextValueMapClass {
  GObjectClass parent_class;
};

GType context_valuemap_get_type(void);

gboolean context_valuemap_contains(const ContextValueMap* m, const gchar* key);
gboolean context_valuemap_unset(ContextValueMap* m, const gchar* key);
GType context_valuemap_get_item_type(const ContextValueMap* m, const gchar* key,
                                     GError** err);

void context_valuemap_set_int(ContextValueMap* m, const gchar* key, gint value);
gint context_valuemap_get_int(const ContextValueMap* m, const gchar* key,
                              GError** err);

void context_valuemap_set_string(ContextValueMap* m, const gchar* key,
                                 const gchar* value);
const gchar* context_valuemap_get_string(const ContextValueMap* m,
                                         const gchar* key, GError** err);

void context_valuemap_set_boolean(ContextValueMap* m, const gchar* key,
                                  gboolean value);
gboolean context_valuemap_get_boolean(const ContextValueMap* m,
                                      const gchar* key, GError** err);

#endif  // CONTEXT_VALUEMAP_H_
