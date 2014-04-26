##############################################################
#
# 	BASIC DEFINITIONS
#
##############################################################



##############################################################
# PATHS       
##############################################################

###########################################
# this should be the main nefwiz directory
BASE_DIR = .
###########################################

OBJ_DIR = $(BASE_DIR)/lib

SRC_DIR = $(BASE_DIR)/src

INCLUDE_DIR = $(BASE_DIR)/lib/include

##############################################################
# COMPILER OPTIONS
##############################################################

CC = gcc

LEX = flex

CFLAGS = -O3 -I$(INCLUDE_DIR) -I$(SRC_DIR) -I$(OBJ_DIR) -lm

CFLAGS_CONE = -o

##############################################################
# MAKE DIRECTORIES TO FIND DEPENDENCIES
##############################################################

VPATH = $(INCLUDE_DIR):$(SRC_DIR):$(OBJ_DIR)

##############################################################

OBJ = $(OBJ_DIR)/list.o $(OBJ_DIR)/divisor.o \
$(OBJ_DIR)/big_arithmetic.o $(OBJ_DIR)/restriction.o \
$(OBJ_DIR)/easy_filters.o $(OBJ_DIR)/flag.o $(OBJ_DIR)/proof.o \
$(OBJ_DIR)/proof_tree.o $(OBJ_DIR)/latex_display.o 


BIN = $(BASE_DIR)/filter $(BASE_DIR)/div2prf $(BASE_DIR)/autodiv2prf


GENERATED = $(SRC_DIR)/autodiv2prf.c $(SRC_DIR)/wizcalc.c $(SRC_DIR)/rescalc.c

####################################################################

####################################################################

default: 
	@cd $(OBJ_DIR) ; $(MAKE)
	@$(MAKE) conestuff
	@$(MAKE) bin
	@$(MAKE) lrs

backup:
	@bash bin/backup_script

bin: $(BIN)

#############################################################

$(BASE_DIR)/filter: list.h divisor.h $(OBJ) $(SRC_DIR)/filter.c
	$(CC) $(CFLAGS) -o $(BASE_DIR)/filter $(SRC_DIR)/filter.c $(OBJ)
	@cp $(SRC_DIR)/ezwizit $(BASE_DIR)
	@cp $(SRC_DIR)/wizit $(BASE_DIR)
	@cp $(SRC_DIR)/prfit $(BASE_DIR)

$(BASE_DIR)/div2prf: list.h divisor.h $(OBJ) \
 $(SRC_DIR)/div2prf.c
	$(CC) $(CFLAGS) -o $(BASE_DIR)/div2prf \
 $(SRC_DIR)/div2prf.c $(OBJ)

$(BASE_DIR)/autodiv2prf: list.h divisor.h $(OBJ) \
 $(SRC_DIR)/autodiv2prf.c
	$(CC) $(CFLAGS) -o $(BASE_DIR)/autodiv2prf \
 $(SRC_DIR)/autodiv2prf.c $(OBJ)

#############################################################
# CONE STUFF
#############################################################

CONE_BIN_DIR = cones/bin

CONE_SRC_DIR = src/cone_src

CONE_BIN = $(CONE_BIN_DIR)/ftestmg $(CONE_BIN_DIR)/flag2mg \
$(CONE_BIN_DIR)/mg2flag $(CONE_BIN_DIR)/linelength \
$(CONE_BIN_DIR)/standardform $(CONE_BIN_DIR)/rm_format \
$(CONE_BIN_DIR)/reduce $(CONE_BIN_DIR)/clearden $(CONE_BIN_DIR)/genieq_flag \
$(CONE_BIN_DIR)/genieq_mg $(CONE_BIN_DIR)/gen_cone_script \
$(CONE_BIN_DIR)/findline

CONE_GENERATED = $(CONE_SRC_DIR)/linelength.c $(CONE_SRC_DIR)/standardform.c \
$(CONE_SRC_DIR)/reduce.c $(CONE_SRC_DIR)/clearden.c \
$(CONE_SRC_DIR)/rm_format.c $(CONE_SRC_DIR)/mg2flag.c \
$(CONE_SRC_DIR)/flag2mg.c $(CONE_SRC_DIR)/ftestmg.c


conestuff : $(CONE_BIN)
	@cp $(CONE_SRC_DIR)/make_cones $(BASE_DIR)

$(CONE_BIN_DIR)/ftestmg : $(CONE_SRC_DIR)/ftestmg.c
	$(CC) $(CFLAGS_CONE) $(CONE_BIN_DIR)/ftestmg $(CONE_SRC_DIR)/ftestmg.c

$(CONE_BIN_DIR)/flag2mg : $(CONE_SRC_DIR)/flag2mg.c
	$(CC) $(CFLAGS_CONE) $(CONE_BIN_DIR)/flag2mg $(CONE_SRC_DIR)/flag2mg.c

$(CONE_BIN_DIR)/mg2flag : $(CONE_SRC_DIR)/mg2flag.c
	$(CC) $(CFLAGS_CONE) $(CONE_BIN_DIR)/mg2flag $(CONE_SRC_DIR)/mg2flag.c

$(CONE_BIN_DIR)/linelength : $(CONE_SRC_DIR)/linelength.c
	$(CC) $(CFLAGS_CONE) $(CONE_BIN_DIR)/linelength \
$(CONE_SRC_DIR)/linelength.c

$(CONE_BIN_DIR)/standardform : $(CONE_SRC_DIR)/standardform.c
	$(CC) $(CFLAGS_CONE) $(CONE_BIN_DIR)/standardform \
$(CONE_SRC_DIR)/standardform.c

$(CONE_BIN_DIR)/reduce : $(CONE_SRC_DIR)/reduce.c
	$(CC) $(CFLAGS_CONE) $(CONE_BIN_DIR)/reduce $(CONE_SRC_DIR)/reduce.c

$(CONE_BIN_DIR)/clearden : $(CONE_SRC_DIR)/clearden.c
	$(CC) $(CFLAGS_CONE) $(CONE_BIN_DIR)/clearden \
$(CONE_SRC_DIR)/clearden.c

$(CONE_BIN_DIR)/rm_format : $(CONE_SRC_DIR)/rm_format.c
	$(CC) $(CFLAGS_CONE) $(CONE_BIN_DIR)/rm_format \
$(CONE_SRC_DIR)/rm_format.c

$(CONE_BIN_DIR)/genieq_flag : $(CONE_SRC_DIR)/genieq_flag.c
	$(CC) $(CFLAGS_CONE) $(CONE_BIN_DIR)/genieq_flag \
$(CONE_SRC_DIR)/genieq_flag.c

$(CONE_BIN_DIR)/genieq_mg : $(CONE_SRC_DIR)/genieq_mg.c
	$(CC) $(CFLAGS_CONE) $(CONE_BIN_DIR)/genieq_mg \
$(CONE_SRC_DIR)/genieq_mg.c

$(CONE_BIN_DIR)/findline : $(CONE_SRC_DIR)/findline.c
	$(CC) $(CFLAGS_CONE) $(CONE_BIN_DIR)/findline \
$(CONE_SRC_DIR)/findline.c

$(CONE_BIN_DIR)/gen_cone_script : $(CONE_SRC_DIR)/gen_cone_script.c
	$(CC) $(CFLAGS_CONE) $(CONE_BIN_DIR)/gen_cone_script \
$(CONE_SRC_DIR)/gen_cone_script.c

clean_cones :
	rm -f $(CONE_BIN) $(CONE_GENERATED) $(BASE_DIR)/make_cones
	cd cones ; bash bin/clear_cones ; cd ..


#############################################################
# LRS
#############################################################

lrs:
	@echo installing lrs files...
	@mv src/lrslib-041.tar.gz ./
	@gunzip lrslib-041.tar.gz
	@tar -xf lrslib-041.tar
	@cd lrslib-041 ; $(MAKE) -s ; cp ./lrs ../cones/bin ; \
cp ./redund ../cones/bin
	@gzip lrslib-041.tar
	@mv lrslib-041.tar.gz src
	@rm -f -r lrslib-041/
	@echo done.

clean_lrs:
	rm -f cones/bin/lrs cones/bin/redund

#############################################################

clean:
	rm -f $(BIN) $(GENERATED) $(BASE_DIR)/wizit $(BASE_DIR)/ezwizit \
$(BASE_DIR)/prfit
	@cd $(OBJ_DIR) ; $(MAKE) clean
	@$(MAKE) clean_cones
	$(MAKE) clean_lrs

