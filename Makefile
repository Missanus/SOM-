CC = gcc
ECHO = echo
RM = rm -f
TAR = tar
MKDIR = mkdir
CHMOD = chmod
CP = rsync -R
# déclaration des options du compilateur
CFLAGS = -Wall -g
CPPFLAGS = -I.
LDFLAGS = -lm  
# définition des fichiers et dossiers
PROGNAME = S0M_NaSSiM
VERSION = 1.5
distdir = $(PROGNAME)-$(VERSION)
HEADERS =  file.h 
SOURCES =  main.c  essaye.c  
OBJ = $(SOURCES:.c=.o)
DOXYFILE = documentation/Doxyfile
EXTRAFILES = COPYING $(wildcard shaders/*.?s images/*.png)
DISTFILES = $(SOURCES) Makefile $(HEADERS) $(DOXYFILE) $(EXTRAFILES)

all: $(PROGNAME)
$(PROGNAME): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $(PROGNAME)
%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@


clean:
	@$(RM) -r $(PROGNAME) $(OBJ) 
