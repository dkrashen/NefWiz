OBJ = ../../obj/


formula_data_configuration:
	ls | grep "\.c" | sed /~/d > formula_list
	formula_concat < formula_list > new_formula_list
	mv new_formula_list formula_list
	echo 'FORMULA_DATA = \' > formula_data.mk
	cat formula_list >> formula_data.mk
	echo '' >> formula_data.mk
	mv formula_data.mk $(OBJ)
	rm formula_list



