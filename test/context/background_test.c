#include "context/context.h"

#include "./config.h"

void test_context_background_should_have_no_deadline(void) {
  Context* ctx;
  gboolean result;

  ctx = context_background();
  result = context_has_deadline(ctx);
  g_assert_false(result);

  g_clear_object(&ctx);
}

int main(int argc, char* argv[]) {
  g_test_init(&argc, &argv, NULL);
  g_test_bug_base(PACKAGE_BUGREPORT);

  g_test_add_func("/context/background/should_have_no_deadline",
                  test_context_background_should_have_no_deadline);

  return g_test_run();
}
