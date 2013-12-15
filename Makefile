.PHONY: all
all:
	echo "make src begin"
	make -C src clean
	rm -rf output
	mkdir output
	make -C src
	echo "make src done"
.PHONY: clean
clean:
	echo "make clean begin"
	make -C src clean
	rm -rf output
	echo "make clean done"

.PHONY: tags
tags :
	ctags -R *
