#include "context/valuemap.h"

#include "config.h"

void test_new(void) {
    ValueMap* v;

    v = valuemap_new();
    g_assert_nonnull(v);

    valuemap_destroy(v);
}

int main(int argc, char* argv[]) {
	g_test_init(&argc, &argv, NULL);
	g_test_bug_base(PACKAGE_BUGREPORT);

	g_test_add_func("/valuemap/new", test_new);

    return g_test_run();
}
