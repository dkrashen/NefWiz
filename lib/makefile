##############################################################
#
# 	BASIC DEFINITIONS
#
##############################################################



##############################################################
# PATHS
#
# (this makefile should reside in the main obj directory)
#
##############################################################

###########################################
# this should be the main nefwiz directory
BASE_DIR = ..
###########################################

SRC_DIR = src
INCLUDE_DIR = include
FORMULAS_SRC_DIR = src/formulas
FLAG_SRC_DIR = src/flag

##############################################################
# COMPILER OPTIONS
##############################################################

CC = gcc

VPATH = $(INCLUDE_DIR):$(SRC_DIR):$(FORMULAS_SRC_DIR):$(FLAG_SRC_DIR)

CFLAGS = -O3 -I$(INCLUDE_DIR) -I$(SRC_DIR) -I$(FORMULAS_SRC_DIR) \
-I$(FLAG_SRC_DIR)



##############################################################

##############################################################

OBJ = list.o divisor.o big_arithmetic.o restriction.o \
easy_filters.o flag.o proof.o proof_tree.o latex_display.o

#############################################################

obj: $(OBJ)

#############################################################

filter_config.o: filter_config.h filter_config.c 

list_calculator.o: list.h list_calculator.c

proof.o: proof.h proof.c restriction.h

proof_tree.o: proof_tree.h proof_tree.c flag.h list.h

easy_filters.o: divisor.h easy_filters.h easy_filters.c

flag.o: restriction.h divisor.h flag.h flag.c $(FLAG_STUFF)

divisor.o: list.h divisor.h divisor.c

restriction.o: divisor.h list.h big_arithmetic.h \
restriction.h restriction.c

big_arithmetic.o: list.h big_arithmetic.h big_arithmetic.c

list.o: list.h list.c

latex_display.o: latex_display.h latex_display.c

clean:
	rm -f $(OBJ)
