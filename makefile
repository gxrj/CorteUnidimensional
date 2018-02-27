# -*- Makefile -*-

exec: *.o
	@gcc *.o -o exec
	@rm -f *.o
*.o: *.c IFFPO.H
	@gcc -c *.c
clear:
	@rm -f *.o exec saida.txt melhores.txt

