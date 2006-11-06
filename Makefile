RELEASE = 1.3.2
DATE = `date "+%Y%m%d"`

clean:
	rm -f a.out out* *.o gl2psTest gl2psTestSimple *~
	cd doc && ${MAKE} clean

purge:
	rm -f `find . -name "*~" -o -name "*~~" -o -name "\#*"\
               -o -name ".\#*" -o -name "gmon.out"`

mac:
	gcc -Wall -g -O0 -o gl2psTest gl2psTest.c gl2ps.c\
            -framework OpenGL -framework GLUT -framework Cocoa

mac2:
	gcc -Wall -g -O0 -o gl2psTestSimple gl2psTestSimple.c gl2ps.c\
            -framework OpenGL -framework GLUT -framework Cocoa

linux:
	gcc -Wall -g -O3 -I/usr/X11R6/include -o gl2psTest gl2psTest.c gl2ps.c\
            -lglut -lGLU -lGL -L/usr/X11R6/lib -lX11 -lm

macz:
	gcc -DHAVE_ZLIB -DHAVE_LIBPNG -Wall -g -O0 -o gl2psTest gl2psTest.c gl2ps.c\
            -framework OpenGL -framework GLUT -framework Cocoa -lz\
                -I/usr/local/include/FL/images -lfltk_png

linuxz:
	gcc -DHAVE_ZLIB -Wall -g -O3 -I/usr/X11R6/include -o gl2psTest gl2psTest.c gl2ps.c\
            -lglut -lGLU -lGL -L/usr/X11R6/lib -lX11 -lm -lz

# -Wbad-function-cast
test:
	gcc -g -O3 -W -Wall\
           -DHAVE_ZLIB -DHAVE_LIBPNG -I/usr/local/include/FL/images\
           -Wredundant-decls -Wcast-align -Wmissing-prototypes\
           -Wsign-compare -Wpointer-arith -Wundef -ansi -pedantic\
           -c gl2ps.c
	g++ -O3 -Wall -ansi -pedantic -c gl2ps.c
	g++ -g -O3 -W -Wall -ansi -pedantic -c gl2psTest.c

distrib:
	rm -rf gl2ps-${RELEASE}/ gl2ps-${RELEASE}.tgz
	mkdir gl2ps-${RELEASE}
	cd doc && ${MAKE}
	sed -e "s/GL2PS_EXTRA_VERSION.*/GL2PS_EXTRA_VERSION \"\"/g"\
           gl2ps.h > gl2ps-${RELEASE}/gl2ps.h
	cp TODO COPYING.GL2PS COPYING.LGPL gl2ps.c gl2psTest.c\
           gl2psTestSimple.c doc/gl2ps.pdf gl2ps-${RELEASE}
	tar zcvf gl2ps-${RELEASE}.tgz gl2ps-${RELEASE}
	@echo "********************************************************************"
	@echo "Did you remember to untabify both gl2ps.c and gl2ps.h?"
	@echo "********************************************************************"

distrib-nightly:
	rm -rf gl2ps-nightly*
	mkdir gl2ps-cvs-${DATE}
	cd doc && ${MAKE} gl2ps.pdf
	sed -e "s/GL2PS_EXTRA_VERSION.*/GL2PS_EXTRA_VERSION \"-cvs-${DATE}\"/g"\
           gl2ps.h > gl2ps-cvs-${DATE}/gl2ps.h
	cp TODO COPYING.GL2PS COPYING.LGPL gl2ps.c gl2psTest.c\
           gl2psTestSimple.c doc/gl2ps.pdf gl2ps-cvs-${DATE}
	tar zcvf gl2ps-nightly.tgz gl2ps-cvs-${DATE}
	rm -rf gl2ps-cvs-${DATE}
