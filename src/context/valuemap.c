#include <glib-object.h>

#include "context/error.h"
#include "context/valuemap.h"

GValue* _valuemap_lookup_or_null(const ValueMap* v, const gchar* key);
GValue* _valuemap_lookup_or_fail(const ValueMap* v, const gchar* key,
                                 GError** err);
GValue* _valuemap_lookup_or_create(ValueMap* v, const gchar* key, GType g_type);
GValue* _valuemap_lookup_sametype(const ValueMap* v, const gchar* key,
                                  GType g_type, GError** err);

ValueMap* valuemap_new() {
  ValueMap* result;

  result = g_new(ValueMap, 1);
  result->table = g_hash_table_new(g_str_hash, g_str_equal);

  return result;
}

void valuemap_destroy(ValueMap* v) {
  GHashTableIter iter;
  gpointer key, value;

  g_hash_table_iter_init(&iter, v->table);
  while (g_hash_table_iter_next(&iter, &key, &value)) {
    g_hash_table_iter_remove(&iter);

    g_value_unset((GValue*)value);
    g_free(value);
    g_free(key);
  }

  g_hash_table_destroy(v->table);
  g_free(v);
}

gboolean valuemap_contains(const ValueMap* m, const gchar* key) {
  return _valuemap_lookup_or_null(m, key) != NULL;
}

gboolean valuemap_unset(ValueMap* m, const gchar* key) {
  gpointer value;
  gpointer orig_key;

  if (!g_hash_table_lookup_extended(m->table, key, &orig_key, &value)) {
    return FALSE;
  } else {
    g_hash_table_remove(m->table, key);

    g_value_unset((GValue*)value);
    g_free(value);
    g_free(orig_key);

    return TRUE;
  }
}

GType valuemap_get_type(const ValueMap* m, const gchar* key, GError** err) {
  GValue* value;

  g_return_val_if_fail(err == NULL || *err == NULL, 0);

  value = _valuemap_lookup_or_fail(m, key, err);
  if (err != NULL && *err != NULL) {
    return G_TYPE_INT;
  }

  return G_VALUE_TYPE(value);
}

void valuemap_set_boolean(ValueMap* m, const gchar* key, gboolean value) {
  GValue* g_value;

  g_value = _valuemap_lookup_or_create(m, key, G_TYPE_BOOLEAN);
  if (G_VALUE_TYPE(g_value) == G_TYPE_BOOLEAN) {
    g_value_set_boolean(g_value, value);
  } else {
    g_value_unset(g_value);
    g_value_init(g_value, G_TYPE_BOOLEAN);
    g_value_set_boolean(g_value, value);
  }
}

gboolean valuemap_get_boolean(const ValueMap* m, const gchar* key,
                              GError** err) {
  GValue* value;

  g_return_val_if_fail(err == NULL || *err == NULL, FALSE);

  value = _valuemap_lookup_sametype(m, key, G_TYPE_BOOLEAN, err);
  if (err != NULL && *err != NULL) {
    return FALSE;
  }

  return g_value_get_boolean(value);
}

void valuemap_set_int(ValueMap* m, const gchar* key, gint value) {
  GValue* g_value;

  g_value = _valuemap_lookup_or_create(m, key, G_TYPE_INT);
  if (G_VALUE_TYPE(g_value) == G_TYPE_INT) {
    g_value_set_int(g_value, value);
  } else {
    g_value_unset(g_value);
    g_value_init(g_value, G_TYPE_INT);
    g_value_set_int(g_value, value);
  }
}

gint valuemap_get_int(const ValueMap* m, const gchar* key, GError** err) {
  GValue* value;

  g_return_val_if_fail(err == NULL || *err == NULL, 0);

  value = _valuemap_lookup_sametype(m, key, G_TYPE_INT, err);
  if (err != NULL && *err != NULL) {
    return 0;
  }

  return g_value_get_int(value);
}

void valuemap_set_string(ValueMap* m, const gchar* key, const gchar* value) {
  GValue* g_value;

  g_value = _valuemap_lookup_or_create(m, key, G_TYPE_STRING);
  if (G_VALUE_TYPE(g_value) == G_TYPE_STRING) {
    g_value_set_string(g_value, value);
  } else {
    g_value_unset(g_value);
    g_value_init(g_value, G_TYPE_STRING);
    g_value_set_string(g_value, value);
  }
}

const gchar* valuemap_get_string(const ValueMap* m, const gchar* key,
                                 GError** err) {
  GValue* value;

  g_return_val_if_fail(err == NULL || *err == NULL, 0);

  value = _valuemap_lookup_sametype(m, key, G_TYPE_STRING, err);
  if (err != NULL && *err != NULL) {
    return NULL;
  }

  return g_value_get_string(value);
}

GValue* _valuemap_lookup_sametype(const ValueMap* v, const gchar* key,
                                  GType g_type, GError** err) {
  GValue* value;

  g_return_val_if_fail(err == NULL || *err == NULL, NULL);

  value = _valuemap_lookup_or_fail(v, key, err);
  if (err != NULL && *err != NULL) {
    return NULL;
  }

  if (G_VALUE_TYPE(value) != g_type) {
    g_set_error(err, CONTEXT_ERROR, CONTEXT_ERROR_INVALID_TYPE,
                "[%s:%d] for key '%s' requested type '%s' but has '%s'",
                __FILE__, __LINE__, key, g_type_name(g_type),
                g_type_name(G_VALUE_TYPE(value)));

    return NULL;
  }

  return value;
}

GValue* _valuemap_lookup_or_create(ValueMap* v, const gchar* key,
                                   GType g_type) {
  GValue* value;

  value = _valuemap_lookup_or_null(v, key);
  if (value == NULL) {
    value = g_new0(GValue, 1);
    g_value_init(value, g_type);
    g_hash_table_insert(v->table, g_strdup(key), value);
  }

  return value;
}

GValue* _valuemap_lookup_or_fail(const ValueMap* v, const gchar* key,
                                 GError** err) {
  GValue* value;

  g_return_val_if_fail(err == NULL || *err == NULL, NULL);

  value = _valuemap_lookup_or_null(v, key);
  if (value == NULL) {
    g_set_error(err, CONTEXT_ERROR, CONTEXT_ERROR_KEY_NOT_FOUND,
                "[%s:%d] key not found %s", __FILE__, __LINE__, key);

    return NULL;
  }

  return value;
}

GValue* _valuemap_lookup_or_null(const ValueMap* v, const gchar* key) {
  return (GValue*)g_hash_table_lookup(v->table, key);
}
