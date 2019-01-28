bin_PROGRAMS = blasteroids
blasteroids_SOURCES = main.c

blasteroids_LDADD = ./libblasteroids.la $(ALLEGRO_LIBS)
noinst_LTLIBRARIES = libblasteroids.la

libblasteroids_la_SOURCES = \
		asteroid.c  \
		blast.c \
		spaceship.c \
		spaceship.h \
		blasteroids.c \
		blasteroids.h \
		error.c \
		error.h \
		input.c \
		input.h \
		movement.c \
		movement.h \
		listd.c \
		listd.h

libblasteroids_CPPFLAGS = $(ALLEGRO_CFLAGS)
libblasteroids_LDADD = $(ALLEGRO_LIBS)
