#ifndef CONTEXT_VALUEMAP_H_
#define CONTEXT_VALUEMAP_H_

#include <glib.h>

typedef struct { GHashTable* table; } ValueMap;

ValueMap* valuemap_new();
void valuemap_destroy(ValueMap* v);

gboolean valuemap_contains(ValueMap* m, const gchar* key);
gboolean valuemap_unset(ValueMap* m, const gchar* key);
GType valuemap_get_type(ValueMap* m, const gchar* key, GError** err);

void valuemap_set_int(ValueMap* m, const gchar* key, gint value);
gint valuemap_get_int(ValueMap* m, const gchar* key, GError** err);

void valuemap_set_string(ValueMap* m, const gchar* key, const gchar* value);
const gchar* valuemap_get_string(ValueMap* m, const gchar* key, GError** err);

void valuemap_set_boolean(ValueMap* m, const gchar* key, gboolean value);
gboolean valuemap_get_boolean(ValueMap* m, const gchar* key, GError** err);

#endif  // CONTEXT_VALUEMAP_H_
