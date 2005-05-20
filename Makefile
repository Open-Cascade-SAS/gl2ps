RELEASE = 1.2.5
DATE = `date "+%Y%m%d"`

clean:
	rm -f *.tex *.ps *.eps *.eps.gz *.pdf *.o gl2psTest a.out *~
	cd doc && ${MAKE} clean

purge:
	rm -f `find . -name "*~" -o -name "*~~" -o -name "\#*"\
               -o -name ".\#*" -o -name "gmon.out"`

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
           -Wsign-compare -Wpointer-arith -Wundef -ansi -pedantic\
           -c gl2ps.c
	g++ -O3 -Wall -ansi -pedantic -c gl2ps.c

distrib:
	rm -rf gl2ps-${RELEASE}/ gl2ps-${RELEASE}.tgz
	mkdir gl2ps-${RELEASE}
	cd doc && ${MAKE}
	cp TODO COPYING.GL2PS COPYING.LGPL gl2ps.c gl2ps.h gl2psTest.c\
           doc/gl2ps.pdf gl2ps-${RELEASE}
	tar zcvf gl2ps-${RELEASE}.tgz gl2ps-${RELEASE}
	@echo "********************************************************************"
	@echo "Did you remember to untabify both gl2ps.c and gl2ps.h?"
	@echo "********************************************************************"

distrib-nightly:
	rm -rf gl2ps-nightly*
	mkdir gl2ps-${DATE}
	cd doc && ${MAKE} gl2ps.pdf
	cp TODO COPYING.GL2PS COPYING.LGPL gl2ps.c gl2ps.h gl2psTest.c\
           doc/gl2ps.pdf gl2ps-${DATE}
	tar zcvf gl2ps-nightly.tgz gl2ps-${DATE}
	rm -rf gl2ps-${DATE}
