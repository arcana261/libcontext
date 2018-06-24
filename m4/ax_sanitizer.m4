AC_DEFUN([AX_SANITIZER],
[
    AX_CHECK_COMPILE_FLAG([-fsanitize=leak], [SANITY_LEAK=true], [SANITY_LEAK=false])
    AX_CHECK_COMPILE_FLAG([-fsanitize=address], [SANITY_ADDRESS=true], [SANITY_LEAK=false])
    AX_CHECK_COMPILE_FLAG([-fsanitize=undefined], [SANITY_UNDEFINED=true], [SANITY_UNDEFINED=false])
    AX_CHECK_COMPILE_FLAG([-fsanitize=memory], [SANITY_MEMORY=true], [SANITY_MEMORY=false])
    AX_CHECK_COMPILE_FLAG([-fsanitize=thread], [
        AX_CHECK_LINK_FLAG(-pie, [SANITY_THREAD=true], [SANITY_THREAD=false])
    ], [SANITY_THREAD=false])

    # gcc: error: -fsanitize=thread linking must be done with -pie or -shared

    AM_CONDITIONAL([HAVE_LEAK_SANITIZER], [test x$SANITY_LEAK = xtrue])
    AM_CONDITIONAL([HAVE_ADDRESS_SANITIZER], [test x$SANITY_ADDRESS = xtrue])
    AM_CONDITIONAL([HAVE_UNDEFINED_SANITIZER], [test x$SANITY_UNDEFINED = xtrue])
    AM_CONDITIONAL([HAVE_THREAD_SANITIZER], [test x$SANITY_THREAD = xtrue])
    AM_CONDITIONAL([HAVE_MEMORY_SANITIZER], [test x$SANITY_MEMORY = xtrue])
])
