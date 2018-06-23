AC_DEFUN([AX_CLANG_FORMAT],
[
    AC_PATH_PROG([CLANG_FORMAT],[clang-format])
    AC_PATH_PROG([XARGS],[xargs])
    AC_PATH_PROG([TOOL_FIND],[find])
    AC_SUBST([CLANG_FORMAT])
    AC_SUBST([XARGS])
    AC_SUBST([TOOL_FIND])
    AM_CONDITIONAL([HAVE_CLANG_FORMAT], [test x$CPPLINT != x -a x$XARGS != x -a x$TOOL_FIND != x])
])
