
default:
	latex gl2ps
	latex gl2ps
	latex gl2ps
	dvips gl2ps -o
	rm -f gl2ps.toc gl2ps.out gl2ps.aux
	make html
	pdflatex gl2ps
	pdflatex gl2ps
	pdflatex gl2ps

html:
	rm gl2ps.html
	echo "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0 Transitional//EN\">" >> gl2ps.html
	echo "<HTML>" >> gl2ps.html
	echo "<HEAD>" >> gl2ps.html
	echo "<TITLE>GL2PS: an OpenGL to Postscript printing library</TITLE>" >> gl2ps.html
	echo "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=ISO-8859-1\">" >> gl2ps.html
	echo "<META name=\"Autor-Handle\" content=\"Christophe.Geuzaine@advalvas.be\">" >> gl2ps.html
	echo "<LINK href=\"/general.css\" rel=\"stylesheet\">" >> gl2ps.html
	echo "</HEAD>" >> gl2ps.html
	echo "<BODY>" >> gl2ps.html
	tth -r -Lgl2ps < gl2ps.tex | sed -e "/<title>/D" >> gl2ps.html
	echo "<P>Back to <a href=\"/\">geuz.org</a>" >> gl2ps.html
	echo "</BODY>" >> gl2ps.html
	echo "</HTML>" >> gl2ps.html
