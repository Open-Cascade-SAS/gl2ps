#  GL2PS, an OpenGL to PostScript Printing Library
#  Copyright (C) 1999-2009 C. Geuzaine
# 
#  This program is free software; you can redistribute it and/or
#  modify it under the terms of either:
# 
#  a) the GNU Library General Public License as published by the Free
#  Software Foundation, either version 2 of the License, or (at your
#  option) any later version; or
# 
#  b) the GL2PS License as published by Christophe Geuzaine, either
#  version 2 of the License, or (at your option) any later version.
# 
#  This program is distributed in the hope that it will be useful, but
#  WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See either
#  the GNU Library General Public License or the GL2PS License for
#  more details.
# 
#  You should have received a copy of the GNU Library General Public
#  License along with this library in the file named "COPYING.LGPL";
#  if not, write to the Free Software Foundation, Inc., 675 Mass Ave,
#  Cambridge, MA 02139, USA.
# 
#  You should have received a copy of the GL2PS License with this
#  library in the file named "COPYING.GL2PS"; if not, I will be glad
#  to provide one.
# 
#  For the latest info about gl2ps and a full list of contributors,
#  see http://www.geuz.org/gl2ps/.
# 
#  Please report all bugs and problems to <gl2ps@geuz.org>.

cmake_minimum_required(VERSION 2.4 FATAL_ERROR)

# if CMAKE_BUILD_TYPE is specified use it; otherwise set the default
# build type to "RelWithDebInfo" ("-O2 -g" with gcc) prior to calling
# project()
if(DEFINED CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE} CACHE STRING "Choose build type")
else(DEFINED CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "Choose build type")
endif(DEFINED CMAKE_BUILD_TYPE)

project(gl2ps C)

set(GL2PS_MAJOR_VERSION 1)
set(GL2PS_MINOR_VERSION 3)
set(GL2PS_PATCH_VERSION 4)
set(GL2PS_EXTRA_VERSION "" CACHE STRING "GL2PS extra version string")

execute_process(COMMAND date "+%Y%m%d" OUTPUT_VARIABLE DATE 
                OUTPUT_STRIP_TRAILING_WHITESPACE)
if(NOT DATE)
  set(DATE "unknown")
endif(NOT DATE)
set(GL2PS_DATE "${DATE}")

find_package(OpenGL REQUIRED)
list(APPEND EXTERNAL_INCLUDES ${OPENGL_INCLUDE_DIR})
list(APPEND EXTERNAL_LIBRARIES ${OPENGL_LIBRARIES})

find_package(GLUT)
if(GLUT_FOUND)
  list(APPEND EXTERNAL_INCLUDES ${GLUT_INCLUDE_DIR})
  list(APPEND EXTERNAL_LIBRARIES ${GLUT_LIBRARIES})
endif(GLUT_FOUND)

find_package(ZLIB)
if(ZLIB_FOUND)
  add_definitions(-DHAVE_ZLIB)
  list(APPEND EXTERNAL_INCLUDES ${ZLIB_INCLUDE_DIR})
  list(APPEND EXTERNAL_LIBRARIES ${ZLIB_LIBRARIES})
endif(ZLIB_FOUND)

find_package(PNG)
if(PNG_FOUND)
  list(APPEND EXTERNAL_LIBRARIES ${PNG_LIBRARIES})
  list(APPEND EXTERNAL_INCLUDES ${PNG_INCLUDE_DIR})
endif(PNG_FOUND)

include_directories(${EXTERNAL_INCLUDES})

add_library(lib STATIC gl2ps.c gl2ps.h)
set_target_properties(lib PROPERTIES OUTPUT_NAME gl2ps)

if(MSVC)
  add_definitions(-DGL2PSDLL -DGL2PSDLL_EXPORTS)
endif(MSVC)

add_library(shared SHARED gl2ps.c gl2ps.h)
set_target_properties(shared PROPERTIES OUTPUT_NAME gl2ps)
target_link_libraries(shared ${EXTERNAL_LIBRARIES})

if(GLUT_FOUND)
  add_executable(gl2psTest WIN32 gl2psTest.c)
  target_link_libraries(gl2psTest shared ${EXTERNAL_LIBRARIES})
  add_executable(gl2psTestSimple WIN32 gl2psTestSimple.c)
  target_link_libraries(gl2psTestSimple shared ${EXTERNAL_LIBRARIES})
endif(GLUT_FOUND)

install(TARGETS lib shared DESTINATION lib)
install(FILES gl2ps.h DESTINATION include)

# distrib:
# 	rm -rf gl2ps-${RELEASE}/ gl2ps-${RELEASE}.tgz
# 	mkdir gl2ps-${RELEASE}
# 	cd doc && ${MAKE}
# 	sed -e "s/GL2PS_EXTRA_VERSION.*/GL2PS_EXTRA_VERSION \"\"/g"\
#            gl2ps.h > gl2ps-${RELEASE}/gl2ps.h
# 	cp TODO COPYING.GL2PS COPYING.LGPL gl2ps.c gl2psTest.c\
#            gl2psTestSimple.c doc/gl2ps.pdf gl2ps-${RELEASE}
# 	tar zcvf gl2ps-${RELEASE}.tgz gl2ps-${RELEASE}
# 	@echo "********************************************************************"
# 	@echo "Did you remember to untabify both gl2ps.c and gl2ps.h?"
# 	@echo "********************************************************************"

# distrib-nightly:
# 	rm -rf gl2ps-cvs*
# 	mkdir gl2ps-cvs-${DATE}
# 	cd doc && ${MAKE} gl2ps.pdf
# 	sed -e "s/GL2PS_EXTRA_VERSION.*/GL2PS_EXTRA_VERSION \"-cvs-${DATE}\"/g"\
#            gl2ps.h > gl2ps-cvs-${DATE}/gl2ps.h
# 	cp TODO COPYING.GL2PS COPYING.LGPL gl2ps.c gl2psTest.c\
#            gl2psTestSimple.c doc/gl2ps.pdf gl2ps-cvs-${DATE}
# 	tar zcvf gl2ps-cvs.tgz gl2ps-cvs-${DATE}
# 	rm -rf gl2ps-cvs-${DATE}

# gl2ps.ps: gl2ps.tex
#         rm -f gl2ps.toc gl2ps.out gl2ps.aux
#         latex gl2ps
#         latex gl2ps
#         latex gl2ps
#         dvips gl2ps -o

# gl2ps.pdf: gl2ps.tex
#         rm -f gl2ps.toc gl2ps.out gl2ps.aux
#         pdflatex gl2ps
#         pdflatex gl2ps
#         pdflatex gl2ps

# gl2ps.html: gl2ps.tex gl2ps.pdf
#         rm -f gl2ps.html
#         echo "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\">" >> gl2ps.html
#         echo "<html>" >> gl2ps.html
#         echo "<head>" >> gl2ps.html
#         echo "<title>GL2PS: an OpenGL to PostScript printing library</title>" >> gl2ps.html
#         echo "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=ISO-8859-1\">" >> gl2ps.html
#         echo "<link href=\"/general.css\" rel=\"stylesheet\" type=\"text/css\">" >> gl2ps.html
#         echo "</head>" >> gl2ps.html
#         echo "<body>" >> gl2ps.html
#         tth -r -Lgl2ps < gl2ps.tex | sed -e "/<title>/D" -e "s|<h1>.*Contents.*</h1>||g" >> gl2ps.html
#         echo "<p>" >> gl2ps.html
#         echo "<form action=\"https://www.paypal.com/cgi-bin/webscr\" method=\"post\">" >> gl2ps.html
#         echo "<input type=\"hidden\" name=\"cmd\" value=\"_xclick\">" >> gl2ps.html
#         echo "<input type=\"hidden\" name=\"business\" value=\"geuzaine@acm.caltech.edu\">" >> gl2ps.html
#         echo "<input type=\"hidden\" name=\"item_name\" value=\"GL2PS donation\">" >> gl2ps.html
#         echo "<input type=\"hidden\" name=\"no_note\" value=\"1\">" >> gl2ps.html
#         echo "<input type=\"hidden\" name=\"currency_code\" value=\"USD\">" >> gl2ps.html
#         echo "<input type=\"hidden\" name=\"tax\" value=\"0\">" >> gl2ps.html
#         echo "<input type=\"image\" src=\"/images/donation.gif\" name=\"submit\"" >> gl2ps.html
#         echo "       alt=\"Make a donation with PayPal\">" >> gl2ps.html
#         echo "</form>" >> gl2ps.html
#         echo "<p>Back to <a href=\"/\">geuz.org</a>" >> gl2ps.html
#         echo "</body>" >> gl2ps.html
#         echo "</html>" >> gl2ps.html

# clean:
#         rm -f *~ *.dvi *.ps *.pdf *.aux *.toc *.log *.html *.out
