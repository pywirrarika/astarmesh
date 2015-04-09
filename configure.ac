AC_INIT([amhello], [1.0], [bug-automake@gnu.org])

AC_PREREQ([2.62])
AM_INIT_AUTOMAKE([ -Wall -Werror foreign])


AC_PROG_CC

CFLAGS="$CFLAGS -ggdb -lm -pg "
AC_CONFIG_HEADERS([config.h])

AC_CONFIG_FILES([
    Makefile
    src/Makefile
])

AC_OUTPUT
