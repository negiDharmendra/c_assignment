aU_1:
	gcc ./array_util/array_util.c ./array_util/array_util_main.c -o ./array_util/array_util
exaU_1:
	./array_util/array_util
claU_1:
	rm ./array_util/array_util
aUTest:
	gcc ./array_util/arrayUtil_test.c ./array_util/array_util.c -o ./array_util/arrayUtilTest
exaUTest:
	./array_util/arrayUtilTest
claUtest:
	rm ./array_util/arrayUtilTest