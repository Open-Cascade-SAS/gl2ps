
default:
	latex gl2ps
	latex gl2ps
	latex gl2ps
	dvips gl2ps -o
	make html
	rm -f gl2ps.toc gl2ps.out gl2ps.aux
	pdflatex gl2ps
	pdflatex gl2ps
	pdflatex gl2ps

html:
	rm -f gl2ps.html
	echo "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0 Transitional//EN\">" >> gl2ps.html
	echo "<html>" >> gl2ps.html
	echo "<head>" >> gl2ps.html
	echo "<title>GL2PS: an OpenGL to PostScript printing library</title>" >> gl2ps.html
	echo "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=ISO-8859-1\">" >> gl2ps.html
	echo "<meta name=\"Autor-Handle\" content=\"geuz@geuz.org\">" >> gl2ps.html
	echo "<link href=\"/general.css\" rel=\"stylesheet\">" >> gl2ps.html
	echo "</head>" >> gl2ps.html
	echo "<body>" >> gl2ps.html
	tth -r -Lgl2ps < gl2ps.tex | sed -e "/<title>/D" >> gl2ps.html
	echo "<p>Back to <a href=\"/\">geuz.org</a>" >> gl2ps.html
	echo "</body>" >> gl2ps.html
	echo "</html>" >> gl2ps.html

clean:
	rm -f *~ gl2ps.dvi gl2ps.ps gl2ps.pdf *.aux *.toc *.log *.html *.out
