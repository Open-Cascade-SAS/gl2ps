
default: gl2ps.ps gl2ps.html gl2ps.pdf

gl2ps.ps: gl2ps.tex
	rm -f gl2ps.toc gl2ps.out gl2ps.aux
	latex gl2ps
	latex gl2ps
	latex gl2ps
	dvips gl2ps -o

gl2ps.pdf: gl2ps.tex
	rm -f gl2ps.toc gl2ps.out gl2ps.aux
	pdflatex gl2ps
	pdflatex gl2ps
	pdflatex gl2ps

gl2ps.html: gl2ps.tex gl2ps.ps
	rm -f gl2ps.html
	echo "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0 Transitional//EN\">" >> gl2ps.html
	echo "<html>" >> gl2ps.html
	echo "<head>" >> gl2ps.html
	echo "<title>GL2PS: an OpenGL to PostScript printing library</title>" >> gl2ps.html
	echo "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=ISO-8859-1\">" >> gl2ps.html
	echo "<meta name=\"Autor-Handle\" content=\"geuz@geuz.org\">" >> gl2ps.html
	echo "<link href=\"/general.css\" rel=\"stylesheet\" type=\"text/css\">" >> gl2ps.html
	echo "</head>" >> gl2ps.html
	echo "<body>" >> gl2ps.html
	tth -r -Lgl2ps < gl2ps.tex | sed -e "/<title>/D" >> gl2ps.html
	echo "<p>" >> gl2ps.html
	echo "<form action=\"https://www.paypal.com/cgi-bin/webscr\" method=\"post\">" >> gl2ps.html
	echo "<input type=\"hidden\" name=\"cmd\" value=\"_xclick\">" >> gl2ps.html
	echo "<input type=\"hidden\" name=\"business\" value=\"geuzaine@acm.caltech.edu\">" >> gl2ps.html
	echo "<input type=\"hidden\" name=\"item_name\" value=\"GL2PS donation\">" >> gl2ps.html
	echo "<input type=\"hidden\" name=\"no_note\" value=\"1\">" >> gl2ps.html
	echo "<input type=\"hidden\" name=\"currency_code\" value=\"USD\">" >> gl2ps.html
	echo "<input type=\"hidden\" name=\"tax\" value=\"0\">" >> gl2ps.html
	echo "<input type=\"image\" src=\"/images/donation.gif\" name=\"submit\"" >> gl2ps.html
	echo "       alt=\"Make a donation with PayPal\">" >> gl2ps.html
	echo "</form>" >> gl2ps.html
	echo "<p>Back to <a href=\"/\">geuz.org</a>" >> gl2ps.html
	echo "</body>" >> gl2ps.html
	echo "</html>" >> gl2ps.html

clean:
	rm -f *~ *.dvi *.ps *.pdf *.aux *.toc *.log *.html *.out
