RELEASE = 1.2.0
UNAME = `uname -s`

default:
	rm -rf gl2ps-${RELEASE}/ gl2ps-${RELEASE}.tar* gl2ps-${RELEASE}.zip*
	mkdir gl2ps-${RELEASE}
	cd doc && ${MAKE}
	cp TODO COPYING.GL2PS COPYING.LGPL gl2ps.c gl2ps.h gl2psTest.c\
           doc/gl2ps.ps doc/gl2ps.pdf gl2ps-${RELEASE}
	chmod 644 gl2ps-${RELEASE}/*
	tar cvf gl2ps-${RELEASE}.tar gl2ps-${RELEASE}
	gzip gl2ps-${RELEASE}.tar
	cd gl2ps-${RELEASE} && zip -r gl2ps-${RELEASE}.zip *
	mv gl2ps-${RELEASE}/gl2ps-${RELEASE}.zip .
	@echo "********************************************************************"
	@echo "Did you remember to untabify both gl2ps.c and gl2ps.h?"
	@echo "********************************************************************"

clean:
	rm -f *.tex *.ps *.eps *.eps.gz *.pdf *.o gl2psTest a.out *~
	cd doc && ${MAKE} clean

mac:
	gcc -Wall -g -o gl2psTest gl2psTest.c gl2ps.c\
            -framework OpenGL -framework GLUT -framework Cocoa

linux:
	gcc -Wall -g -O3 -I/usr/X11R6/include -o gl2psTest gl2psTest.c gl2ps.c\
            -lglut -lGLU -lGL -L/usr/X11R6/lib -lX11 -lXi -lXmu -lm

macz:
	gcc -DHAVE_ZLIB -Wall -g -O2 -o gl2psTest gl2psTest.c gl2ps.c\
            -framework OpenGL -framework GLUT -framework Cocoa -lz

linuxz:
	gcc -DHAVE_ZLIB -Wall -g -O3 -I/usr/X11R6/include -o gl2psTest gl2psTest.c gl2ps.c\
            -lglut -lGLU -lGL -L/usr/X11R6/lib -lX11 -lXi -lXmu -lm -lz


# -Wbad-function-cast
test:
	gcc -g -O3 -W -Wall\
           -Wredundant-decls -Wcast-align -Wmissing-prototypes\
           -Wsign-compare -Wpointer-arith -Wundef -pedantic\
           -c gl2ps.c
