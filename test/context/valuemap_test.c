#include <glib-object.h>
#include <glib.h>

#include "context/error.h"
#include "context/valuemap.h"

#include "./config.h"

void test_new(void) {
  ContextValueMap* v;

  v = g_object_new(CONTEXT_TYPE_VALUEMAP, NULL);
  g_assert_nonnull(v);

  g_clear_object(&v);
}

void test_contains_existing(void) {
  ContextValueMap* v;
  gboolean result;

  v = g_object_new(CONTEXT_TYPE_VALUEMAP, NULL);
  g_assert_nonnull(v);

  context_valuemap_set_int(v, "some-key", 12);
  result = context_valuemap_contains(v, "some-key");
  g_assert_true(result);

  g_clear_object(&v);
}

void test_contains_nonexisting(void) {
  ContextValueMap* v;
  gboolean result;

  v = g_object_new(CONTEXT_TYPE_VALUEMAP, NULL);
  g_assert_nonnull(v);

  result = context_valuemap_contains(v, "some-key");
  g_assert_false(result);

  g_clear_object(&v);
}

void test_unset_existing(void) {
  ContextValueMap* v;
  gboolean result;

  v = g_object_new(CONTEXT_TYPE_VALUEMAP, NULL);
  g_assert_nonnull(v);

  context_valuemap_set_int(v, "some-key", 12);
  result = context_valuemap_unset(v, "some-key");
  g_assert_true(result);
  result = context_valuemap_contains(v, "some-key");
  g_assert_false(result);

  g_clear_object(&v);
}

void test_unset_nonexisting(void) {
  ContextValueMap* v;
  gboolean result;

  v = g_object_new(CONTEXT_TYPE_VALUEMAP, NULL);
  g_assert_nonnull(v);

  result = context_valuemap_unset(v, "some-key");
  g_assert_false(result);

  g_clear_object(&v);
}

void test_int(void) {
  ContextValueMap* v;
  gint result;
  GError* err = NULL;

  v = g_object_new(CONTEXT_TYPE_VALUEMAP, NULL);
  g_assert_nonnull(v);

  context_valuemap_set_int(v, "some-key", 12);
  result = context_valuemap_get_int(v, "some-key", &err);
  g_assert_no_error(err);
  g_assert_cmpint(result, ==, 12);

  g_clear_object(&v);
}

void test_int_override(void) {
  ContextValueMap* v;
  gint result;
  GError* err = NULL;

  v = g_object_new(CONTEXT_TYPE_VALUEMAP, NULL);
  g_assert_nonnull(v);

  context_valuemap_set_string(v, "some-key", "some-value");
  context_valuemap_set_int(v, "some-key", 15);
  result = context_valuemap_get_int(v, "some-key", &err);
  g_assert_no_error(err);
  g_assert_cmpint(result, ==, 15);

  g_clear_object(&v);
}

void test_key_ownership(void) {
  ContextValueMap* v;
  gchar* input;
  gboolean result;

  input = g_strdup("some-key");
  v = g_object_new(CONTEXT_TYPE_VALUEMAP, NULL);
  g_assert_nonnull(v);
  context_valuemap_set_int(v, input, 12);
  *input = 'Q';
  result = context_valuemap_contains(v, input);
  g_assert_false(result);
  result = context_valuemap_contains(v, "some-key");
  g_assert_true(result);

  g_free(input);
  g_clear_object(&v);
}

void test_string(void) {
  ContextValueMap* v;
  const gchar* result;
  GError* err = NULL;

  v = g_object_new(CONTEXT_TYPE_VALUEMAP, NULL);
  g_assert_nonnull(v);

  context_valuemap_set_string(v, "some-key", "some-value");
  result = context_valuemap_get_string(v, "some-key", &err);
  g_assert_no_error(err);
  g_assert_cmpstr(result, ==, "some-value");

  g_clear_object(&v);
}

void test_string_override(void) {
  ContextValueMap* v;
  const gchar* result;
  GError* err = NULL;

  v = g_object_new(CONTEXT_TYPE_VALUEMAP, NULL);
  g_assert_nonnull(v);

  context_valuemap_set_int(v, "some-key", 15);
  context_valuemap_set_string(v, "some-key", "some-value");
  result = context_valuemap_get_string(v, "some-key", &err);
  g_assert_no_error(err);
  g_assert_cmpstr(result, ==, "some-value");

  g_clear_object(&v);
}

void test_string_should_fail_for_nonexisting_key(void) {
  ContextValueMap* v;
  GError* err = NULL;

  v = g_object_new(CONTEXT_TYPE_VALUEMAP, NULL);
  g_assert_nonnull(v);

  context_valuemap_get_string(v, "some-key", &err);
  g_assert_error(err, CONTEXT_ERROR, CONTEXT_ERROR_KEY_NOT_FOUND);

  g_clear_object(&v);
}

void test_string_ownership(void) {
  ContextValueMap* v;
  const gchar* result;
  GError* err = NULL;
  gchar* input;

  input = g_strdup("some-value");
  v = g_object_new(CONTEXT_TYPE_VALUEMAP, NULL);
  g_assert_nonnull(v);

  context_valuemap_set_string(v, "some-key", input);
  *input = 'Q';
  result = context_valuemap_get_string(v, "some-key", &err);
  g_assert_no_error(err);
  g_assert_cmpstr(result, ==, "some-value");

  g_free(input);
  g_clear_object(&v);
}

void test_get_type_int(void) {
  ContextValueMap* v;
  GType value;
  GError* err = NULL;

  v = g_object_new(CONTEXT_TYPE_VALUEMAP, NULL);
  g_assert_nonnull(v);

  context_valuemap_set_int(v, "some-key", 15);
  value = context_valuemap_get_item_type(v, "some-key", &err);
  g_assert_no_error(err);
  g_assert_true(value == G_TYPE_INT);

  g_clear_object(&v);
}

void test_get_type_string(void) {
  ContextValueMap* v;
  GType value;
  GError* err = NULL;

  v = g_object_new(CONTEXT_TYPE_VALUEMAP, NULL);
  g_assert_nonnull(v);

  context_valuemap_set_string(v, "some-key", "some-value");
  value = context_valuemap_get_item_type(v, "some-key", &err);
  g_assert_no_error(err);
  g_assert_true(value == G_TYPE_STRING);

  g_clear_object(&v);
}

void test_get_type_should_return_error_nonexisting_key(void) {
  ContextValueMap* v;
  GError* err = NULL;

  v = g_object_new(CONTEXT_TYPE_VALUEMAP, NULL);
  g_assert_nonnull(v);

  context_valuemap_get_item_type(v, "some-key", &err);
  g_assert_error(err, CONTEXT_ERROR, CONTEXT_ERROR_KEY_NOT_FOUND);

  g_clear_object(&v);
}

void test_boolean(void) {
  ContextValueMap* v;
  GError* err = NULL;
  gboolean result;

  v = g_object_new(CONTEXT_TYPE_VALUEMAP, NULL);
  g_assert_nonnull(v);

  context_valuemap_set_boolean(v, "some-key", TRUE);
  result = context_valuemap_get_boolean(v, "some-key", &err);
  g_assert_no_error(err);
  g_assert_cmpint(result, ==, TRUE);

  g_clear_object(&v);
}

void test_set_boolean_override(void) {
  ContextValueMap* v;
  GError* err = NULL;
  gboolean result;

  v = g_object_new(CONTEXT_TYPE_VALUEMAP, NULL);
  g_assert_nonnull(v);

  context_valuemap_set_string(v, "some-key", "some-value");
  context_valuemap_set_boolean(v, "some-key", TRUE);
  result = context_valuemap_get_boolean(v, "some-key", &err);
  g_assert_no_error(err);
  g_assert_cmpint(result, ==, TRUE);

  g_clear_object(&v);
}

void test_set_boolean_should_fail_for_nonexisting_key(void) {
  ContextValueMap* v;
  GError* err = NULL;

  v = g_object_new(CONTEXT_TYPE_VALUEMAP, NULL);
  g_assert_nonnull(v);

  context_valuemap_get_boolean(v, "some-key", &err);
  g_assert_error(err, CONTEXT_ERROR, CONTEXT_ERROR_KEY_NOT_FOUND);

  g_clear_object(&v);
}

void test_get_int_should_fail_for_nonexisting_key(void) {
  ContextValueMap* v;
  GError* err = NULL;

  v = g_object_new(CONTEXT_TYPE_VALUEMAP, NULL);
  g_assert_nonnull(v);

  context_valuemap_get_int(v, "some-key", &err);
  g_assert_error(err, CONTEXT_ERROR, CONTEXT_ERROR_KEY_NOT_FOUND);

  g_clear_object(&v);
}

void test_get_int_should_fail_for_incompatible_type(void) {
  ContextValueMap* v;
  GError* err = NULL;

  v = g_object_new(CONTEXT_TYPE_VALUEMAP, NULL);
  g_assert_nonnull(v);

  context_valuemap_set_string(v, "some-key", "some-value");
  context_valuemap_get_int(v, "some-key", &err);
  g_assert_error(err, CONTEXT_ERROR, CONTEXT_ERROR_INVALID_TYPE);

  g_clear_object(&v);
}

int main(int argc, char* argv[]) {
  g_test_init(&argc, &argv, NULL);
  g_test_bug_base(PACKAGE_BUGREPORT);

  g_test_add_func("/valuemap/new", test_new);
  g_test_add_func("/valuemap/key_ownership", test_key_ownership);
  g_test_add_func("/valuemap/contains_existing", test_contains_existing);
  g_test_add_func("/valuemap/contains_nonexisting", test_contains_existing);
  g_test_add_func("/valuemap/set_nonexisting", test_unset_nonexisting);
  g_test_add_func("/valuemap/unset_nonexisting", test_unset_existing);
  g_test_add_func("/valuemap/int", test_int);
  g_test_add_func("/valuemap/int/override", test_int_override);
  g_test_add_func("/valuemap/int/should_return_error_for_nonexisting_key",
                  test_get_int_should_fail_for_nonexisting_key);
  g_test_add_func("/valuemap/int/should_fail_for_incompatible_type",
                  test_get_int_should_fail_for_incompatible_type);
  g_test_add_func("/valuemap/string", test_string);
  g_test_add_func("/valuemap/string/override", test_string_override);
  g_test_add_func("/valuemap/string_ownership", test_string);
  g_test_add_func("/valuemap/string/should_fail_for_nonexisting_key",
                  test_string_should_fail_for_nonexisting_key);
  g_test_add_func("/valuemap/boolean", test_boolean);
  g_test_add_func(
      "/valuemap/boolean/set_boolean_should_fail_for_nonexisting_key",
      test_set_boolean_should_fail_for_nonexisting_key);
  g_test_add_func("/valuemap/string/set_override", test_set_boolean_override);

  g_test_add_func("/valuemap/get_type/int", test_get_type_int);
  g_test_add_func("/valuemap/get_type/string", test_get_type_string);
  g_test_add_func("/valuemap/get_type/should_return_error_nonexisting_key",
                  test_get_type_should_return_error_nonexisting_key);

  return g_test_run();
}
