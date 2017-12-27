all:
	make -f Makefile.latex main
	make -f Makefile.latex clean

clean:
	make -f Makefile.latex clean

open:
	nohup evince main.pdf 1> /dev/null 2> /dev/null &
