AC_INIT([amhello], [1.0], [bug-automake@gnu.org])

AC_PREREQ([2.62])
AM_INIT_AUTOMAKE([ -Wall -Werror foreign])


AC_PROG_CC

# Check for OpenMP
AC_OPENMP 

# since some systems have broken OMP libraries
# we also check that the actual package will work
#ac_pkg_openmp=no
#if test -n "${OPENMP_CFLAGS}"; then
#    AC_MSG_CHECKING([whether OpenMP will work in a package])
#    AC_LANG_CONFTEST(
#    [AC_LANG_PROGRAM([[#include <omp.h>]], [[ return omp_get_num_threads (); ]])])
#    PKG_CFLAGS="${OPENMP_CFLAGS}" PKG_LIBS="${OPENMP_CFLAGS}" "$RBIN" CMD SHLIB conftest.c 1>&AS_MESSAGE_LOG_FD 2>&AS_MESSAGE_LOG_FD && "$RBIN" --vanilla -q -e "dyn.load(paste('conftest',.Platform\$dynlib.ext,sep=''))" 1>&AS_MESSAGE_LOG_FD 2>&AS_MESSAGE_LOG_FD && ac_pkg_openmp=yes
#    AC_MSG_RESULT([${ac_pkg_openmp}])
#fi

# if ${ac_pkg_openmp} = "yes" then we have OMP, otherwise it will be "no"
#if test "${ac_pkg_openmp}" = no; then
#    OPENMP_CFLAGS=''
#    AC_MSG_ERROR([OpenMP is required])
#    # you could put AC_MSG_ERROR here is OpenMP is required
#fi 

CFLAGS="$CFLAGS -ggdb -lm -pg "
AC_CONFIG_HEADERS([config.h])

AC_CONFIG_FILES([
    Makefile
    src/Makefile
])

AC_OUTPUT
