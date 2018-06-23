AC_DEFUN([AX_CPPLINT],
[
    AC_PATH_PROG([CPPLINT],[cpplint])
    AC_PATH_PROG([XARGS],[xargs])
    AC_SUBST([CPPLINT])
    AC_SUBST([XARGS])
    AM_CONDITIONAL([HAVE_CPPLINT], [test x$CPPLINT != x -a x$XARGS != x])
])
