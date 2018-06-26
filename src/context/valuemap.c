#include "context/valuemap.h"
#include "context/error.h"

typedef struct { GHashTable* table; } ContextValueMapPrivate;

G_DEFINE_TYPE_WITH_CODE(ContextValueMap, context_valuemap, G_TYPE_OBJECT,
                        G_ADD_PRIVATE(ContextValueMap))

static void context_valuemap_init(ContextValueMap* v) {
  ContextValueMapPrivate* priv;

  priv = context_valuemap_get_instance_private(v);
  priv->table = g_hash_table_new(g_str_hash, g_str_equal);
}

static void context_valuemap_finalize(GObject* v) {
  ContextValueMapPrivate* priv;
  GHashTableIter iter;
  gpointer key, value;

  priv = context_valuemap_get_instance_private(CONTEXT_VALUEMAP(v));

  g_hash_table_iter_init(&iter, priv->table);
  while (g_hash_table_iter_next(&iter, &key, &value)) {
    g_hash_table_iter_remove(&iter);

    g_value_unset((GValue*)value);
    g_free(value);
    g_free(key);
  }

  g_hash_table_destroy(priv->table);

  G_OBJECT_CLASS(context_valuemap_parent_class)->finalize(v);
}

static void context_valuemap_class_init(ContextValueMapClass* klass) {
  GObjectClass* gobject_class;

  gobject_class = G_OBJECT_CLASS(klass);

  gobject_class->finalize = context_valuemap_finalize;
}

GValue* _valuemap_lookup_or_null(const ContextValueMap* v, const gchar* key);
GValue* _valuemap_lookup_or_fail(const ContextValueMap* v, const gchar* key,
                                 GError** err);
GValue* _valuemap_lookup_or_create(ContextValueMap* v, const gchar* key,
                                   GType g_type);
GValue* _valuemap_lookup_sametype(const ContextValueMap* v, const gchar* key,
                                  GType g_type, GError** err);

gboolean context_valuemap_contains(const ContextValueMap* m, const gchar* key) {
  return _valuemap_lookup_or_null(m, key) != NULL;
}

gboolean context_valuemap_unset(ContextValueMap* m, const gchar* key) {
  gpointer value;
  gpointer orig_key;
  ContextValueMapPrivate* priv;

  priv = context_valuemap_get_instance_private(m);

  if (!g_hash_table_lookup_extended(priv->table, key, &orig_key, &value)) {
    return FALSE;
  } else {
    g_hash_table_remove(priv->table, key);

    g_value_unset((GValue*)value);
    g_free(value);
    g_free(orig_key);

    return TRUE;
  }
}

GType context_valuemap_get_item_type(const ContextValueMap* m, const gchar* key,
                                     GError** err) {
  GValue* value;

  g_return_val_if_fail(err == NULL || *err == NULL, 0);

  value = _valuemap_lookup_or_fail(m, key, err);
  if (err != NULL && *err != NULL) {
    return G_TYPE_INT;
  }

  return G_VALUE_TYPE(value);
}

void context_valuemap_set_boolean(ContextValueMap* m, const gchar* key,
                                  gboolean value) {
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

gboolean context_valuemap_get_boolean(const ContextValueMap* m,
                                      const gchar* key, GError** err) {
  GValue* value;

  g_return_val_if_fail(err == NULL || *err == NULL, FALSE);

  value = _valuemap_lookup_sametype(m, key, G_TYPE_BOOLEAN, err);
  if (err != NULL && *err != NULL) {
    return FALSE;
  }

  return g_value_get_boolean(value);
}

void context_valuemap_set_int(ContextValueMap* m, const gchar* key,
                              gint value) {
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

gint context_valuemap_get_int(const ContextValueMap* m, const gchar* key,
                              GError** err) {
  GValue* value;

  g_return_val_if_fail(err == NULL || *err == NULL, 0);

  value = _valuemap_lookup_sametype(m, key, G_TYPE_INT, err);
  if (err != NULL && *err != NULL) {
    return 0;
  }

  return g_value_get_int(value);
}

void context_valuemap_set_string(ContextValueMap* m, const gchar* key,
                                 const gchar* value) {
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

const gchar* context_valuemap_get_string(const ContextValueMap* m,
                                         const gchar* key, GError** err) {
  GValue* value;

  g_return_val_if_fail(err == NULL || *err == NULL, 0);

  value = _valuemap_lookup_sametype(m, key, G_TYPE_STRING, err);
  if (err != NULL && *err != NULL) {
    return NULL;
  }

  return g_value_get_string(value);
}

GValue* _valuemap_lookup_sametype(const ContextValueMap* v, const gchar* key,
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

GValue* _valuemap_lookup_or_create(ContextValueMap* v, const gchar* key,
                                   GType g_type) {
  GValue* value;
  ContextValueMapPrivate* priv;

  value = _valuemap_lookup_or_null(v, key);
  if (value == NULL) {
    priv = context_valuemap_get_instance_private(v);
    value = g_new0(GValue, 1);
    g_value_init(value, g_type);
    g_hash_table_insert(priv->table, g_strdup(key), value);
  }

  return value;
}

GValue* _valuemap_lookup_or_fail(const ContextValueMap* v, const gchar* key,
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

GValue* _valuemap_lookup_or_null(const ContextValueMap* v, const gchar* key) {
  ContextValueMapPrivate* priv;

  priv = context_valuemap_get_instance_private((ContextValueMap*)v);

  return (GValue*)g_hash_table_lookup(priv->table, key);
}
