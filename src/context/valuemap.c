#include <glib-object.h>

#include "valuemap.h"
#include "error.h"

GValue* _valuemap_lookup_or_null(ValueMap* v, const gchar* key);
GValue* _valuemap_lookup_or_fail(ValueMap* v, const gchar* key, GError **err);
GValue* _valuemap_lookup_or_create(ValueMap* v, const gchar* key, GType g_type);
GValue* _valuemap_lookup_typed(ValueMap* v, const gchar* key, GType g_type, GError **err);

ValueMap* valuemap_new() {
    ValueMap* result;
    
    result = g_new(ValueMap, 1);
    result->table = g_hash_table_new(g_str_hash, g_str_equal);

    return result;
}

void valuemap_destroy(ValueMap* v) {

}

gboolean valuemap_contains(ValueMap* m, const gchar* key) {
    return _valuemap_lookup_or_null(m, key) != NULL;
}

gboolean valuemap_unset(ValueMap* m, const gchar* key) {
    gpointer value;
    gpointer orig_key;

    if (!g_hash_table_lookup_extended(m->table, key, &orig_key, &value)) {
        return FALSE;
    } else {
        g_hash_table_remove(m->table, key);

        g_value_unset((GValue*) value);
        g_free(value);
        g_free(orig_key);

        return TRUE;
    }
}

void valuemap_set_int(ValueMap* m, const gchar* key, gint value) {
    GValue *g_value;

    g_value = _valuemap_lookup_or_create(m, key, G_TYPE_INT);
    if (G_VALUE_TYPE(g_value) == G_TYPE_INT) {
        g_value_set_int(g_value, value);
    } else {
        g_value_unset(g_value);
        g_value_init(g_value, G_TYPE_INT);
        g_value_set_int(g_value, value);
    }
}

gint valuemap_get_int(ValueMap* m, const gchar* key, GError **err) {
    GValue *value;
    GValue new_value = G_VALUE_INIT;

    g_return_val_if_fail(err == NULL || *err == NULL, 0);

    value = _valuemap_lookup_typed(m, key, G_TYPE_INT, err);
    g_return_val_if_fail(err == NULL || *err == NULL, 0);
    g_assert_nonnull(value);

    if (G_VALUE_TYPE(value) == G_TYPE_INT) {
        return g_value_get_int(value);
    } else {
        g_value_init(&new_value, G_TYPE_INT);
        g_value_transform(value, &new_value);
        return g_value_get_int(&new_value);
    }
}

gboolean valuemap_is_int(ValueMap* m, const gchar* key) {
    GError *err;

    _valuemap_lookup_typed(m, key, G_TYPE_INT, &err);

    if (err != NULL) {
        g_error_free(err);
        return FALSE;
    }

    return TRUE;
}

GValue* _valuemap_lookup_typed(ValueMap* v, const gchar* key, GType g_type, GError **err) {
    GValue* value;

    g_return_val_if_fail(err == NULL || *err == NULL, NULL);

    value = _valuemap_lookup_or_fail(v, key, err);
    g_return_val_if_fail(err == NULL || *err == NULL, NULL);
    g_assert_nonnull(value);

    if (!g_value_type_transformable(G_VALUE_TYPE(value), g_type)) {
        g_set_error(err,
            CONTEXT_ERROR,
            CONTEXT_ERROR_INVALID_TYPE,
            "[%s:%d] can not convert value from type %s to %s",
            __FILE__,
            __LINE__,
            g_type_name(G_VALUE_TYPE(value)),
            g_type_name(g_type));

        return NULL;
    }

    return value;
}

GValue* _valuemap_lookup_or_create(ValueMap* v, const gchar* key, GType g_type) {
    GValue* value;

    value = _valuemap_lookup_or_null(v, key);
    if (value == NULL) {
        value = g_new0(GValue, 1);
        g_value_init(value, g_type);
        g_hash_table_insert(v->table, g_strdup(key), value);
    } 

    return value;
}

GValue* _valuemap_lookup_or_fail(ValueMap* v, const gchar* key, GError **err) {
    GValue *value;

    g_return_val_if_fail(err == NULL || *err == NULL, NULL);

    value = _valuemap_lookup_or_null(v, key);
    if (value == NULL) {
        g_set_error(err,
            CONTEXT_ERROR,
            CONTEXT_ERROR_KEY_NOT_FOUND,
            "[%s:%d] key not found %s",
            __FILE__,
            __LINE__,
            key);

        return NULL;
    }

    return value;
}

GValue* _valuemap_lookup_or_null(ValueMap* v, const gchar* key) {
    return (GValue*) g_hash_table_lookup(v->table, key);
}
