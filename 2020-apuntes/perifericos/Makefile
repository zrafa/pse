
CAP = perifericos-pse2020.tex

pdf: $(CAP)
	if (! ls build) ; then mkdir build ; fi
	xelatex -output-directory=build $^
	pdftk build/*pdf cat 13 15-end output /tmp/out_tmp_build_pse.pdf
	mv /tmp/out_tmp_build_pse.pdf build/*.pdf

clean:
	rm -rf build

