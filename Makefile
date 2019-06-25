LATEXCMD = pdflatex -shell-escape -output-directory pdf/build/
export TEXINPUTS=.:pdf/kactl-include/:
export max_print_line = 1048576

help:
	@echo "This makefile builds the pdf using KACTL code"
	@echo ""
	@echo "Available commands are:"
	@echo "	make pdf	- to build KACTL"
	@echo "	make clean	- to clean up the build process"
	@echo "	make veryclean	- to clean up and remove main.pdf"
	@echo "	make help	- to show this information"
	@echo ""
	@echo "For more information see the file 'doc/README'"

pdf: | build
	$(LATEXCMD) code/main.tex </dev/null
	$(LATEXCMD) code/main.tex </dev/null
	cp pdf/build/main.pdf main.pdf
	rm header.tmp

clean: 
	cd pdf/build && rm -f main.aux main.log main.tmp main.toc main.pdf main.ptc main.out

veryclean: clean
	rm -f main.pdf

.PHONY: help pdf clean veryclean

build:
	mkdir -p pdf/build/
