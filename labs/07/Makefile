all:
	yacc -d calcuSyntax.y
	flex calcuLex.l
	gcc lex.yy.c y.tab.c -lfl -o calculadora

clean:
	rm -rf *.c
	rm -rf *.o
	rm -rf *.h
	rm -rf calculadora
	rm -rf derivationTree.dot