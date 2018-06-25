#include <glib-object.h>
#include <glib.h>

#include "context/error.h"
#include "context/valuemap.h"

#include "./config.h"

void test_new(void) {
  ValueMap* v;

  v = valuemap_new();
  g_assert_nonnull(v);

  valuemap_destroy(v);
}

void test_contains_existing(void) {
  ValueMap* v;
  gboolean result;

  v = valuemap_new();
  g_assert_nonnull(v);

  valuemap_set_int(v, "some-key", 12);
  result = valuemap_contains(v, "some-key");
  g_assert_true(result);

  valuemap_destroy(v);
}

void test_contains_nonexisting(void) {
  ValueMap* v;
  gboolean result;

  v = valuemap_new();
  g_assert_nonnull(v);

  result = valuemap_contains(v, "some-key");
  g_assert_false(result);

  valuemap_destroy(v);
}

void test_unset_existing(void) {
  ValueMap* v;
  gboolean result;

  v = valuemap_new();
  g_assert_nonnull(v);

  valuemap_set_int(v, "some-key", 12);
  result = valuemap_unset(v, "some-key");
  g_assert_true(result);
  result = valuemap_contains(v, "some-key");
  g_assert_false(result);

  valuemap_destroy(v);
}

void test_unset_nonexisting(void) {
  ValueMap* v;
  gboolean result;

  v = valuemap_new();
  g_assert_nonnull(v);

  result = valuemap_unset(v, "some-key");
  g_assert_false(result);

  valuemap_destroy(v);
}

void test_int(void) {
  ValueMap* v;
  gint result;
  GError* err = NULL;

  v = valuemap_new();
  g_assert_nonnull(v);

  valuemap_set_int(v, "some-key", 12);
  result = valuemap_get_int(v, "some-key", &err);
  g_assert_no_error(err);
  g_assert_cmpint(result, ==, 12);

  valuemap_destroy(v);
}

void test_int_override(void) {
  ValueMap* v;
  gint result;
  GError* err = NULL;

  v = valuemap_new();
  g_assert_nonnull(v);

  valuemap_set_string(v, "some-key", "some-value");
  valuemap_set_int(v, "some-key", 15);
  result = valuemap_get_int(v, "some-key", &err);
  g_assert_no_error(err);
  g_assert_cmpint(result, ==, 15);

  valuemap_destroy(v);
}

void test_key_ownership(void) {
  ValueMap* v;
  gchar* input;
  gboolean result;

  input = g_strdup("some-key");
  v = valuemap_new();
  g_assert_nonnull(v);
  valuemap_set_int(v, input, 12);
  *input = 'Q';
  result = valuemap_contains(v, input);
  g_assert_false(result);
  result = valuemap_contains(v, "some-key");
  g_assert_true(result);

  g_free(input);
  valuemap_destroy(v);
}

void test_string(void) {
  ValueMap* v;
  const gchar* result;
  GError* err = NULL;

  v = valuemap_new();
  g_assert_nonnull(v);

  valuemap_set_string(v, "some-key", "some-value");
  result = valuemap_get_string(v, "some-key", &err);
  g_assert_no_error(err);
  g_assert_cmpstr(result, ==, "some-value");

  valuemap_destroy(v);
}

void test_string_override(void) {
  ValueMap* v;
  const gchar* result;
  GError* err = NULL;

  v = valuemap_new();
  g_assert_nonnull(v);

  valuemap_set_int(v, "some-key", 15);
  valuemap_set_string(v, "some-key", "some-value");
  result = valuemap_get_string(v, "some-key", &err);
  g_assert_no_error(err);
  g_assert_cmpstr(result, ==, "some-value");

  valuemap_destroy(v);
}

void test_string_ownership(void) {
  ValueMap* v;
  const gchar* result;
  GError* err = NULL;
  gchar* input;

  input = g_strdup("some-value");
  v = valuemap_new();
  g_assert_nonnull(v);

  valuemap_set_string(v, "some-key", input);
  *input = 'Q';
  result = valuemap_get_string(v, "some-key", &err);
  g_assert_no_error(err);
  g_assert_cmpstr(result, ==, "some-value");

  g_free(input);
  valuemap_destroy(v);
}

void test_get_type_int(void) {
  ValueMap* v;
  GType value;
  GError* err = NULL;

  v = valuemap_new();
  g_assert_nonnull(v);

  valuemap_set_int(v, "some-key", 15);
  value = valuemap_get_type(v, "some-key", &err);
  g_assert_no_error(err);
  g_assert_true(value == G_TYPE_INT);

  valuemap_destroy(v);
}

void test_get_type_string(void) {
  ValueMap* v;
  GType value;
  GError* err = NULL;

  v = valuemap_new();
  g_assert_nonnull(v);

  valuemap_set_string(v, "some-key", "some-value");
  value = valuemap_get_type(v, "some-key", &err);
  g_assert_no_error(err);
  g_assert_true(value == G_TYPE_STRING);

  valuemap_destroy(v);
}

void test_get_type_should_return_error_nonexisting_key(void) {
  ValueMap* v;
  GError* err = NULL;

  v = valuemap_new();
  g_assert_nonnull(v);

  valuemap_get_type(v, "some-key", &err);
  g_assert_error(err, CONTEXT_ERROR, CONTEXT_ERROR_KEY_NOT_FOUND);

  valuemap_destroy(v);
}

void test_boolean(void) {
  ValueMap* v;
  GError *err = NULL;
  gboolean result;

  v = valuemap_new();
  g_assert_nonnull(v);

  valuemap_set_boolean(v, "some-key", TRUE);
  result = valuemap_get_boolean(v, "some-key", &err);
  g_assert_no_error(err);
  g_assert_cmpint(result, ==, TRUE);

  valuemap_destroy(v);
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
  g_test_add_func("/valuemap/string", test_string);
  g_test_add_func("/valuemap/string/override", test_string_override);
  g_test_add_func("/valuemap/string_ownership", test_string);
  g_test_add_func("/valuemap/boolean", test_boolean);

  g_test_add_func("/valuemap/get_type/int", test_get_type_int);
  g_test_add_func("/valuemap/get_type/string", test_get_type_string);
  g_test_add_func("/valuemap/get_type/should_return_error_nonexisting_key",
                  test_get_type_should_return_error_nonexisting_key);

  return g_test_run();
}
