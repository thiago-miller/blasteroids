#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([blasteroids], [0.0.1], [tmiller@mochsl.org.br])
AC_CONFIG_SRCDIR([src/main.c])
AC_CONFIG_AUX_DIR(config)
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIRS([m4])

LT_PREREQ([2.2])
LT_INIT([dlopen])

AM_INIT_AUTOMAKE

# Checks for programs.
AC_PROG_CC_C99
AC_PROG_INSTALL

# Checks for libraries.
AC_SEARCH_LIBS([sqrt], [m], ,
	[AC_MSG_ERROR([math (libm) not found!])])
PKG_CHECK_MODULES([ALLEGRO], [allegro-5 allegro_primitives-5 allegro_font-5 \
	allegro_image-5 allegro_audio-5 allegro_acodec-5], , [AC_MSG_ERROR([allegro-5.0 not found!])])

# Checks for header files.
AC_HEADER_STDC
AC_HEADER_ASSERT
AC_CHECK_HEADERS([allegro5/allegro5.h allegro5/allegro_primitives.h \
	allegro5/allegro_font.h allegro5/allegro_image.h allegro5/allegro_audio.h allegro5/allegro_acodec.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

# Define variable to handle assets/ dir
PACKAGE_DATA_SRCDIR="$srcdir/assets"
AC_SUBST(PACKAGE_DATA_SRCDIR)

AC_CONFIG_FILES([Makefile src/Makefile])
AC_OUTPUT
