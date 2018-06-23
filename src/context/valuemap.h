#ifndef _CONTEXT_MAP_H__
#define _CONTEXT_MAP_H__

#include <glib.h>

typedef struct {
    GHashTable* table;
} ValueMap;

ValueMap*   valuemap_new();
void        valuemap_destroy(ValueMap* v);

gboolean    valuemap_contains(ValueMap* m, const gchar* key);
gboolean    valuemap_unset(ValueMap* m, const gchar* key);

void        valuemap_set_int(ValueMap* m, const gchar* key, gint value);
gint        valuemap_get_int(ValueMap* m, const gchar* key, GError **err);
gboolean    valuemap_is_int(ValueMap* m, const gchar* key);

#endif
