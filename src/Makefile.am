bin_PROGRAMS = blasteroids
blasteroids_SOURCES = main.c

blasteroids_LDADD = ./libblasteroids.la $(ALLEGRO_LIBS)
noinst_LTLIBRARIES = libblasteroids.la

libblasteroids_la_SOURCES = \
		asteroid.c  \
		blast.c \
		spaceship.c \
		blasteroids.c

libblasteroids_CPPFLAGS = $(ALLEGRO_CFLAGS)
libblasteroids_LDADD = $(ALLEGRO_LIBS)
