all:
		flex calcuLex.l
		gcc lex.yy.c -ll -o calcuLexAnalyzer
		gcc syntax_calculator.c -o calcuSynAnalyzer

clean:
		rm -rf lex.yy.c
		rm -rf calcuLexAnalyzer
		rm -rf calcuSynAnalyzer
		rm -rf tokens.out