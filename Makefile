RELEASE = 0.8

default:
	rm -rf gl2ps-${RELEASE}/ gl2ps-${RELEASE}.tar* gl2ps-${RELEASE}.zip*
	mkdir gl2ps-${RELEASE}
	cd doc && ${MAKE}
	cp TODO COPYING.LIB gl2ps.c gl2ps.h gl2psTest.c doc/gl2ps.ps doc/gl2ps.pdf gl2ps-${RELEASE}/
	chmod 644 gl2ps-${RELEASE}/*
	tar cvf gl2ps-${RELEASE}.tar gl2ps-${RELEASE}
	gzip gl2ps-${RELEASE}.tar
	cd gl2ps-${RELEASE} && zip -r gl2ps-${RELEASE}.zip *
	mv gl2ps-${RELEASE}/gl2ps-${RELEASE}.zip .

test:
	gcc -Wall -g -O3 -I/usr/X11R6/include -o gl2psTest gl2psTest.c gl2ps.c\
            -lglut -lGLU -lGL -L/usr/X11R6/lib -lX11 -lm

clean:
	rm -f *.ps *.eps gl2psTest *~

