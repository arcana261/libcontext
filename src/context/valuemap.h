#ifndef _CONTEXT_MAP_H__
#define _CONTEXT_MAP_H__

#include <glib.h>

typedef struct {
    GHashTable* table;
} ValueMap;

ValueMap*   valuemap_new();
void        valuemap_destroy(ValueMap* v);

void        valuemap_set_int(ValueMap* m, const gchar* key, gint value, GError **err);
gint        valuemap_get_int(ValueMap* m, const gchar* key, GError **err);

#endif
