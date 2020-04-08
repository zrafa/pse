
CAP = intro-pse2020.tex

pdf: $(CAP)
	if (! ls build) ; then mkdir build ; fi
	xelatex -output-directory=build $^

clean:
	rm -rf build

