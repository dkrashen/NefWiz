CC = gcc
INCLUDE = ../../../include

VPATH = $(INCLUDE)

CFLAGS = -g -O -D_USE_FIXED_PROTOTYPES_ -I$(INCLUDE)

GENERATED_CODE = calc_parse.c calc_parse_lexer.c formula_concat.c

EXECUTABLE = ../calc_parse ../formula_concat

OBJ = calc_parse.o

all: $(EXECUTABLE)

portable: $(GENERATED_CODE)
	rm -f $(EXECUTABLE) $(OBJ)

../calc_parse : calc_parse.o basic_types.h
	$(CC) $(CFLAGS) -o ../calc_parse calc_parse.o 

calc_parse.o: calc_parse.c calc_parse_lexer.c

calc_parse.c : calc_parse.y calc_parse_lexer.c
	yacc calc_parse.y
	mv y.tab.c calc_parse.c


calc_parse_lexer.c: calc_parse_lexer.l
	lex -Pcalc_parse_lexer calc_parse_lexer.l
	mv lex.calc_parse_lexer.c calc_parse_lexer.c


../formula_concat : formula_concat.c
	$(CC) $(CFLAGS) -o ../formula_concat formula_concat.c

formula_concat.c: formula_concat.l 
	lex -Pformula_concat formula_concat.l
	mv lex.formula_concat.c formula_concat.c


clean:
	rm -f $(GENERATED_CODE) $(EXECUTABLE) $(OBJ)
