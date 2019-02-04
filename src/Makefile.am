bin_PROGRAMS = blasteroids
blasteroids_SOURCES = main.c

blasteroids_LDADD = ./libblasteroids.la $(ALLEGRO_LIBS)
noinst_LTLIBRARIES = libblasteroids.la

libblasteroids_la_SOURCES = \
		asteroid.c  \
		asteroid.h  \
		blast.c \
		blast.h \
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
		list.c \
		list.h \
		asteroid.c \
		asteroid.h \
		collision.c \
		collision.h \
		recycle.c \
		recycle.h \
		status.c \
		status.h \
		sound.c \
		sound.h \
		effect.c \
		effect.h

libblasteroids_CPPFLAGS = $(ALLEGRO_CFLAGS)
libblasteroids_LDADD = $(ALLEGRO_LIBS)
