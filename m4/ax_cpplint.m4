AC_DEFUN([AX_CPPLINT],
[
    AC_PATH_PROG([CPPLINT],[cpplint])
    AC_PATH_PROG([XARGS],[xargs])
    AC_PATH_PROG([TOOL_FIND],[find])
    AC_SUBST([CPPLINT])
    AC_SUBST([XARGS])
    AC_SUBST([TOOL_FIND])
    AM_CONDITIONAL([HAVE_CPPLINT], [test x$CPPLINT != x -a x$XARGS != x -a x$TOOL_FIND != x])
])
