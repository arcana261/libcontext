#include <glib-object.h>

#include "valuemap.h"
#include "error.h"

GValue* _valuemap_lookup(ValueMap* v, const gchar* key);
GValue* _valuemap_lookup_or_create(ValueMap* v, const gchar* key, GType t, GError **err);

ValueMap* valuemap_new() {
    ValueMap* result;
    
    result = g_new(ValueMap, 1);
    result->table = g_hash_table_new(g_str_hash, g_str_equal);

    return result;
}

void valuemap_destroy(ValueMap* v) {

}

GValue* _valuemap_lookup(ValueMap* v, const gchar* key) {
    return (GValue*) g_hash_table_lookup(v->table, key);
}

GValue* _valuemap_lookup_or_create(ValueMap* v, const gchar* key, GType t, GError **err) {
    GValue* value;

    g_return_val_if_fail(err == NULL || *err == NULL, NULL);

    value = _valuemap_lookup(v, key);
    if (value == NULL) {
        g_value_init(value, t);
        g_hash_table_insert(v->table, g_strdup(key), value);
    } else {
        if (!g_value_type_transformable(G_VALUE_TYPE(value), t)) {
            g_set_error(err,
                CONTEXT_ERROR,
                CONTEXT_ERROR_INVALID_TYPE,
                "[%s:%d] can not convert value from type %s to %s",
                __FILE__,
                __LINE__,
                g_type_name(G_VALUE_TYPE(value)),
                g_type_name(t));

            return NULL;
        }
    }

    return value;
}
