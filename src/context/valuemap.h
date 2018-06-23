#ifndef CONTEXT_VALUEMAP_H_
#define CONTEXT_VALUEMAP_H_

#include <glib.h>

typedef struct { GHashTable* table; } ValueMap;

ValueMap* valuemap_new();
void valuemap_destroy(ValueMap* v);

gboolean valuemap_contains(ValueMap* m, const gchar* key);
gboolean valuemap_unset(ValueMap* m, const gchar* key);

void valuemap_set_int(ValueMap* m, const gchar* key, gint value);
gint valuemap_get_int(ValueMap* m, const gchar* key, GError** err);
gboolean valuemap_is_int(ValueMap* m, const gchar* key);

void valuemap_set_string(ValueMap* m, const gchar* key, const gchar* value);
const gchar* valuemap_get_string(ValueMap* m, const gchar* key, GError** err);
gboolean valuemap_is_string(ValueMap* m, const gchar* key);

#endif  // CONTEXT_VALUEMAP_H_
