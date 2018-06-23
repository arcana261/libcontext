#include <glib.h>

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
  int result;
  GError* err = NULL;

  v = valuemap_new();
  g_assert_nonnull(v);

  valuemap_set_int(v, "some-key", 12);
  result = valuemap_get_int(v, "some-key", &err);
  g_assert_no_error(err);
  g_assert_cmpint(result, ==, 12);

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

int main(int argc, char* argv[]) {
  g_test_init(&argc, &argv, NULL);
  g_test_bug_base(PACKAGE_BUGREPORT);

  g_test_add_func("/valuemap/new", test_new);
  g_test_add_func("/valuemap/key_ownership", test_key_ownership);
  g_test_add_func("/valuemap/contains_existing", test_contains_existing);
  g_test_add_func("/valuemap/contains_nonexisting", test_contains_existing);
  g_test_add_func("/valuemap/set_nonexisting", test_contains_existing);
  g_test_add_func("/valuemap/unset_nonexisting", test_contains_existing);
  g_test_add_func("/valuemap/int", test_int);
  g_test_add_func("/valuemap/string", test_string);
  g_test_add_func("/valuemap/string_ownership", test_string);

  return g_test_run();
}
