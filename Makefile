RELEASE = 1.2.0

default:
	rm -rf gl2ps-${RELEASE}/ gl2ps-${RELEASE}.tar* gl2ps-${RELEASE}.zip*
	mkdir gl2ps-${RELEASE}
	cd doc && ${MAKE}
	cp TODO COPYING.GL2PS COPYING.LGPL gl2ps.c gl2ps.h gl2psTest.c gl2psTestSimple.c\
           doc/gl2ps.ps doc/gl2ps.pdf gl2ps-${RELEASE}
	chmod 644 gl2ps-${RELEASE}/*
	tar cvf gl2ps-${RELEASE}.tar gl2ps-${RELEASE}
	gzip gl2ps-${RELEASE}.tar
	cd gl2ps-${RELEASE} && zip -r gl2ps-${RELEASE}.zip *
	mv gl2ps-${RELEASE}/gl2ps-${RELEASE}.zip .

linux:
	gcc -Wall -g -O3 -I/usr/X11R6/include -o gl2psTest gl2psTest.c gl2ps.c\
            -lglut -lGLU -lGL -L/usr/X11R6/lib -lX11 -lXi -lXmu -lm

linuxz:
	gcc -DHAVE_ZLIB -Wall -g -O3 -I/usr/X11R6/include -o gl2psTest gl2psTest.c gl2ps.c\
            -lglut -lGLU -lGL -L/usr/X11R6/lib -lX11 -lXi -lXmu -lm -lz

mac:
	gcc -Wall -g -o gl2psTest gl2psTest.c gl2ps.c\
            -framework OpenGL -framework GLUT -framework Cocoa

macz:
	gcc -DHAVE_ZLIB -Wall -g -O2 -o gl2psTest gl2psTest.c gl2ps.c\
            -framework OpenGL -framework GLUT -framework Cocoa -lz

clean:
	rm -f *.tex *.ps *.eps *.pdf gl2psTest a.out *~
	cd doc && ${MAKE} clean
